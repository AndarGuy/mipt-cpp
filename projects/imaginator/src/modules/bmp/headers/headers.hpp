#pragma once

#include <cinttypes>
#include <fstream>
#include <initializer_list>
#include <string>
#include <memory>
#include <iostream>
#include <cstdint>
#include <cstring>

// **IDENTIFICATORS**

// ...............

#define IDENTIFICATOR_BM "BM"  // Windows 3.1x, 95, NT, ... etc.
#define IDENTIFICATOR_BA "BA"  // OS/2 struct bitmap array
#define IDENTIFICATOR_CI "CI"  // OS/2 struct color icon
#define IDENTIFICATOR_CP "CP"  // OS/2 const color pointer
#define IDENTIFICATOR_IC "IC"  // OS/2 struct icon
#define IDENTIFICATOR_PT "PT"  // OS/2 pointer

// **COMPRESSIONS**

// ...............

#define COMPRESSION_BI_RGB 0             // Most common
#define COMPRESSION_BI_RLE8 1            // Can be used only with 8-bit/pixel bitmaps
#define COMPRESSION_BI_RLE4 2            // Can be used only with 4-bit/pixel bitmaps
#define COMPRESSION_BI_BITFIELDS 3       // BITMAPV2INFOHEADER: RGB bit field masks, BITMAPV3INFOHEADER+: RGBA
#define COMPRESSION_BI_JPEG 4            // BITMAPV4INFOHEADER+: JPEG image for printing
#define COMPRESSION_BI_PNG 5             // BITMAPV4INFOHEADER+: PNG image for printing
#define COMPRESSION_BI_ALPHABITFIELDS 6  // only Windows CE 5.0 with .NET 4.0 or later
#define COMPRESSION_BI_CMYK 11           // only Windows Metafile CMYK
#define COMPRESSION_BI_CMYKRLE8 12       // only Windows Metafile CMYK
#define COMPRESSION_BI_CMYKRLE4 13       // only Windows Metafile CMYK

// **RGB TYPES**

#define RGB32 0
#define RGB24 1
#define RGB565 2
#define RGB555 3

// **HALFTONING ALGORITHMS**

// ...............

#define HALFTONING_ALGORITHM_NONE 0  // Most common
#define HALFTONING_ALGORITHM_ERROR_DIFFUSION \
  1  // Halftoning parameter 1 (offset 64) is the percentage of error damping. 100 indicates no damping. 0 indicates
     // that errors are not diffused
#define HALFTONING_ALGORITHM_PANDA \
  2  // Halftoning parameters 1 and 2 (offsets 64 and 68, respectively) represent the X and Y dimensions, in pixels,
     // respectively, of the halftoning pattern used
#define HALFTONING_ALGORITHM_SUPER_CIRCLE \
  3  // Halftoning parameters 1 and 2 (offsets 64 and 68, respectively) represent the X and Y dimensions, in pixels,
     // respectively, of the halftoning pattern used

// **COLOR ENCODINGS**

// ...............

#define COLOR_ENCODING_RGB 0

// **HEADERS**

struct I_OFFSETED {
 public:
  virtual ~I_OFFSETED() {
  }
  virtual uint32_t get_offset() = 0;
};

struct I_DATA_SECTION {
 protected:
  virtual void* get_data_section() const = 0;
};

// ...............

struct __attribute__((packed)) COLOR_BITMASK {
  uint32_t red;
  uint32_t green;
  uint32_t blue;
};

struct __attribute__((packed)) COLOR_WITH_ALPHA_BITMASK : COLOR_BITMASK {
  uint32_t alpha;
};

// ...............

// To store general information about the bitmap image file
struct __attribute__((packed)) BITMAP_FILE_HEADER : I_OFFSETED, I_DATA_SECTION {
  static const uint32_t SIZE = 14;

 private:
  static const uint32_t OFFSET = 0x0;

 protected:
  int8_t identificator[2];
  uint32_t file_size;           // The size of the BMP file in bytes
  int16_t application_code[2];  // Reserved; actual value depends on the application that creates the image, if created
                                // manually can be 0
  uint32_t
      offset;  // The offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found.

 public:
  /// @brief Get the offset of the file header.
  /// @return Zero, as file header located at the very beginning of the file.
  uint32_t get_offset() override {
    return OFFSET;
  }

  void* get_data_section() const override {
    return (void*)&identificator[0];
  }

  /// @brief Check if header is a valid BMP header.
  /// @return True if header is valid, and false – otherwise.
  bool check_header() const;

  /// @brief The method checks if filesize in header agrees real filesize.
  /// @param real_size Real filesize.
  /// @return True if filesize in header equals real filesize, false – otherwise.
  bool check_size(uint32_t) const;

  /// @brief The method reads a BITMAP_FILE_HEADER from provided stream and returns it.
  /// @param stream Provided stream to read.
  /// @return Unique pointer to BITMAP_FILE_HEADER read from stream.
  static std::unique_ptr<BITMAP_FILE_HEADER> read(std::istream&);

  void write(std::ostream&);

  std::string get_identificator() const {
    return std::string({static_cast<char>(identificator[0]), static_cast<char>(identificator[1])});
  }

  void set_identificator(int8_t identificator[2]) {
    this->identificator[0] = identificator[0];
    this->identificator[1] = identificator[1];
  }

  uint32_t get_file_size() const {
    return file_size;
  }

  void set_file_size(uint32_t file_size) {
    this->file_size = file_size;
  }

  uint32_t get_pixel_storage_offset() const {
    return offset;
  }

  void set_pixel_storage_offset(uint32_t offset) {
    this->offset = offset;
  }

  /// @brief Operator `<<`.
  /// @param os Stream to use.
  /// @param header Header to output.
  /// @return Used stream.
  friend std::ostream& operator<<(std::ostream& os, BITMAP_FILE_HEADER const& header);

  /// @brief Clone operator.
  std::unique_ptr<BITMAP_FILE_HEADER> clone() const;
};

class BITMAP_DIB_HEADER : I_OFFSETED, I_DATA_SECTION {
  static const uint32_t OFFSET = 0xE;
  static const uint32_t SIZE = 4;

 private:
  std::unique_ptr<BITMAP_DIB_HEADER> parse_header() const;
  static std::unique_ptr<BITMAP_DIB_HEADER> parse_header(uint32_t header_size);

 protected:
  uint32_t header_size;  // The size of this header

 public:
  BITMAP_DIB_HEADER() = default;

  BITMAP_DIB_HEADER(uint32_t header_size) : header_size(header_size) {
    // Empty
  }

  uint32_t get_offset() {
    return OFFSET;
  }

  void* get_data_section() const override {
    return (void*)&header_size;
  }

  static std::unique_ptr<BITMAP_DIB_HEADER> read(std::istream&);

  void write(std::ostream&);

  uint32_t get_header_size() const {
    return header_size;
  }
  virtual int32_t get_width() const {
    return 0;
  }
  virtual void set_width(int32_t) {
    return;
  }
  virtual int32_t get_height() const {
    return 0;
  }
  virtual void set_height(int32_t) {
    return;
  }
  virtual uint16_t get_color_planes() const {
    return 1;
  }
  virtual void set_color_planes(uint16_t) {
    return;
  }
  virtual uint16_t get_bit_per_pixel() const {
    return 24;
  }
  virtual void set_bit_per_pixel(uint16_t) {
    return;
  }
  virtual int32_t get_compression() const {
    return COMPRESSION_BI_RGB;
  }
  virtual int32_t get_image_size() const {
    return 0;
  }
  virtual int32_t get_horizontal_resolution() const {
    return 0;
  }
  virtual int32_t get_vertical_resolution() const {
    return 0;
  }
  virtual uint32_t get_color_palette() const {
    return 0;
  }
  virtual uint32_t get_important_colors() const {
    return 0;
  }

  virtual uint16_t get_units() const {
    return 0;
  }
  virtual uint16_t get_padding() const {
    return 0;
  }
  virtual uint16_t get_direction() const {
    return 0;
  }
  virtual uint16_t get_halftoning_algorithm() const {
    return HALFTONING_ALGORITHM_NONE;
  }
  virtual uint32_t get_halftoning_parameter1() const {
    return 0;
  }
  virtual uint32_t get_halftoning_parameter2() const {
    return 0;
  }
  virtual uint32_t get_color_encoding() const {
    return COLOR_ENCODING_RGB;
  }
  virtual uint32_t get_application_identifier() const {
    return 0;
  }
  virtual COLOR_WITH_ALPHA_BITMASK get_color_bitmask() const {
    return {0b00000000000000000000000011111111, 0b00000000000000001111111100000000, 0b00000000111111110000000000000000,
            0b11111111000000000000000000000000};
  }
  virtual char* get_color_space() const {
    return NULL;
  }
  virtual COLOR_BITMASK get_color_gamma() const {
    return {0, 0, 0};
  }

  /// @brief Operator `<<`.
  /// @param os Stream to use.
  /// @param header Header to output.
  /// @return Used stream.
  friend std::ostream& operator<<(std::ostream& os, BITMAP_DIB_HEADER const& header);

  /// @brief Clone operator.
  std::unique_ptr<BITMAP_DIB_HEADER> clone() const;
};

// Immediately follows the Bitmap file header
struct __attribute__((packed)) BITMAP_CORE_HEADER : BITMAP_DIB_HEADER {
  static const uint32_t SIZE = 12;

 protected:
  uint16_t width;          // The bitmap width in pixels (unsigned 16-bit)
  uint16_t height;         // The bitmap height in pixels (unsigned 16-bit)
  uint16_t color_planes;   // The number of color planes, must be 1
  uint16_t bit_per_pixel;  // The number of bits per pixel

 public:
  int32_t get_width() const override {
    return width;
  }
  int32_t get_height() const override {
    return height;
  }

  uint16_t get_color_planes() const override {
    return color_planes;
  }
  uint16_t get_bit_per_pixel() const override {
    return bit_per_pixel;
  }

  void set_width(int32_t width) override {
    this->width = width;
  }
  void set_height(int32_t height) override {
    this->height = height;
  }
  void set_color_planes(uint16_t color_planes) override {
    this->color_planes = color_planes;
  }
  void set_bit_per_pixel(uint16_t bit_per_pixel) override {
    this->bit_per_pixel = bit_per_pixel;
  }

  COLOR_WITH_ALPHA_BITMASK get_color_bitmask() const override;
};

// Extended bitmap core header
struct __attribute__((packed)) BITMAP_INFO_HEADER : BITMAP_DIB_HEADER {
  static const uint32_t SIZE = 40;  // the size of this header, in bytes (40)

 protected:
  int32_t width;           // the bitmap width in pixels (signed integer)
  int32_t height;          // the bitmap height in pixels (signed integer)
  uint16_t color_planes;   // The number of color planes, must be 1
  uint16_t bit_per_pixel;  // The number of bits per pixel
  int32_t compression;     // the compression method being used.
  int32_t image_size;      // the image size. This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB
                           // bitmaps.
  int32_t horizontal_resolution;  // the horizontal resolution of the image. (pixel per metre, signed integer)
  int32_t vertical_resolution;    // the vertical resolution of the image. (pixel per metre, signed integer)
  uint32_t color_palette;         // the number of colors in the color palette, or 0 to default to 2n
  uint32_t
      important_colors;  // the number of important colors used, or 0 when every color is important; generally ignored

 public:
  int32_t get_width() const override {
    return width;
  }
  int32_t get_height() const override {
    return height;
  }
  uint16_t get_color_planes() const override {
    return color_planes;
  }
  uint16_t get_bit_per_pixel() const override {
    return bit_per_pixel;
  }
  int32_t get_compression() const override {
    return compression;
  }
  int32_t get_image_size() const override {
    return image_size;
  }
  int32_t get_horizontal_resolution() const override {
    return horizontal_resolution;
  }
  int32_t get_vertical_resolution() const override {
    return vertical_resolution;
  }
  uint32_t get_color_palette() const override {
    return color_palette;
  }
  uint32_t get_important_colors() const override {
    return important_colors;
  }

  void set_width(int32_t width) override {
    this->width = width;
  }
  void set_height(int32_t height) override {
    this->height = height;
  }
  void set_color_planes(uint16_t color_planes) override {
    this->color_planes = color_planes;
  }
  void set_bit_per_pixel(uint16_t bit_per_pixel) override {
    this->bit_per_pixel = bit_per_pixel;
  }

  COLOR_WITH_ALPHA_BITMASK get_color_bitmask() const override;
};

struct __attribute__((packed)) BITMAP_INFO_HEADER2 : BITMAP_INFO_HEADER {
  static const uint32_t SIZE = 64;

 protected:
  uint16_t units;    // An enumerated value specifying the units for the horizontal and vertical resolutions (offsets 38
                     // and 42). The only defined value is 0, meaning pixels per metre
  uint16_t padding;  // Padding. Ignored and should be zero
  uint16_t direction;  // An enumerated value indicating the direction in which the bits fill the bitmap. The only
                       // defined value is 0, meaning the origin is the lower-left corner. Bits fill from
                       // left-to-right, then bottom-to-top.
  uint16_t halftoning_algorithm;   // An enumerated value indicating a halftoning algorithm that should be used when
                                   // rendering the image.
  uint32_t halftoning_parameter1;  // Halftoning parameter 1 (see below)
  uint32_t halftoning_parameter2;  // Halftoning parameter 2 (see below)
  uint32_t color_encoding;  // An enumerated value indicating the color encoding for each entry in the color table.
                            // The only defined value is 0, indicating RGB.
  uint32_t application_identifier;  // An application-defined identifier. Not used for image rendering

 public:
  uint16_t get_units() const override {
    return units;
  }
  uint16_t get_padding() const override {
    return padding;
  }
  uint16_t get_direction() const override {
    return direction;
  }
  uint16_t get_halftoning_algorithm() const override {
    return halftoning_algorithm;
  }
  uint32_t get_halftoning_parameter1() const override {
    return halftoning_parameter1;
  }
  uint32_t get_halftoning_parameter2() const override {
    return halftoning_parameter2;
  }
  uint32_t get_color_encoding() const override {
    return color_encoding;
  }
  uint32_t get_application_identifier() const override {
    return application_identifier;
  }
};

struct __attribute__((packed)) BITMAP_V4_HEADER : BITMAP_INFO_HEADER {
  static const uint32_t SIZE = 108;

 protected:
  COLOR_WITH_ALPHA_BITMASK color_bitmask;
  char color_space[24];
  COLOR_BITMASK color_gamma;

 public:
  COLOR_WITH_ALPHA_BITMASK get_color_bitmask() const override {
    return color_bitmask;
  }

  char* get_color_space() const override {
    return (char*)color_space;
  }

  COLOR_BITMASK get_color_gamma() const override {
    return color_gamma;
  }
};