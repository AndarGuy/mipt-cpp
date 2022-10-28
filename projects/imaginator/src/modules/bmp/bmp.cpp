#include "bmp.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

#include "headers/headers.hpp"

// Bitmap::Bitmap(std::string path) noexcept {
//     std::ifstream stream;
//     stream.open(path, std::ios::binary);
//     if (!stream.is_open()) {
//         FileHeader header;
//         stream.read((char*)&header, sizeof(FileHeader));
//     }
// }

uint32_t PixelStorage::calculate_row_size(int32_t image_width, uint16_t bits_per_pixel) {
    return std::ceil(((double)bits_per_pixel) * ((double)image_width) / 32) * 4;
}

uint32_t PixelStorage::calculate_pixel_array_size(int32_t image_heigth, uint32_t row_size) {
    return row_size * std::abs(image_heigth);
}

Bitmap::Bitmap(std::fstream stream) {
    this->file_stream = std::move(stream);
    this->file_header = FileHeader::read_header(this->file_stream);
    if (this->file_header == nullptr) throw new BitmapCorruptedException();
    if (!this->file_header->check_header()) throw new NotBitmapException();
    this->dib_header = DIBHeader::read_header(this->file_stream);
    if (this->dib_header == nullptr) throw new BitmapCorruptedException();
}