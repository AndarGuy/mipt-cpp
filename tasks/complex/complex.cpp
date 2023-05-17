#include "complex.hpp"

Complex::Complex(const Complex& complex) {
  this->real = complex.real;
  this->imaginary = complex.imaginary;
}

Complex::Complex(double _real, double _imaginary) {
  this->real = _real;
  this->imaginary = _imaginary;
}

double Complex::getReal() const {
  return this->real;
}

double Complex::getImaginary() const {
  return this->imaginary;
}

std::ostream& operator<<(std::ostream& os, Complex const& complex) {
  std::cout << complex.getReal() << ' ' << complex.getImaginary() << std::endl;
  return os;
}

bool operator==(Complex const& left, Complex const& right) {
  return right.imaginary == left.imaginary && right.real == left.real;
}
bool operator!=(Complex const& left, Complex const& right) {
  return right.imaginary != left.imaginary || right.real != left.real;
}

Complex operator+(const Complex& left, const Complex& right) {
  return Complex(left.real + right.real, left.imaginary + right.imaginary);
}
Complex operator-(const Complex& left, const Complex& right) {
  return Complex(left.real - right.real, left.imaginary - right.imaginary);
}
Complex operator*(const Complex& left, const Complex& right) {
  return Complex(left.real * right.real - left.imaginary * right.imaginary,
                 left.real * right.imaginary + left.imaginary * right.real);
}

const Complex& Complex::operator=(const Complex& other) {
  this->real = other.real;
  this->imaginary = other.imaginary;
  return *this;
}

const Complex& Complex::operator+=(const Complex& right) {
  this->imaginary += right.getImaginary();
  this->real += right.getReal();
  return *this;
}
const Complex& Complex::operator-=(const Complex& right) {
  this->imaginary -= right.getImaginary();
  this->real -= right.getReal();
  return *this;
}
const Complex& Complex::operator*=(const Complex& right) {
  double imaginary = this->getReal() * right.getImaginary() + this->getImaginary() * right.getReal();
  double real = this->getReal() * right.getReal() - this->getImaginary() * right.getImaginary();
  this->imaginary = imaginary;
  this->real = real;
  return *this;
}

const Complex Complex::operator+() {
  return *this;
}
const Complex Complex::operator-() {
  return Complex(-this->real, -this->imaginary);
}
