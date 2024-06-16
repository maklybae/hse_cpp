#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

#include "rational_division_by_zero.h"

class Rational {
 private:
  int numerator_{0};
  int denominator_{1};

  void Reduce();

 public:
  Rational() = default;
  Rational(int num) : numerator_{num} {};  // NOLINT
  Rational(int num, int den) : numerator_{num}, denominator_{den} {
    if (den == 0) {
      throw RationalDivisionByZero{};
    }
    Reduce();
  }

  int GetNumerator() const {
    return numerator_;
  }
  Rational& SetNumerator(int num);

  int GetDenominator() const {
    return denominator_;
  }
  Rational& SetDenominator(int den);

  Rational operator+() const;
  Rational operator-() const;
  Rational& operator+=(const Rational& second);
  Rational& operator-=(const Rational& second);
  Rational& operator*=(const Rational& second);
  Rational& operator/=(const Rational& second);
  Rational& operator++();
  Rational& operator--();
  Rational operator++(int);
  Rational operator--(int);

  friend std::istream& operator>>(std::istream& in, Rational& rational);
};

Rational operator+(const Rational& rational1, const Rational& rational2);
Rational operator-(const Rational& rational1, const Rational& rational2);
Rational operator*(const Rational& rational1, const Rational& rational2);
Rational operator/(const Rational& rational1, const Rational& rational2);
std::ostream& operator<<(std::ostream& out, const Rational& rational);
bool operator==(const Rational& rational1, const Rational& rational2);
bool operator!=(const Rational& rational1, const Rational& rational2);
bool operator<(const Rational& rational1, const Rational& rational2);
bool operator>(const Rational& rational1, const Rational& rational2);
bool operator<=(const Rational& rational1, const Rational& rational2);
bool operator>=(const Rational& rational1, const Rational& rational2);

#endif