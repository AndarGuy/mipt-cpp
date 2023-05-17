#pragma once

#include <cinttypes>
#include <cmath>
#include <memory>
#include <vector>

#include "../headers/headers.hpp"

class PIXEL;
class LINKED_PIXEL;

class PIXEL_ROW {
 public:
  class Iterator {
   public:
    Iterator(const PIXEL_ROW* bitset, size_t item) : item(item), bitset(bitset) {
      // Constructor initialized through list.
    }

    Iterator operator++();

    LINKED_PIXEL operator*();

    bool operator==(const Iterator& rhs);

   private:
    size_t item;
    const PIXEL_ROW* bitset;
  };

 private:
  std::vector<uint32_t>& storage;
  const class PIXEL_MATRIX* instance;

 public:
  /// @brief Constructor
  /// @param capacity The number of bits need to be saved.
  PIXEL_ROW(std::vector<uint32_t>& storage, const PIXEL_MATRIX* instance) noexcept;

  /// @brief The function returns a pointer to the storage.
  /// @return A pointer to the storage.
  uint32_t* get_storage() {
    return storage.data();
  }

  /// @brief The function loads and return the chunk from PIXEL_ROW storage.
  /// @param x The number of chunk.
  /// @return The chunk.
  uint32_t get_chunk(size_t x) const;

  /// @brief The funtion saves the chunk into PIXEL_ROW storage.
  /// @param x The number of chunk.
  /// @param chunk The chunk.
  void save_chunk(size_t x, uint32_t chunk);

  /// @brief Operator[] for getting chunk as LINKED_PIXEL.
  /// @param x The number of chunk.
  /// @return The LINKED_PIXEL.
  LINKED_PIXEL operator[](size_t x) const;

  /// @brief Function gets a chunk as a LINKED_PIXEL.
  /// @param x The number of chunk.
  /// @return The LINKED_PIXEL.
  LINKED_PIXEL get_pixel(size_t x) const;

  Iterator begin();

  Iterator end();

  /// @brief Made LINKED_PIXEL class friendly to give access to private fields e.g instance.
  friend class LINKED_PIXEL;
};

class PIXEL {
 private:
  uint32_t red = 0, green = 0, blue = 0, alpha = 0;

 public:
  PIXEL() = default;

  PIXEL(uint32_t gray) : red(gray), green(gray), blue(gray), alpha(0) {
    // Constructor initialized through list.
  }

  PIXEL(uint32_t red, uint32_t green, uint32_t blue) : red(red), green(green), blue(blue), alpha(0) {
    // Constructor initialized through list.
  }

  PIXEL(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha)
      : red(red), green(green), blue(blue), alpha(alpha) {
    // Constructor initialized through list.
  }

  /// @brief Get the RED value of the PIXEL.
  /// @return The RED value
  virtual uint32_t get_red() const {
    return red;
  }

  /// @brief Get the GREEN value of the PIXEL.
  /// @return The GREEN value
  virtual uint32_t get_green() const {
    return green;
  }

  /// @brief Get the BLUE value of the PIXEL.
  /// @return The BLUE value
  virtual uint32_t get_blue() const {
    return blue;
  }

  /// @brief Get the ALPHA value of the PIXEL.
  /// @return The ALPHA value
  virtual uint32_t get_alpha() const {
    return alpha;
  }

  virtual void set_red(uint32_t value) {
    this->red = value;
  }

  virtual void set_green(uint32_t value) {
    this->green = value;
  }

  virtual void set_blue(uint32_t value) {
    this->blue = value;
  }

  virtual void set_alpha(uint32_t value) {
    this->alpha = value;
  }

  void set_rgb(uint32_t red, uint32_t green, uint32_t blue) {
    set_red(red);
    set_green(green);
    set_blue(blue);
    set_alpha(UINT32_MAX);
  }

  void set_rgba(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) {
    set_red(red);
    set_green(green);
    set_blue(blue);
    set_alpha(alpha);
  }

  bool is_grayscale() const {
    return get_red() == get_green() && get_green() == get_blue();
  }

  friend std::ostream& operator<<(std::ostream& os, PIXEL const& pixel);

  PIXEL& operator=(std::tuple<uint32_t, uint32_t, uint32_t> tuple);

  PIXEL& operator=(uint32_t array[3]);

  bool operator==(const PIXEL& other);

  void set(size_t index, uint32_t value) {
    switch (index) {
      case 0:
        return set_red(value);
      case 1:
        return set_green(value);
      case 2:
        return set_blue(value);
      case 3:
        return set_alpha(value);
    }
  }

  int32_t get(size_t index) {
    switch (index) {
      case 0:
        return get_red();
      case 1:
        return get_green();
      case 2:
        return get_blue();
      case 3:
        return get_alpha();
      default:
        return -1;
    }
  }

  std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> as_tuple() {
    return {get_red(), get_green(), get_blue(), get_alpha()};
  }
};

template <>
struct std::tuple_size<PIXEL> : std::integral_constant<std::size_t, 4> {};

template <std::size_t N>
struct std::tuple_element<N, PIXEL> {
  using type = uint32_t;
};

/// @brief Structure for storing pixels.
class LINKED_PIXEL : public PIXEL {
 private:
  PIXEL_ROW* bitset;
  size_t x;

 private:
  /// @brief Set the value to data using mask.
  /// @param value The value to set.
  /// @param mask The mask to use.
  void set_masked(uint32_t value, uint32_t mask);

  /// @brief Get the value of data using mask.
  /// @param mask The mask to use.
  /// @return Requested value.
  uint32_t get_masked(uint32_t mask) const;

  uint32_t data() const;

 public:
  LINKED_PIXEL(PIXEL_ROW* bitset, size_t x) : bitset(bitset), x(x) {
    // Initialized through list.
  }

  /// @brief Get the RED value of the LINKED_PIXEL.
  /// @return The RED value
  uint32_t get_red() const override;

  /// @brief Get the GREEN value of the LINKED_PIXEL.
  /// @return The GREEN value
  uint32_t get_green() const override;

  /// @brief Get the BLUE value of the LINKED_PIXEL.
  /// @return The BLUE value
  uint32_t get_blue() const override;

  /// @brief Get the ALPHA value of the LINKED_PIXEL.
  /// @return The ALPHA value
  uint32_t get_alpha() const override;

  void set_red(uint32_t value) override;

  void set_green(uint32_t value) override;

  void set_blue(uint32_t value) override;

  void set_alpha(uint32_t value) override;

  LINKED_PIXEL& operator=(const PIXEL&);

  LINKED_PIXEL& operator=(const LINKED_PIXEL&);
};

// **PIXEL STORAGE**

// ...............

class PIXEL_MATRIX {
 private:
  const BITMAP_FILE_HEADER* file_header;
  const BITMAP_DIB_HEADER* dib_header;

  std::vector<std::vector<uint32_t>> storage;

 public:
  class Iterator {
   public:
    Iterator(size_t line, PIXEL_MATRIX* instance) : line(line), instance(instance) {
      // Constructor initialized through list.
    }

    Iterator operator++() {
      line++;
      return *this;
    }

    PIXEL_ROW operator*() {
      return instance->get_line(line);
    }

    bool operator==(const Iterator& rhs) {
      return line == rhs.line;
    }

   private:
    size_t line;
    PIXEL_MATRIX* instance;
  };

 public:
  /// @brief Default constructor.
  PIXEL_MATRIX(const BITMAP_FILE_HEADER* file_header, const BITMAP_DIB_HEADER* dib_header)
      : file_header(file_header), dib_header(dib_header) {
    // Initialized through list.
  }

  static uint32_t calculate_row_size(int32_t image_width, uint16_t bits_per_pixel);
  static uint32_t calculate_pixel_array_size(int32_t image_heigth, uint32_t row_size);

  /// @brief Read PIXEL_STORAGE in provided stream.
  /// @param stream The stream to read PIXEL_STORAGE in.
  /// @param file_header The FILE_HEADER of file.
  /// @param dib_header The DIB_HEADER of file.
  /// @return The pointer to a PIXEL_STORAGE.
  static std::unique_ptr<PIXEL_MATRIX> read(std::istream& stream, const BITMAP_FILE_HEADER* file_header,
                                            const BITMAP_DIB_HEADER* dib_header);

  /// @brief Write PIXEL_STORAGE into provided stream.
  /// @param stream The stream to write PIXEL_STORAGE in.
  /// @param pixel_storage The painter to PIXEL_STORAGE.
  void write(std::ostream& stream);

  /// @brief Clone operator.
  /// @return A pointer to a cloned object.
  std::unique_ptr<PIXEL_MATRIX> clone(const BITMAP_FILE_HEADER* file_header, const BITMAP_DIB_HEADER* dib_header) const;

  /// @brief Get common number of presented pixels.
  /// @return A number of pixels.
  size_t get_capacity() const {
    return storage.size();
  }

  /// @brief Get PIXEL_ROW line of an Image.
  /// @param x Number of a line.
  /// @return PIXEL_ROW line.
  PIXEL_ROW get_line(int x) {
    return PIXEL_ROW(storage[storage.size() - x - 1], this);
  }

  /// @brief Get vector storage.
  /// @return Link to vector.
  std::vector<std::vector<uint32_t>>& get_storage() {
    return storage;
  }

  int32_t resize(size_t height, size_t width);

  /// @brief Function for supporting iterating.
  /// @return Iterator of PIXEL_ROW.
  Iterator begin() {
    return Iterator(0, this);
  }

  /// @brief Function for supporting iterating.
  /// @return Iterator of PIXEL_ROW.
  Iterator end() {
    return Iterator(this->dib_header->get_height(), this);
  }

  friend class PIXEL_ROW;
  friend class LINKED_PIXEL;
};