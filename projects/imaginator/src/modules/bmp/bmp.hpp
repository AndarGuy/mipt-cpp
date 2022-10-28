#include <cinttypes>
#include <string>

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
    std::unique_ptr<PixelStorage> pixel_storage;
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