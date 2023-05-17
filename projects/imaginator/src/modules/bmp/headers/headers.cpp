#include "headers.hpp"

#include <iostream>

bool BITMAP_FILE_HEADER::check_header() const {
  for (auto identificator :
       {IDENTIFICATOR_BM, IDENTIFICATOR_BA, IDENTIFICATOR_CI, IDENTIFICATOR_CP, IDENTIFICATOR_IC, IDENTIFICATOR_PT}) {
    if (this->identificator[0] == identificator[0] && this->identificator[1] == identificator[1])
      return true;
  }
  return false;
}

bool BITMAP_FILE_HEADER::check_size(uint32_t actual_size) const {
  return this->file_size == actual_size;
}

std::unique_ptr<BITMAP_FILE_HEADER> BITMAP_FILE_HEADER::read(std::istream& stream) {
  stream.seekg(BITMAP_FILE_HEADER::OFFSET, std::ios::beg);
  std::unique_ptr<BITMAP_FILE_HEADER> header_pointer(new BITMAP_FILE_HEADER);
  stream.read(static_cast<char*>(header_pointer->get_data_section()), BITMAP_FILE_HEADER::SIZE);
  if (stream.gcount() < BITMAP_FILE_HEADER::SIZE)
    return nullptr;
  return header_pointer;
}

void BITMAP_FILE_HEADER::write(std::ostream& stream) {
  stream.write(static_cast<char*>(this->get_data_section()), BITMAP_FILE_HEADER::SIZE);
}

std::unique_ptr<BITMAP_DIB_HEADER> BITMAP_DIB_HEADER::parse_header() const {
  return BITMAP_DIB_HEADER::parse_header(this->get_header_size());
}

std::unique_ptr<BITMAP_DIB_HEADER> BITMAP_DIB_HEADER::parse_header(uint32_t header_size) {
  switch (header_size) {
    case BITMAP_CORE_HEADER::SIZE:
      return std::unique_ptr<BITMAP_CORE_HEADER>(new BITMAP_CORE_HEADER);
    case BITMAP_INFO_HEADER::SIZE:
      return std::unique_ptr<BITMAP_INFO_HEADER>(new BITMAP_INFO_HEADER);
    case BITMAP_INFO_HEADER2::SIZE:
      return std::unique_ptr<BITMAP_INFO_HEADER2>(new BITMAP_INFO_HEADER2);
    default:
      return nullptr;
  }
}

std::unique_ptr<BITMAP_DIB_HEADER> BITMAP_DIB_HEADER::read(std::istream& stream) {
  stream.seekg(BITMAP_DIB_HEADER::OFFSET, std::ios::beg);
  std::unique_ptr<BITMAP_DIB_HEADER> header_pointer(new BITMAP_DIB_HEADER);
  stream.read(static_cast<char*>(header_pointer->get_data_section()), BITMAP_DIB_HEADER::SIZE);
  if (stream.gcount() < BITMAP_DIB_HEADER::SIZE)
    return nullptr;
  uint32_t header_size = header_pointer->get_header_size();
  header_pointer = header_pointer->parse_header();
  stream.seekg(BITMAP_DIB_HEADER::OFFSET, std::ios::beg);
  stream.read(static_cast<char*>(header_pointer->get_data_section()), header_size);
  if (stream.gcount() < header_size)
    return nullptr;
  return header_pointer;
}

void BITMAP_DIB_HEADER::write(std::ostream& stream) {
  stream.write(static_cast<char*>(this->get_data_section()), this->get_header_size());
}

std::ostream& operator<<(std::ostream& os, BITMAP_DIB_HEADER const& header) {
  os << "BITMAP_DIB_HEADER{"
     << "header_size=" << header.get_header_size() << ","
     << "height=" << header.get_height() << ","
     << "width=" << header.get_width() << ","
     << "color_planes=" << header.get_color_planes() << ","
     << "bit_per_pixel=" << header.get_bit_per_pixel() << ","
     << "compression=" << header.get_compression() << ","
     << "image_size=" << header.get_image_size() << ","
     << "horizontal_resolution=" << header.get_horizontal_resolution() << ","
     << "vertical_resolution=" << header.get_vertical_resolution() << ","
     << "color_palette=" << header.get_color_palette() << ","
     << "important_colors=" << header.get_important_colors() << "}";
  return os;
}

std::ostream& operator<<(std::ostream& os, BITMAP_FILE_HEADER const& header) {
  os << "BITMAP_FILE_HEADER{"
     << "valid=" << header.check_header() << ","
     << "identificator=" << header.get_identificator() << ","
     << "file_size=" << header.get_file_size() << ","
     << "pixel_storage_offset=" << header.get_pixel_storage_offset() << "}";
  return os;
}

std::unique_ptr<BITMAP_DIB_HEADER> BITMAP_DIB_HEADER::clone() const {
  std::unique_ptr<BITMAP_DIB_HEADER> new_header = this->parse_header();
  std::memcpy(new_header->get_data_section(), this->get_data_section(), this->get_header_size());
  return new_header;
}

std::unique_ptr<BITMAP_FILE_HEADER> BITMAP_FILE_HEADER::clone() const {
  std::unique_ptr<BITMAP_FILE_HEADER> new_header(new BITMAP_FILE_HEADER);
  std::memcpy(new_header->get_data_section(), this->get_data_section(), BITMAP_FILE_HEADER::SIZE);
  return new_header;
}

COLOR_WITH_ALPHA_BITMASK BITMAP_INFO_HEADER::get_color_bitmask() const {
  switch (this->get_bit_per_pixel()) {
    case 32:
    case 8:
    case 4:
    case 2:
    case 1:
      return {0b11111111000000000000000000000000, 0b00000000111111110000000000000000,
              0b00000000000000001111111100000000, 0b00000000000000000000000011111111};
    case 16:
      return {0b00000000000000001111100000000000, 0b00000000000000000000011111000000,
              0b00000000000000000000000000111110, 0b00000000000000000000000000000001};
    case 24:
      return {0b00000000111111110000000000000000, 0b00000000000000001111111100000000,
              0b00000000000000000000000011111111, 0b00000000000000000000000000000000};
    default:
      return {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
              0b00000000000000000000000000000000, 0b00000000000000000000000000000000};
  }
}

COLOR_WITH_ALPHA_BITMASK BITMAP_CORE_HEADER::get_color_bitmask() const {
  switch (this->get_bit_per_pixel()) {
    case 24:
    case 8:
    case 4:
    case 1:
      return {0b00000000111111110000000000000000, 0b00000000000000001111111100000000,
              0b00000000000000000000000011111111, 0b00000000000000000000000000000000};
    default:
      return {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
              0b00000000000000000000000000000000, 0b00000000000000000000000000000000};
  }
}