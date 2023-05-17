#pragma once

#include <cinttypes>
#include <string>
#include <functional>

#include "exceptions/exceptions.hpp"
#include "headers/headers.hpp"
#include "pixel_storage/pixel_storage.hpp"

// **COLOR TABLE**

// ...............

// NOT IMPLEMENTED YET

// **BITMAP DATA**

// ...............

class Bitmap {
 private:
  std::unique_ptr<BITMAP_FILE_HEADER> file_header;
  std::unique_ptr<BITMAP_DIB_HEADER> dib_header;
  std::unique_ptr<PIXEL_MATRIX> pixel_storage;

 public:
  // Constructor by default.
  Bitmap() = default;

  /// @brief Copy constructor.
  /// @param bitmap The bitmap to copy.
  Bitmap(const Bitmap& bitmap)
      : file_header(bitmap.file_header->clone())
      , dib_header(bitmap.dib_header->clone())
      , pixel_storage(bitmap.pixel_storage->clone(file_header.get(), dib_header.get())) {
    // Constructor implemented using initialization list.
  }

  /// @brief Move constructor.
  /// @param bitmap The bitmap to move.
  Bitmap(Bitmap&& bitmap) = default;

  /// @brief Move operator.
  /// @param bitmap The bitmap to move.
  /// @return Bitmap.
  Bitmap operator=(Bitmap&& bitmap) {
    this->file_header = std::move(bitmap.file_header);
    this->dib_header = std::move(bitmap.dib_header);
    this->pixel_storage = std::move(bitmap.pixel_storage);
    return *this;
  }

  /// @brief Copy operator.
  /// @param bitmap The bitmap to copy.
  /// @return Bitmap.
  Bitmap operator=(const Bitmap& bitmap) {
    this->file_header = bitmap.file_header->clone();
    this->dib_header = bitmap.dib_header->clone();
    this->pixel_storage = bitmap.pixel_storage->clone(file_header.get(), dib_header.get());
    return *this;
  }

  /// @brief Open bitmap from file.
  /// @param path The path to a bitmap file.
  Bitmap(std::string path) : Bitmap(std::ifstream(path)) {
    // Extension of previous declared constructor.
  }

  /// @brief Read bitmap from stream.
  /// @param  stream The stream to read from.
  Bitmap(std::istream&&);

  /// @brief The function saves bitmap using given path.
  /// @param path A path to save.
  void save(std::string path);

  /// @brief The function saves bitmap using provided stream.
  /// @param stream
  void save(std::ostream& stream);

  void apply(std::function<void(Bitmap&)> processor);

  /// @brief Operator[] gets PIXEL_ROW by row number.
  /// @param x A number of a row.
  /// @return PIXEL_ROW.
  PIXEL_ROW operator[](size_t x) const {
    return this->pixel_storage->get_line(x);
  }

  /// @brief Function for supporting iterating.
  /// @return Iterator of PIXEL_ROW.
  PIXEL_MATRIX::Iterator begin() {
    return this->pixel_storage->begin();
  }

  /// @brief Function for supporting iterating.
  /// @return Iterator of PIXEL_ROW.
  PIXEL_MATRIX::Iterator end() {
    return this->pixel_storage->end();
  }

  /// @brief Get height of the BITMAP.
  /// @return The height of the BITMAP.
  size_t height() {
    return this->dib_header->get_height();
  }

  /// @brief Get width of the BITMAP.
  /// @return The width of the BITMAP.
  size_t width() {
    return this->dib_header->get_width();
  }

  void resize(size_t height, size_t width) {
    int32_t delta = this->pixel_storage->resize(height, width);
    this->dib_header->set_height(height);
    this->dib_header->set_width(width);
    this->file_header->set_file_size(this->file_header->get_file_size() + delta);
  }
};