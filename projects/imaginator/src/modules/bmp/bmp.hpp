#include <cinttypes>
#include <string>

#include "exceptions/exceptions.hpp"
#include "headers/headers.hpp"

// **COLOR TABLE**

// ...............

// NOT IMPLEMENTED YET

// **PIXEL STORAGE**

// ...............

class PixelStorage {
   public:
    static uint32_t calculate_row_size(int32_t image_width, uint16_t bits_per_pixel);
    static uint32_t calculate_pixel_array_size(int32_t image_heigth, uint32_t row_size);
};

// **BITMAP DATA**

// ...............

class Bitmap {
   private:
    std::unique_ptr<FileHeader> file_header;
    std::unique_ptr<DIBHeader> dib_header;
    std::fstream file_stream;

   public:
    // Constructor by default.
    Bitmap() = default;

    // // Copy constructor.
    // Bitmap(const Bitmap&) noexcept;

    // // Open bitmap from file.
    // Bitmap(std::string) noexcept;

    // Read bitmap from stream.
    Bitmap(std::fstream);
};