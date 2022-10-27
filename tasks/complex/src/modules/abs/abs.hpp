#include <cmath>

#include "../complex/complex.hpp"
#include "../uglify.hpp"

template <typename T>
T absolute(T number) {
    return number > 0 ? number : -number;
}

template <>
Complex absolute<Complex>(Complex number) {
    return sqrt(number.getReal() * number.getReal() + number.getImaginary() * number.getImaginary());
}
