
#include "complex.hpp"
#include <cmath>

template <typename T>
T absolute(T number) {
  return number > 0 ? number : -number;
}

template <>
Complex absolute<Complex>(Complex number) {
  return sqrt(number.getReal() * number.getReal() + number.getImaginary() * number.getImaginary());
}
