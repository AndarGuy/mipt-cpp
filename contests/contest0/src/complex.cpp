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

class Complex {
   public:
    double real;
    double imaginary;

    Complex(const Complex& complex) {
        real = complex.real;
        imaginary = complex.imaginary;
    }

    Complex(double _real = 0.0, double _imaginary = 0.0) {
        real = _real;
        imaginary = _imaginary;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Complex& number);

    friend bool operator==(const Complex& left, const Complex& right);
    friend bool operator!=(const Complex& left, const Complex& right);

    friend Complex operator+(const Complex& left, const Complex& right);
    friend Complex operator-(const Complex& left, const Complex& right);
    friend Complex operator*(const Complex& left, const Complex& right);
    friend Complex operator/(const Complex& left, const Complex& right);

    double abs() const;
};

double Complex::abs() const {
    return real * real + imaginary * imaginary;
}

Complex operator+(Complex const& left, Complex const& right) {
    return Complex(left.real + right.real, left.imaginary + right.imaginary);
}

Complex operator+(const Complex& left, int right) {
    return Complex(left.real + right, left.imaginary);
}

Complex operator-(Complex const& left, Complex const& right) {
    return Complex(left.real - right.real, left.imaginary - right.imaginary);
}

Complex operator*(Complex const& left, Complex const& right) {
    return Complex(left.real * right.real + left.imaginary * right.imaginary, left.real * right.imaginary + left.imaginary * right.real);
}

Complex operator/(Complex const& left, Complex const& right) {
    return left * Complex(right.real / right.abs(), -1 * right.imaginary / right.abs());
}

bool operator==(Complex const& left, Complex const& right) {
    return right.imaginary == left.imaginary && right.real == left.real;
}

bool operator!=(Complex const& left, Complex const& right) {
    return right.imaginary != left.imaginary || right.real != left.real;
}

std::ostream& operator<<(std::ostream& os, Complex const& complex) {
    std::cout << complex.real << ' ' << complex.imaginary << std::endl;
    return os;
}

int main() {
    Complex a(8, 2);
    Complex b(4, 1);
    std::cout << a / b << std::endl;
}