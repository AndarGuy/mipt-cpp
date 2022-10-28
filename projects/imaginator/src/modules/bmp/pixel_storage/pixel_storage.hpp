#include <cinttypes>
#include <cmath>

// **PIXEL STORAGE**

// ...............

class PixelStorage {
   public:
    static uint32_t calculate_row_size(int32_t image_width, uint16_t bits_per_pixel);
    static uint32_t calculate_pixel_array_size(int32_t image_heigth, uint32_t row_size);
};