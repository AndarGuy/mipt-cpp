#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "../src/modules/bmp/bmp.hpp"

#define EXAMPLE_PATH "/home/andarguy/courserepo2/Projects/Imaginator/examples/"

TEST_CASE("The most significant header.") {
  std::ifstream image;
  image.open(EXAMPLE_PATH "blue.bmp", std::ios::binary);

  SECTION("Extracting image properties.") {
    std::unique_ptr<BITMAP_FILE_HEADER> header = BITMAP_FILE_HEADER::read(image);
    REQUIRE(header->check_header());
    REQUIRE(header->get_file_size() == 86454);
    REQUIRE(header->get_pixel_storage_offset() == 54);
    REQUIRE(header->get_identificator() == "BM");
  }
  SECTION("Getting the feedback about invalid image.") {
    std::ifstream not_image;
    not_image.open(EXAMPLE_PATH "invalid.bmp", std::ios::binary);
    std::unique_ptr<BITMAP_FILE_HEADER> header = BITMAP_FILE_HEADER::read(not_image);
    REQUIRE(!header->check_header());
  }
}

TEST_CASE("The second header.") {
  std::ifstream image;
  image.open(EXAMPLE_PATH "blue.bmp", std::ios::binary);

  SECTION("Extracting image properties.") {
    std::unique_ptr<BITMAP_DIB_HEADER> dib_header = BITMAP_DIB_HEADER::read(image);
    REQUIRE(dib_header->get_header_size() == BITMAP_INFO_HEADER::SIZE);
    REQUIRE(dib_header->get_height() == 144);
    REQUIRE(dib_header->get_width() == 200);
    REQUIRE(dib_header->get_color_planes() == 1);
    REQUIRE(dib_header->get_bit_per_pixel() == 24);
  }
}

TEST_CASE("Pixel storage.") {
  std::ifstream image;
  image.open(EXAMPLE_PATH "blue.bmp", std::ios::binary);
  std::unique_ptr<BITMAP_FILE_HEADER> file_header = BITMAP_FILE_HEADER::read(image);
  std::unique_ptr<BITMAP_DIB_HEADER> dib_header = BITMAP_DIB_HEADER::read(image);
  std::unique_ptr<PIXEL_MATRIX> pixel_storage = PIXEL_MATRIX::read(image, file_header.get(), dib_header.get());

  SECTION("Extracting image properties.") {
    REQUIRE(pixel_storage->get_capacity() == 144);
    REQUIRE(pixel_storage->get_line(128)[128] == PIXEL{0, 3, 255});
  }
}