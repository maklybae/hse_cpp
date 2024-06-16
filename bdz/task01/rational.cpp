#include "rational.h"

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>

#include "rational_division_by_zero.h"

void Rational::Reduce() {
  int gcd = std::gcd(numerator_, denominator_);
  bool is_negative = (numerator_ > 0) != (denominator_ > 0);

  numerator_ = std::abs(numerator_) / gcd * (is_negative ? -1 : 1);
  denominator_ = std::abs(denominator_) / gcd;
}
Rational& Rational::SetNumerator(int num) {
  numerator_ = num;
  Reduce();
  return *this;
}
Rational& Rational::SetDenominator(int den) {
  if (den == 0) {
    throw RationalDivisionByZero{};
  }
  denominator_ = den;
  Reduce();
  return *this;
}

Rational Rational::operator+() const {
  return *this;
}
Rational Rational::operator-() const {
  return {-GetNumerator(), GetDenominator()};
}

Rational& Rational::operator+=(const Rational& second) {
  int denominator_gcd = std::gcd(GetDenominator(), second.GetDenominator());
  numerator_ = GetNumerator() * (second.GetDenominator() / denominator_gcd) +
               second.GetNumerator() * (GetDenominator() / denominator_gcd);
  denominator_ = GetDenominator() * (second.GetDenominator() / denominator_gcd);
  Reduce();
  return *this;
}
Rational& Rational::operator-=(const Rational& second) {
  return (*this) += (-second);
}
Rational& Rational::operator*=(const Rational& second) {
  numerator_ = GetNumerator() * second.GetNumerator();
  denominator_ = GetDenominator() * second.GetDenominator();
  Reduce();
  return *this;
}
Rational& Rational::operator/=(const Rational& second) {
  if (second.GetNumerator() == 0) {
    throw RationalDivisionByZero{};
  }
  numerator_ = GetNumerator() * second.GetDenominator();
  denominator_ = GetDenominator() * second.GetNumerator();
  Reduce();
  return *this;
}

Rational operator+(const Rational& rational1, const Rational& rational2) {
  Rational result = rational1;
  result += rational2;
  return result;
}
Rational operator-(const Rational& rational1, const Rational& rational2) {
  Rational result = rational1;
  result -= rational2;
  return result;
}
Rational operator*(const Rational& rational1, const Rational& rational2) {
  Rational result = rational1;
  result *= rational2;
  return result;
}
Rational operator/(const Rational& rational1, const Rational& rational2) {
  Rational result = rational1;
  result /= rational2;
  return result;
}

Rational& Rational::operator++() {
  return (*this) += 1;
}
Rational& Rational::operator--() {
  return (*this) -= 1;
}
Rational Rational::operator++(int) {
  Rational result = *this;
  ++(*this);
  return result;
}
Rational Rational::operator--(int) {
  Rational result = *this;
  --(*this);
  return result;
}

std::ostream& operator<<(std::ostream& out, const Rational& rational) {
  if (rational.GetDenominator() == 1) {
    out << rational.GetNumerator();
  } else {
    out << rational.GetNumerator() << '/' << rational.GetDenominator();
  }
  return out;
}
std::istream& operator>>(std::istream& in, Rational& rational) {
  std::string input;
  in >> input;
  size_t delimiter_pos = input.find('/');
  if (delimiter_pos == std::string::npos) {
    rational.numerator_ = std::stoi(input);
    rational.denominator_ = 1;
  } else {
    int num = std::stoi(input.substr(0, delimiter_pos));
    int den = std::stoi(input.substr(delimiter_pos + 1, input.size() - 1 - delimiter_pos));
    if (den == 0) {
      throw RationalDivisionByZero{};
    }

    rational.numerator_ = num;
    rational.denominator_ = den;
    rational.Reduce();
  }

  return in;
}

bool operator==(const Rational& rational1, const Rational& rational2) {
  return rational1.GetNumerator() == rational2.GetNumerator() &&
         rational1.GetDenominator() == rational2.GetDenominator();
}
bool operator!=(const Rational& rational1, const Rational& rational2) {
  return !(rational1 == rational2);
}

bool operator<(const Rational& rational1, const Rational& rational2) {
  return static_cast<int64_t>(rational1.GetNumerator()) * rational2.GetDenominator() <
         static_cast<int64_t>(rational1.GetDenominator()) * rational2.GetNumerator();
}
bool operator>(const Rational& rational1, const Rational& rational2) {
  return rational2 < rational1;
}

bool operator<=(const Rational& rational1, const Rational& rational2) {
  return !(rational1 > rational2);
}

bool operator>=(const Rational& rational1, const Rational& rational2) {
  return !(rational1 < rational2);
}
