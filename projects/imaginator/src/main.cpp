#include <iostream>

#include "modules/bmp/headers/headers.hpp"

int main() {
    std::ifstream stream;
    stream.open("../examples/BLU.BMP", std::ios::binary);
    std::unique_ptr<BITMAP_FILE_HEADER> header = BITMAP_FILE_HEADER::read_header(stream);
    // std::cout << header->check_header() << std::endl;
    return 0;
}