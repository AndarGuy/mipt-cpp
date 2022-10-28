#include "pixel_storage.hpp"

uint32_t PixelStorage::calculate_row_size(int32_t image_width, uint16_t bits_per_pixel) {
    return std::ceil(((double)bits_per_pixel) * ((double)image_width) / 32) * 4;
}

uint32_t PixelStorage::calculate_pixel_array_size(int32_t image_heigth, uint32_t row_size) {
    return row_size * std::abs(image_heigth);
}
