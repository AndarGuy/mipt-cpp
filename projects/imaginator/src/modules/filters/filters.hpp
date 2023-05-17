#include "../bmp/bmp.hpp"

const auto FILTER_NEGATIVE = [](Bitmap& bitmap) {
  for (auto row : bitmap)
    for (auto pixel : row)
      pixel.set_rgb(UINT32_MAX - pixel.get_red(), UINT32_MAX - pixel.get_green(), UINT32_MAX - pixel.get_blue());
};

const auto FILTER_GRAYSCALE = [](Bitmap& bitmap) {
  for (auto row : bitmap)
    for (auto pixel : row) {
      int mean = (pixel.get_red() + pixel.get_green() + pixel.get_blue()) / 3;
      pixel.set_rgb(mean, mean, mean);
    }
};

const auto FILTER_REPLACE_COLOR = [](PIXEL replaceable, PIXEL replacement) {
  return [replaceable, replacement](Bitmap& bitmap) {
    for (auto row : bitmap)
      for (auto pixel : row) {
        if (pixel == replaceable)
          pixel = replacement;
      }
  };
};

const auto FILTER_SEPIA = [](Bitmap& bitmap) {
  for (auto row : bitmap) {
    for (auto pixel : row) {
      uint32_t red = pixel.get_red(), green = pixel.get_green(), blue = pixel.get_blue();
      pixel.set_rgb(std::min(255., blue * 0.272 + green * 0.534 + red * 0.131),
                    std::min(255., blue * 0.349 + green * 0.686 + red * 0.168),
                    std::min(255., blue * 0.393 + green * 0.769 + red * 0.189));
    }
  }
};

const auto CONVOLUTION = [](std::vector<std::vector<double>> kernel, double coefficient = 1) {
  return [kernel, coefficient](Bitmap& bitmap) {
    size_t kernel_height = kernel.size();
    if (!kernel_height)
      throw BitmapFilterIllegalArgument();
    size_t kernel_width [[maybe_unused]] = kernel[0].size();

    Bitmap copy = bitmap;

    for (size_t x = 0; x < bitmap.height(); x++) {
      for (size_t y = 0; y < bitmap.width(); y++) {
        double modified_red = 0, modified_green = 0, modified_blue = 0;
        for (size_t i = x; i < x + kernel_height && i < bitmap.height(); i++) {
          for (size_t j = y; j < y + kernel_width && j < bitmap.width(); j++) {
            double red = bitmap[i][j].get_red(), green = bitmap[i][j].get_green(), blue = bitmap[i][j].get_blue();
            double kernel_value = kernel[i - x][j - y] / coefficient;
            modified_red += red * kernel_value;
            modified_green += green * kernel_value;
            modified_blue += blue * kernel_value;
          }
        }
        copy[x][y].set_rgb(static_cast<uint32_t>(std::max(0., std::min(255., modified_red))),
                           static_cast<uint32_t>(std::max(0., std::min(255., modified_green))),
                           static_cast<uint32_t>(std::max(0., std::min(255., modified_blue))));
      }
    }

    bitmap = std::move(copy);
  };
};

const auto FILTER_GAUSSIAN_BLUR = [](size_t height, size_t width, double sigma) {
  std::vector<std::vector<double>> kernel(height, std::vector<double>(width));
  double coefficient = 0;

  if (height % 2 == 0 || width % 2 == 0)
    throw BitmapFilterIllegalArgument();

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      int x = i - height / 2, y = j - width / 2;
      double top = x * x + y * y;
      double bottom = 2 * sigma * sigma;
      double value = exp(-top / bottom) / (M_PI * bottom);
      kernel[i][j] = value;
      coefficient += kernel[i][j];
    }
  }

  return CONVOLUTION(kernel, coefficient);
};

const auto FILTER_IMPROVE_QUALITY = [](Bitmap& bitmap) {
  std::vector<std::vector<double>> kernel = {{-1, -1, -1}, {-1, 9, -1}, {-1, -1, -1}};
  CONVOLUTION(kernel)(bitmap);
};

const auto FILTER_EDGE_SELECTION = [](Bitmap& bitmap) {
  std::vector<std::vector<double>> kernel = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
  CONVOLUTION(kernel)(bitmap);
};

const auto FILTER_NOISE_REMOVAL = [](size_t height, size_t width) {
  if (height % 2 == 0 || width % 2 == 0)
    throw BitmapFilterIllegalArgument();

  return [height, width](Bitmap& bitmap) {
    Bitmap copy = bitmap;
    for (size_t x = 0; x < bitmap.height(); x++) {
      for (size_t y = 0; y < bitmap.width(); y++) {
        for (size_t color = 0; color < 3; color++) {
          std::vector<uint32_t> buffer;
          for (size_t i = x; i < x + height && i < bitmap.height(); i++) {
            for (size_t j = y; j < y + width && j < bitmap.width(); j++) {
              buffer.push_back(bitmap[i][j].get(color));
            }
          }

          std::sort(buffer.begin(), buffer.end());

          copy[x][y].set(color, buffer[buffer.size() / 2]);
        }
      }
    }

    bitmap = copy;
  };
};

const auto FILTER_CUT = [](size_t x, size_t y, size_t height, size_t width) {
  return [x, y, height, width]([[maybe_unused]] Bitmap& bitmap) {
    if (x + height > bitmap.height() || y + width > bitmap.width())
      throw BitmapFilterIllegalArgument();
    Bitmap copy = bitmap;
    copy.resize(height, width);
    for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
        copy[i][j] = bitmap[x + i][y + j];
      }
    }
    bitmap = std::move(copy);
  };
};