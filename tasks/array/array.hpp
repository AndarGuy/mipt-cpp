#pragma once

#include <algorithm>
#include <initializer_list>

#define Front front
#define Back back
#define Size size
#define Empty empty
#define Data data
#define Swap swap

template <typename T, int N>
class Array {
 public:
  Array(std::initializer_list<T> lst) {  // Do not touch.
    std::copy(lst.begin(), lst.end(), storage);
  }

  const T& front() const {
    return this->storage[0];
  }

  T& front() {
    return this->storage[0];
  }

  T& back() {
    return this->storage[N - 1];
  }

  const T& back() const {
    return this->storage[N - 1];
  }

  int size() const {
    return N;
  }

  bool empty() const {
    return N == 0;
  }

  const T* data() const {
    return this->storage;
  }

  T* data() {
    return this->storage;
  }

  T& operator[](int i) {
    return this->storage[i];
  }

  const T& operator[](int i) const {
    return this->storage[i];
  }

  void swap(Array<T, N>& current) {
    char *a = (char*)this->storage, *b = (char*)current.storage;
    for (size_t i = 0; i < N * sizeof(T); i++) std::swap(a[i], b[i]);
  }

 private:
  T storage[N];
};
