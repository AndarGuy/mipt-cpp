#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

#define Abs absolute
#define GetRe getReal
#define GetIm getImaginary

class Complex {
 private:
  double real;
  double imaginary;

 public:
  Complex(const Complex& complex);
  Complex(double _real = 0.0, double _imaginary = 0.0);

  double getReal() const;
  double getImaginary() const;

  friend std::ostream& operator<<(std::ostream& os, Complex const& complex);

  friend bool operator==(Complex const& left, Complex const& right);
  friend bool operator!=(Complex const& left, Complex const& right);

  friend Complex operator+(const Complex& left, const Complex& right);
  friend Complex operator+(const Complex& left, int right);
  friend Complex operator-(const Complex& left, const Complex& right);
  friend Complex operator*(const Complex& left, const Complex& right);

  const Complex& operator=(const Complex& other);
  const Complex& operator+=(const Complex& right);
  const Complex& operator-=(const Complex& right);
  const Complex& operator*=(const Complex& right);

  const Complex operator+();
  const Complex operator-();
};
