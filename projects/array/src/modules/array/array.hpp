#pragma once

#include <algorithm>
#include <initializer_list>
#include <stdexcept>

#include "../uglify.hpp"

template <typename T, int N>
class Array {
   public:
    Array(std::initializer_list<T> lst) {  // Do not touch.
        std::copy(lst.begin(), lst.end(), arr_);
    }

    T& front() {
        return this->arr_[0];
    }

    T& back() {
        return this->arr_[N - 1];
    }

    int size() {
        return N;
    }

    bool empty() {
        return N == 0;
    }

    T* data() {
        return this->arr_;
    }

    T& operator[](int i) {
        return this->arr_[i];
    }

    void swap(Array<T, N>& current) {
        char *a = (char*)this->arr_, *b = (char*)current.arr_;
        for (size_t i = 0; i < N * sizeof(T); i++) std::swap(a[i], b[i]);
    }

   private:
    T arr_[N];
};
