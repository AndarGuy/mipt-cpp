#include "headers.hpp"

#include <iostream>

bool BITMAP_FILE_HEADER::check_header() {
    for (auto identificator : {IDENTIFICATOR_BM, IDENTIFICATOR_BA, IDENTIFICATOR_CI, IDENTIFICATOR_CP, IDENTIFICATOR_IC, IDENTIFICATOR_PT}) {
        if (this->identificator[0] == identificator[0] && this->identificator[1] == identificator[1])
            return true;
    }
    return false;
}

bool BITMAP_FILE_HEADER::check_size(uint32_t actual_size) {
    return this->file_size == actual_size;
}

std::unique_ptr<BITMAP_FILE_HEADER> BITMAP_FILE_HEADER::read_header(std::istream& stream) {
    stream.seekg(BITMAP_FILE_HEADER::OFFSET, std::ios::beg);
    std::unique_ptr<BITMAP_FILE_HEADER> header_pointer(new BITMAP_FILE_HEADER);
    stream.read((char*)header_pointer->identificator, BITMAP_FILE_HEADER::SIZE);
    std::cout << header_pointer->file_size << std::endl;
    if (stream.gcount() < BITMAP_FILE_HEADER::SIZE) return nullptr;
    return header_pointer;
}

std::unique_ptr<BITMAP_DIB_HEADER> BITMAP_DIB_HEADER::parse_header() {
    switch (this->get_header_size()) {
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

std::unique_ptr<BITMAP_DIB_HEADER> BITMAP_DIB_HEADER::read_header(std::istream& stream) {
    stream.seekg(BITMAP_DIB_HEADER::OFFSET, std::ios::beg);
    std::unique_ptr<BITMAP_DIB_HEADER> header_pointer(new BITMAP_DIB_HEADER);
    stream.read((char*)header_pointer.get(), BITMAP_DIB_HEADER::SIZE);
    if (stream.gcount() < BITMAP_DIB_HEADER::SIZE) return nullptr;
    uint32_t header_size = header_pointer->get_header_size();
    header_pointer = header_pointer->parse_header();
    stream.seekg(BITMAP_DIB_HEADER::OFFSET, std::ios::beg);
    stream.read((char*)header_pointer.get(), header_size);
    if (stream.gcount() < header_size) return nullptr;
    return header_pointer;
}