#include "str.hpp"

String::String() : _string(nullptr), _capacity(0), _size(0) {
  // Default Constructor
}

String::~String() {
  delete[] _string;
}

String::String(const String& other) : String::String() {
  for (size_t i = 0; i < other.size(); i++) {
    push_back(other[i]);
  }
  _capacity = other.capacity();
}

String::String(unsigned int size, char filler) : String::String() {
  resize(size, filler);
}

String::String(const char* string, unsigned int slice) : String::String() {
  this->reserve(this->size() + slice);
  for (size_t i = 0; i < slice && string[i] != 0; i++) {
    push_back(string[i]);
  }
}

String::String(const char* string) : String::String() {
  for (size_t i = 0; string[i] != 0; i++) push_back(string[i]);
  shrink();
}

void String::reallocate(unsigned int new_capacity) {
  char* temp = new char[new_capacity + 1];
  for (size_t i = 0; i < std::min(size(), new_capacity); i++) {
    temp[i] = _string[i];
  }
  if (_string)
    delete[] _string;
  _string = temp;
  _capacity = new_capacity;
}

void String::reserve(unsigned int new_capacity) {
  if (_capacity + 1 > new_capacity)
    return;
  reallocate(new_capacity);
}

void String::shrink() {
  _capacity = size();
  reallocate(size());
}

char& String::front() const {
  return *_string;
}

char& String::back() const {
  return *(_string + size() - 1);
}

const char* String::cstring() const {
  _string[size()] = 0;
  return data();
}

const char* String::data() const {
  return _string;
}

unsigned int String::size() const {
  return _size;
}

unsigned int String::length() const {
  return _size;
}

unsigned int String::capacity() const {
  return _capacity;
}

bool String::empty() {
  return size() == 0;
}

void String::clear() {
  _size = 0;
}

void String::swap(String& other) {
  std::swap(_string, other._string);
  std::swap(_capacity, other._capacity);
  std::swap(_size, other._size);
}

std::ostream& operator<<(std::ostream& os, String const& string) {
  for (size_t i = 0; i < string.size(); i++) os << string[i];
  return os;
}

void String::pop_back() {
  _size--;
}

void String::push_back(char symbol) {
  if (size() + 2 > capacity())
    reserve(capacity() ? capacity() * EXPANSION_COEFFICIENT : 1);
  _string[size()] = symbol;
  _size++;
}

void String::resize(unsigned int new_size, char filler) {
  reserve(new_size);
  if (new_size > size())
    for (size_t i = 0; i < new_size - size(); i++) {
      operator[](size() + i) = filler;
    }
  _size = new_size;
}

String operator+(const String& left, const String& right) {
  String concat = left;
  return concat += right;
}

String& String::operator+=(const String& right) {
  this->reserve(this->size() + right.size());
  for (size_t i = 0; i < right.size(); i++) push_back(right[i]);
  return *this;
}

char& String::operator[](int index) {
  return _string[index];
}

const char& String::operator[](int index) const {
  return _string[index];
}

int operator<=>(const String& left, const String& right) {
  for (size_t i = 0; i < std::min(right.size(), left.size()); i++) {
    if (left[i] < right[i])
      return -1;
    else if (left[i] > right[i])
      return 1;
  }

  if (left.size() < right.size())
    return -1;
  else if (left.size() > right.size())
    return 1;

  return 0;
}

bool operator==(String const& left, String const& right) {
  if (left.size() != right.size())
    return false;
  for (size_t i = 0; i < left.size(); i++) {
    if (left[i] != right[i])
      return false;
  }
  return true;
}

String& String::operator=(const String& other) {
  if (this == &other)
    return *this;
  String new_string(other);
  new_string.swap(*this);
  return *this;
}