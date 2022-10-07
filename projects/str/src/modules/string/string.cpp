#include "string.hpp"

String::String() {
    this->_string = nullptr;
    this->_capacity = 0;
    this->_size = 0;
}

String::~String() {
    delete this->_string;
}

String::String(const String& other) : String::String() {
    *this = other;
}

String::String(unsigned int size, char filler) : String::String() {
    this->resize(size, filler);
}

String::String(const char* string, unsigned int slice) : String::String() {
    for (size_t i = 0; i < slice && string[i] != 0; i++) {
        this->push_back(string[i]);
    }
}

String::String(const char* string) : String::String() {
    for (size_t i = 0; string[i] != 0; i++) this->push_back(string[i]);
    this->shrink();
}

void String::reserve(unsigned int new_capacity) {
    if (this->_capacity + 1 > new_capacity) return;
    char* temp = new char[new_capacity];
    for (size_t i = 0; i < this->size(); i++) {
        temp[i] = this->_string[i];
    }
    this->_string = temp;
    this->_capacity = new_capacity;
}

void String::shrink() {
    this->_capacity = this->_size;
}

char& String::front() const {
    return *this->_string;
}

char& String::back() const {
    return *(this->_string + this->size() - 1);
}

const char* String::cstring() const {
    this->_string[this->size()] = 0;
    return this->data();
}

const char* String::data() const {
    return this->_string;
}

unsigned int String::size() const {
    return this->_size;
}

unsigned int String::length() const {
    return this->_size;
}

unsigned int String::capacity() const {
    return this->_capacity;
}

bool String::empty() {
    return this->size() == 0;
}

void String::clear() {
    this->_size = 0;
}

void String::swap(String& other) {
    std::swap(this->_string, other._string);
    std::swap(this->_capacity, other._capacity);
    std::swap(this->_size, other._size);
}

std::ostream& operator<<(std::ostream& os, String const& string) {
    for (size_t i = 0; i < string.size(); i++) os << string[i];
    return os;
}

char String::pop_back() {
    assert(this->size() > 0);
    char popped = this->back();
    this->_size--;
    return popped;
}

void String::push_back(char symbol) {
    if (this->size() + 2 > this->capacity()) this->reserve(this->capacity() ? this->capacity() * this->EXPANSION_COEFFICIENT : 1);
    this->_string[this->size()] = symbol;
    this->_size++;
}

void String::resize(unsigned int new_size, char filler) {
    this->reserve(new_size);
    if (new_size > this->size())
        for (size_t i = 0; i < new_size - this->size(); i++) {
            this->operator[](this->size() + i) = filler;
        }
    this->_size = new_size;
}

String operator+(const String& left, const String& right) {
    String concat = left;
    for (size_t i = 0; i < right.size(); i++) concat.push_back(right[i]);
    return concat;
}

String& String::operator+=(const String& right) {
    for (size_t i = 0; i < right.size(); i++) this->push_back(right[i]);
    return *this;
}

char& String::operator[](int index) {
    return this->_string[index];
}

const char& String::operator[](int index) const {
    return this->_string[index];
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
    if (left.size() != right.size()) return false;
    for (size_t i = 0; i < left.size(); i++) {
        if (left[i] != right[i]) return false;
    }
    return true;
}

bool operator!=(String const& left, String const& right) {
    return !(left == right);
}

String& String::operator=(const String& other) {
    if (*this == other) return *this;

    this->_size = 0;
    for (size_t i = 0; i < other.size(); i++) {
        this->push_back(other[i]);
    }
    this->_capacity = other.capacity();

    return *this;
}