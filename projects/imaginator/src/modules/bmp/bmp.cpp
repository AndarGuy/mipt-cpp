#include "bmp.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

#include "headers/headers.hpp"
#include "pixel_storage/pixel_storage.hpp"

Bitmap::Bitmap(std::istream&& stream) {
  this->file_header = BITMAP_FILE_HEADER::read(stream);
  if (this->file_header == nullptr)
    throw new BitmapCorruptedException();
  if (!this->file_header->check_header())
    throw new NotBitmapException();
  this->dib_header = BITMAP_DIB_HEADER::read(stream);
  if (this->dib_header == nullptr)
    throw new BitmapCorruptedException();
  this->pixel_storage = PIXEL_MATRIX::read(stream, this->file_header.get(), this->dib_header.get());
}

void Bitmap::save(std::ostream& stream) {
  this->file_header->write(stream);
  this->dib_header->write(stream);
  this->pixel_storage->write(stream);
}

void Bitmap::save(std::string path) {
  std::ofstream stream(path, std::ios::binary);
  this->save(stream);
}

void Bitmap::apply(std::function<void(Bitmap&)> processor) {
  processor(*this);
}