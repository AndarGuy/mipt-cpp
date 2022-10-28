#include <cinttypes>
#include <fstream>
#include <initializer_list>

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

// **HALFTONING ALGORITHMS**

// ...............

#define HALFTONING_ALGORITHM_NONE 0             // Most common
#define HALFTONING_ALGORITHM_ERROR_DIFFUSION 1  // Halftoning parameter 1 (offset 64) is the percentage of error damping. 100 indicates no damping. 0 indicates that errors are not diffused
#define HALFTONING_ALGORITHM_PANDA 2            // Halftoning parameters 1 and 2 (offsets 64 and 68, respectively) represent the X and Y dimensions, in pixels, respectively, of the halftoning pattern used
#define HALFTONING_ALGORITHM_SUPER_CIRCLE 3     // Halftoning parameters 1 and 2 (offsets 64 and 68, respectively) represent the X and Y dimensions, in pixels, respectively, of the halftoning pattern used

// **COLOR ENCODINGS**

// ...............

#define COLOR_ENCODING_RGB 0

// **HEADERS**

struct I_OFFSETED {
   public:
    virtual ~I_OFFSETED() {}
    virtual uint32_t get_offset() = 0;
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
struct __attribute__((packed)) BITMAP_FILE_HEADER : I_OFFSETED {
    static const uint32_t SIZE = 14;
    static const uint32_t OFFSET = 0x0;

   protected:
    int8_t identificator[2];
    uint32_t file_size;           // The size of the BMP file in bytes
    int16_t application_code[2];  // Reserved; actual value depends on the application that creates the image, if created manually can be 0
    uint32_t offset;              // The offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found.

   public:
    /// @brief Get the offset of the file header.
    /// @return Zero, as file header located at the very beginning of the file.
    uint32_t get_offset() override { return OFFSET; }

    /// @brief Check if header is a valid BMP header.
    /// @return True if header is valid, and false – otherwise.
    bool check_header();

    /// @brief The method checks if filesize in header agrees real filesize.
    /// @param real_size Real filesize.
    /// @return True if filesize in header equals real filesize, false – otherwise.
    bool check_size(uint32_t);

    /// @brief The method reads a BITMAP_FILE_HEADER from provided stream and returns it.
    /// @param stream Provided stream to read.
    /// @return Unique pointer to BITMAP_FILE_HEADER read from stream.
    static std::unique_ptr<BITMAP_FILE_HEADER> read_header(std::istream&);
};

class BITMAP_DIB_HEADER : I_OFFSETED {
    static const uint32_t OFFSET = 0xE;
    static const uint32_t SIZE = 4;

   private:
    std::unique_ptr<BITMAP_DIB_HEADER> parse_header();

   protected:
    uint32_t header_size;  // The size of this header

   public:
    BITMAP_DIB_HEADER() = default;

    uint32_t get_offset() { return OFFSET; }

    static std::unique_ptr<BITMAP_DIB_HEADER> read_header(std::istream&);

    uint32_t get_header_size() { return header_size; }
    virtual int32_t get_width() { return 0; }
    virtual int32_t get_height() { return 0; }
    virtual uint16_t get_color_planes() { return 1; }
    virtual uint16_t get_bit_per_pixel() { return 24; }

    virtual int32_t get_compression() { return COMPRESSION_BI_RGB; }
    virtual int32_t get_image_size() { return 0; }
    virtual int32_t get_horizontal_resolution() { return 0; }
    virtual int32_t get_vertical_resolution() { return 0; }
    virtual uint32_t get_color_palette() { return 0; }
    virtual uint32_t get_important_colors() { return 0; }

    virtual uint16_t get_units() { return 0; }
    virtual uint16_t get_padding() { return 0; }
    virtual uint16_t get_direction() { return 0; }
    virtual uint16_t get_halftoning_algorithm() { return HALFTONING_ALGORITHM_NONE; }
    virtual uint32_t get_halftoning_parameter1() { return 0; }
    virtual uint32_t get_halftoning_parameter2() { return 0; }
    virtual uint32_t get_color_encoding() { return COLOR_ENCODING_RGB; }
    virtual uint32_t get_application_identifier() { return 0; }
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
    int32_t get_width() override { return width; }
    int32_t get_height() override { return height; }
    uint16_t get_color_planes() override { return color_planes; }
    uint16_t get_bit_per_pixel() override { return bit_per_pixel; }
};

// Extended bitmap core header
struct __attribute__((packed)) BITMAP_INFO_HEADER : BITMAP_DIB_HEADER {
    static const uint32_t SIZE = 40;  // the size of this header, in bytes (40)

   protected:
    int32_t width;                  // the bitmap width in pixels (signed integer)
    int32_t height;                 // the bitmap height in pixels (signed integer)
    uint16_t color_planes;          // The number of color planes, must be 1
    uint16_t bit_per_pixel;         // The number of bits per pixel
    int32_t compression;            // the compression method being used.
    int32_t image_size;             // the image size. This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps.
    int32_t horizontal_resolution;  // the horizontal resolution of the image. (pixel per metre, signed integer)
    int32_t vertical_resolution;    // the vertical resolution of the image. (pixel per metre, signed integer)
    uint32_t color_palette;         // the number of colors in the color palette, or 0 to default to 2n
    uint32_t important_colors;      // the number of important colors used, or 0 when every color is important; generally ignored

   public:
    int32_t get_width() override { return width; }
    int32_t get_height() override { return height; }
    uint16_t get_color_planes() override { return color_planes; }
    uint16_t get_bit_per_pixel() override { return bit_per_pixel; }
    int32_t get_compression() override { return compression; }
    int32_t get_image_size() override { return image_size; }
    int32_t get_horizontal_resolution() override { return horizontal_resolution; }
    int32_t get_vertical_resolution() override { return vertical_resolution; }
    uint32_t get_color_palette() override { return color_palette; }
    uint32_t get_important_colors() override { return important_colors; }
};

struct __attribute__((packed)) BITMAP_INFO_HEADER2 : BITMAP_INFO_HEADER {
    static const uint32_t SIZE = 64;

   protected:
    uint16_t units;                   // An enumerated value specifying the units for the horizontal and vertical resolutions (offsets 38 and 42). The only defined value is 0, meaning pixels per metre
    uint16_t padding;                 // Padding. Ignored and should be zero
    uint16_t direction;               // An enumerated value indicating the direction in which the bits fill the bitmap. The only defined value is 0, meaning the origin is the lower-left corner. Bits fill from left-to-right, then bottom-to-top.
    uint16_t halftoning_algorithm;    // An enumerated value indicating a halftoning algorithm that should be used when rendering the image.
    uint32_t halftoning_parameter1;   // Halftoning parameter 1 (see below)
    uint32_t halftoning_parameter2;   // Halftoning parameter 2 (see below)
    uint32_t color_encoding;          // An enumerated value indicating the color encoding for each entry in the color table. The only defined value is 0, indicating RGB.
    uint32_t application_identifier;  // An application-defined identifier. Not used for image rendering

   public:
    uint16_t get_units() override { return units; }
    uint16_t get_padding() override { return padding; }
    uint16_t get_direction() override { return direction; }
    uint16_t get_halftoning_algorithm() override { return halftoning_algorithm; }
    uint32_t get_halftoning_parameter1() override { return halftoning_parameter1; }
    uint32_t get_halftoning_parameter2() override { return halftoning_parameter2; }
    uint32_t get_color_encoding() override { return color_encoding; }
    uint32_t get_application_identifier() override { return application_identifier; }
};

struct __attribute__((packed)) BITMAP_V4_HEADER : BITMAP_INFO_HEADER {
    static const uint32_t SIZE = 108;

   protected:
    COLOR_WITH_ALPHA_BITMASK color_bitmask;
    char color_space[24];
    COLOR_BITMASK color_gamma;

   public:
};