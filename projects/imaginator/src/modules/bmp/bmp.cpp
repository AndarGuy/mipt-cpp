#include "bmp.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

#include "headers/headers.hpp"

// Bitmap::Bitmap(std::string path) noexcept {
//     std::ifstream stream;
//     stream.open(path, std::ios::binary);
//     if (!stream.is_open()) {
//         BITMAP_FILE_HEADER header;
//         stream.read((char*)&header, sizeof(BITMAP_FILE_HEADER));
//     }
// }

Bitmap::Bitmap(std::fstream stream) {
    this->file_stream = std::move(stream);
    this->file_header = BITMAP_FILE_HEADER::read_header(this->file_stream);
    if (this->file_header == nullptr) throw new BitmapCorruptedException();
    if (!this->file_header->check_header()) throw new NotBitmapException();
    this->dib_header = BITMAP_DIB_HEADER::read_header(this->file_stream);
    if (this->dib_header == nullptr) throw new BitmapCorruptedException();
}