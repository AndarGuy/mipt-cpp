#include "pixel_storage.hpp"

uint32_t PIXEL_MATRIX::calculate_row_size(int32_t image_width, uint16_t bits_per_pixel) {
  return std::ceil(((double)bits_per_pixel) * ((double)image_width) / 32) * 4;
}

uint32_t PIXEL_MATRIX::calculate_pixel_array_size(int32_t image_heigth, uint32_t row_size) {
  return row_size * std::abs(image_heigth);
}

std::unique_ptr<PIXEL_MATRIX> PIXEL_MATRIX::clone(const BITMAP_FILE_HEADER* file_header,
                                                  const BITMAP_DIB_HEADER* dib_header) const {
  std::unique_ptr<PIXEL_MATRIX> bitmap(new PIXEL_MATRIX(file_header, dib_header));
  bitmap->storage = storage;
  return bitmap;
}

std::unique_ptr<PIXEL_MATRIX> PIXEL_MATRIX::read(std::istream& stream, const BITMAP_FILE_HEADER* file_header,
                                                 const BITMAP_DIB_HEADER* dib_header) {
  uint32_t row_size = PIXEL_MATRIX::calculate_row_size(dib_header->get_width(), dib_header->get_bit_per_pixel());

  PIXEL_MATRIX* bitmap = new PIXEL_MATRIX(file_header, dib_header);
  stream.seekg(file_header->get_pixel_storage_offset(), std::ios::beg);

  bitmap->storage.resize(dib_header->get_height(), std::vector<uint32_t>(row_size / sizeof(uint32_t) + 1));
  for (int i = 0; i < dib_header->get_height(); i++) stream.read((char*)bitmap->storage[i].data(), row_size);

  return std::unique_ptr<PIXEL_MATRIX>(bitmap);
}

void PIXEL_MATRIX::write(std::ostream& stream) {
  uint32_t row_size =
      PIXEL_MATRIX::calculate_row_size(this->dib_header->get_width(), this->dib_header->get_bit_per_pixel());
  for (auto row : this->storage) stream.write((char*)row.data(), row_size);
}

std::ostream& operator<<(std::ostream& os, PIXEL const& pixel) {
  os << "PIXEL{"
     << "red=" << pixel.get_red() << ","
     << "green=" << pixel.get_green() << ","
     << "blue=" << pixel.get_blue() << ","
     << "alpha=" << pixel.get_alpha() << "}";
  return os;
}

void LINKED_PIXEL::set_masked(uint32_t value, uint32_t mask) {
  int shift = mask ? __builtin_ctz(mask) : 0;
  value = value << shift;
  value = value & mask;
  uint32_t data = this->data();
  data = data & ~mask;
  data = data | value;
  this->bitset->save_chunk(this->x, data);
}

uint32_t LINKED_PIXEL::data() const {
  return this->bitset->get_chunk(this->x);
}

uint32_t LINKED_PIXEL::get_masked(uint32_t mask) const {
  int shift = mask ? __builtin_ctz(mask) : 0;
  return (this->bitset->get_chunk(this->x) & mask) >> shift;
}

uint32_t PIXEL_ROW::get_chunk(size_t x) const {
  size_t bit = x * this->instance->dib_header->get_bit_per_pixel();
  size_t block = bit / (sizeof(uint32_t) * 8), start = bit % (sizeof(uint32_t) * 8);
  uint32_t chunk = storage[block] >> start;
  int32_t bit_remain = this->instance->dib_header->get_bit_per_pixel() - (sizeof(uint32_t) * 8 - start);
  if (bit_remain > 0)
    chunk |= storage[++block] << (this->instance->dib_header->get_bit_per_pixel() - bit_remain);
  return chunk;
}

void PIXEL_ROW::save_chunk(size_t x, uint32_t chunk) {
  size_t bit = x * this->instance->dib_header->get_bit_per_pixel();
  size_t block = bit / (sizeof(uint32_t) * 8), start = bit % (sizeof(uint32_t) * 8),
         end = std::min(sizeof(uint32_t) * 8, start + this->instance->dib_header->get_bit_per_pixel());
  uint32_t mask = ((1UL << start) - 1) ^ ((1UL << end) - 1);
  storage[block] = storage[block] & ~mask;
  storage[block] = storage[block] | ((chunk << start) & mask);
  int32_t bit_remain = this->instance->dib_header->get_bit_per_pixel() - (sizeof(uint32_t) * 8 - start);
  if (bit_remain > 0) {
    block++;
    mask = (1UL << bit_remain) - 1;
    storage[block] = storage[block] & ~mask;
    storage[block] =
        storage[block] | ((chunk >> (this->instance->dib_header->get_bit_per_pixel() - bit_remain)) & mask);
  }
}

LINKED_PIXEL PIXEL_ROW::operator[](size_t x) const {
  return this->get_pixel(x);
}

LINKED_PIXEL PIXEL_ROW::get_pixel(size_t x) const {
  return LINKED_PIXEL(const_cast<PIXEL_ROW*>(this), x);
}

PIXEL_ROW::PIXEL_ROW(std::vector<uint32_t>& storage, const PIXEL_MATRIX* instance) noexcept
    : storage(storage), instance(instance) {
}

uint32_t LINKED_PIXEL::get_red() const {
  return this->get_masked(this->bitset->instance->dib_header->get_color_bitmask().red);
}

uint32_t LINKED_PIXEL::get_green() const {
  return this->get_masked(this->bitset->instance->dib_header->get_color_bitmask().green);
}

uint32_t LINKED_PIXEL::get_blue() const {
  return this->get_masked(this->bitset->instance->dib_header->get_color_bitmask().blue);
}

uint32_t LINKED_PIXEL::get_alpha() const {
  return this->get_masked(this->bitset->instance->dib_header->get_color_bitmask().alpha);
}

void LINKED_PIXEL::set_red(uint32_t value) {
  return this->set_masked(value, this->bitset->instance->dib_header->get_color_bitmask().red);
}

void LINKED_PIXEL::set_green(uint32_t value) {
  return this->set_masked(value, this->bitset->instance->dib_header->get_color_bitmask().green);
}

void LINKED_PIXEL::set_blue(uint32_t value) {
  return this->set_masked(value, this->bitset->instance->dib_header->get_color_bitmask().blue);
}

void LINKED_PIXEL::set_alpha(uint32_t value) {
  return this->set_masked(value, this->bitset->instance->dib_header->get_color_bitmask().alpha);
}

LINKED_PIXEL PIXEL_ROW::Iterator::operator*() {
  return bitset->get_pixel(item);
}

PIXEL_ROW::Iterator PIXEL_ROW::begin() {
  return Iterator(this, 0);
}

PIXEL_ROW::Iterator PIXEL_ROW::end() {
  return Iterator(this, instance->dib_header->get_width());
}

PIXEL_ROW::Iterator PIXEL_ROW::Iterator::operator++() {
  item++;
  return *this;
}

bool PIXEL_ROW::Iterator::operator==(const Iterator& rhs) {
  return item == rhs.item;
}

PIXEL& PIXEL::operator=(std::tuple<uint32_t, uint32_t, uint32_t> tuple) {
  set_red(std::get<0>(tuple));
  set_green(std::get<1>(tuple));
  set_blue(std::get<2>(tuple));
  set_alpha(0);
  return *this;
}

PIXEL& PIXEL::operator=(uint32_t array[3]) {
  set_red(array[0]);
  set_green(array[1]);
  set_blue(array[2]);
  set_alpha(0);
  return *this;
}

bool PIXEL::operator==(const PIXEL& other) {
  return get_red() == other.get_red() && get_green() == other.get_green() && get_blue() == other.get_blue() &&
         get_alpha() == other.get_alpha();
}

LINKED_PIXEL& LINKED_PIXEL::operator=(const PIXEL& pixel) {
  set_red(pixel.get_red());
  set_green(pixel.get_green());
  set_blue(pixel.get_blue());
  set_alpha(pixel.get_alpha());
  return *this;
}

LINKED_PIXEL& LINKED_PIXEL::operator=(const LINKED_PIXEL& pixel) {
  set_red(pixel.get_red());
  set_green(pixel.get_green());
  set_blue(pixel.get_blue());
  set_alpha(pixel.get_alpha());
  return *this;
}

int32_t PIXEL_MATRIX::resize(size_t height, size_t width) {
  uint32_t row_size = PIXEL_MATRIX::calculate_row_size(height, width);
  this->storage.resize(height);
  for (size_t i = 0; i < height; i++) this->storage[i].resize(row_size / sizeof(uint32_t) + 1);

  size_t new_size = row_size * height,
         old_size = PIXEL_MATRIX::calculate_row_size(height, width) * this->dib_header->get_height();

  return new_size - old_size;
}