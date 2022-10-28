#include "headers.hpp"

bool FileHeader::check_header() {
    for (auto identificator : {IDENTIFICATOR_BM, IDENTIFICATOR_BA, IDENTIFICATOR_CI, IDENTIFICATOR_CP, IDENTIFICATOR_IC, IDENTIFICATOR_PT}) {
        if (this->identificator[0] == identificator[0] && this->identificator[1] == identificator[1])
            return true;
    }
    return false;
}

bool FileHeader::check_size(uint32_t actual_size) {
    return this->file_size == actual_size;
}

std::unique_ptr<FileHeader> FileHeader::read_header(std::istream& stream) {
    stream.seekg(OFFSET_FILE_HEADER, std::ios::beg);
    std::unique_ptr<FileHeader> header_pointer(new FileHeader);
    stream.read((char*)header_pointer.get(), sizeof(FileHeader));
    if (stream.gcount() < sizeof(FileHeader)) return nullptr;
    return header_pointer;
}

std::unique_ptr<DIBHeader> DIBHeader::parse_header() {
    switch (this->get_header_size()) {
        case sizeof(BITMAP_CORE_HEADER):
            return std::unique_ptr<BITMAP_CORE_HEADER>(new BITMAP_CORE_HEADER);
        case sizeof(BITMAP_INFO_HEADER):
            return std::unique_ptr<BITMAP_INFO_HEADER>(new BITMAP_INFO_HEADER);
        case sizeof(BITMAP_INFO_HEADER2):
            return std::unique_ptr<BITMAP_INFO_HEADER2>(new BITMAP_INFO_HEADER2);
        default:
            return nullptr;
    }
}

std::unique_ptr<DIBHeader> DIBHeader::read_header(std::istream& stream) {
    stream.seekg(OFFSET_DIB_HEADER, std::ios::beg);
    std::unique_ptr<DIBHeader> header_pointer(new DIBHeader);
    stream.read((char*)header_pointer.get(), sizeof(DIBHeader));
    if (stream.gcount() < sizeof(DIBHeader)) return nullptr;
    uint32_t header_size = header_pointer->get_header_size();
    header_pointer = header_pointer->parse_header();
    stream.seekg(OFFSET_DIB_HEADER, std::ios::beg);
    stream.read((char*)header_pointer.get(), header_size);
    if (stream.gcount() < header_size) return nullptr;
    return header_pointer;
}