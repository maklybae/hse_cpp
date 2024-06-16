#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#define BIG_INTEGER_DIVISION_IMPLEMENTED

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <vector>

class BigIntegerOverflow : public std::runtime_error {
 public:
  BigIntegerOverflow() : std::runtime_error("BigIntegerOverflow") {
  }
};

class BigIntegerDivisionByZero : public std::runtime_error {
 public:
  BigIntegerDivisionByZero() : std::runtime_error("BigIntegerDivisionByZero") {
  }
};

class BigInteger {
 public:
  using DigitType = uint16_t;
  using DoubleDigitType = uint32_t;

 private:
  std::vector<DigitType> data_{};
  bool is_negative_{false};

  BigInteger& RemoveLeadingZeros();

 public:
  static constexpr DigitType kBase{10000};
  static constexpr size_t kCountDigitsBase{4};

  BigInteger() = default;
  BigInteger(int64_t);                                           // NOLINT
  BigInteger(const char*);                                       // NOLINT
  BigInteger(int num) : BigInteger(static_cast<int64_t>(num)) {  // NOLINT
  }

  bool IsNegative() const;
  BigInteger operator+() const;
  BigInteger operator-() const;
  BigInteger& operator+=(const BigInteger&);
  BigInteger& operator-=(const BigInteger&);
  BigInteger& operator*=(const BigInteger&);
  BigInteger& operator/=(const BigInteger&);
  BigInteger& operator%=(const BigInteger&);
  BigInteger& operator+=(int64_t);
  BigInteger& operator-=(int64_t);
  BigInteger& operator*=(int64_t);
  BigInteger& operator/=(int64_t);
  BigInteger& operator%=(int64_t);

  BigInteger& operator++();
  BigInteger& operator--();
  BigInteger operator++(int);
  BigInteger operator--(int);

  BigInteger& BaseMultiplication(size_t power);

  explicit operator bool();

  friend bool operator==(const BigInteger&, const BigInteger&);
  friend bool operator!=(const BigInteger&, const BigInteger&);
  friend bool operator<(const BigInteger&, const BigInteger&);
  friend bool operator>(const BigInteger&, const BigInteger&);
  friend bool operator<=(const BigInteger&, const BigInteger&);
  friend bool operator>=(const BigInteger&, const BigInteger&);

  friend BigInteger operator+(const BigInteger&, const BigInteger&);
  friend BigInteger operator-(const BigInteger&, const BigInteger&);
  friend BigInteger operator*(const BigInteger&, const BigInteger&);
  friend BigInteger operator/(const BigInteger&, const BigInteger&);
  friend BigInteger operator%(const BigInteger&, const BigInteger&);

  friend BigInteger operator+(int64_t, const BigInteger&);
  friend BigInteger operator-(int64_t, const BigInteger&);
  friend BigInteger operator*(int64_t, const BigInteger&);
  friend BigInteger operator/(int64_t, const BigInteger&);
  friend BigInteger operator%(int64_t, const BigInteger&);

  friend BigInteger operator+(const BigInteger&, int64_t);
  friend BigInteger operator-(const BigInteger&, int64_t);
  friend BigInteger operator*(const BigInteger&, int64_t);
  friend BigInteger operator/(const BigInteger&, int64_t);
  friend BigInteger operator%(const BigInteger&, int64_t);

  friend std::istream& operator>>(std::istream& is, BigInteger& value);
  friend std::ostream& operator<<(std::ostream& os, BigInteger value);
};

#endif