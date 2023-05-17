#include <iostream>

#include "modules/bmp/headers/headers.hpp"
#include "modules/bmp/bmp.hpp"
#include "modules/filters/filters.hpp"

int main() {
  std::ifstream stream;
  stream.open("../examples/blue.bmp", std::ios::binary);
  std::unique_ptr<BITMAP_FILE_HEADER> header = BITMAP_FILE_HEADER::read(stream);
  std::cout << *header << std::endl;

  std::unique_ptr<BITMAP_DIB_HEADER> dib_header = BITMAP_DIB_HEADER::read(stream);
  std::cout << *dib_header << std::endl;

  std::unique_ptr<PIXEL_MATRIX> pixel_storage = PIXEL_MATRIX::read(stream, header.get(), dib_header.get());

  Bitmap bitmap("../examples/blue.bmp");

  bitmap.apply(FILTER_REPLACE_COLOR({0, 3, 255}, {255, 0, 0}));

  // bitmap.apply(FILTER_NEGATIVE);

  std::cout << bitmap[0][0] << std::endl;

  bitmap.save("result.bmp");

  return 0;
}