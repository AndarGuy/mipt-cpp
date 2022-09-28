/*

C

Написать класс комплексных чисел C.

У класса должны быть доступны члены класса re и im, а так же метод double abs, который возвращает модуль комплексного числа.

Определить конструкторы:

1) от пары чисел типа double;

2) одного числа типа double (действительной части);

3) конструктор копирования - от одного комплексного числа типа C.

Определить для класса арифметические операции (+, -, *, /, ==, !=), а также операции между комплексными и действительными числами (в том числе и для случая, когда действительное число является левым операндом).

Определить оператор потокового вывода, комплексное число выводить в формате двух действительных чисел, разделённых пробелом (действительная часть вначале).

Функция main() находится в коде Заказчика, её вызывать НЕ надо

*/

#include <cmath>
#include <cstdlib>
#include <iostream>

class C {
   public:
    double re;
    double im;

    C(const C& complex) {
        re = complex.re;
        im = complex.im;
    }

    C(double _real = 0.0, double _imaginary = 0.0) {
        re = _real;
        im = _imaginary;
    }

    friend std::ostream& operator<<(std::ostream& stream, const C& number);

    friend bool operator==(const C& left, const C& right);
    friend bool operator!=(const C& left, const C& right);

    friend C operator+(const C& left, const C& right);
    friend C operator-(const C& left, const C& right);
    friend C operator*(const C& left, const C& right);
    friend C operator/(const C& left, const C& right);

    double abs() const;
};

double C::abs() const {
    return re * re + im * im;
}

C operator+(C const& left, C const& right) {
    return C(left.re + right.re, left.im + right.im);
}

C operator+(const C& left, int right) {
    return C(left.re + right, left.im);
}

C operator-(C const& left, C const& right) {
    return C(left.re - right.re, left.im - right.im);
}

C operator*(C const& left, C const& right) {
    return C(left.re * right.re + left.im * right.im, left.re * right.im + left.im * right.re);
}

C operator/(C const& left, C const& right) {
    return left * C(right.re / right.abs(), -1 * right.im / right.abs());
}

bool operator==(C const& left, C const& right) {
    return right.im == left.im && right.re == left.re;
}

bool operator!=(C const& left, C const& right) {
    return right.im != left.im || right.re != left.re;
}

std::ostream& operator<<(std::ostream& os, C const& complex) {
    std::cout << complex.re << ' ' << complex.im << std::endl;
    return os;
}

int main() {
    C a(8, 2);
    C b(4, 1);
    std::cout << a / b << std::endl;
}