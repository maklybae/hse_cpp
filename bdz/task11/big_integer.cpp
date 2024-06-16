#include "big_integer.h"

#include <algorithm>
#include <charconv>
#include <cstdlib>
#include <iomanip>
#include <string>

// ----------------------------------------------------------------------------
// --------------------------------Constructors--------------------------------
// ----------------------------------------------------------------------------

BigInteger::BigInteger(int64_t num) : is_negative_{num < 0} {
  data_.reserve(8);
  num = std::abs(num);
  while (num != 0) {
    data_.push_back(static_cast<DigitType>(num % kBase));
    num /= kBase;
  }
}

BigInteger::BigInteger(const char* cstr_num) {
  std::string str_num{cstr_num};
  if (!str_num.empty()) {
    data_.reserve(str_num.length() / 4 + 1);
    if (str_num[0] == '-') {
      str_num.erase(0, 1);
      is_negative_ = true;
    }
    if (str_num[0] == '+') {
      str_num.erase(0, 1);
    }

    for (size_t i = 0; i < str_num.length(); i += kCountDigitsBase) {
      if (i + 4 > str_num.length()) {
        data_.push_back(static_cast<DigitType>(std::stoi(str_num.substr(0, str_num.length() - i))));
      } else {
        data_.push_back(static_cast<DigitType>(std::stoi(str_num.substr(str_num.length() - 4 - i, 4))));
      }
    }
    RemoveLeadingZeros();
  }
}

// ----------------------------------------------------------------------------
// -----------------------------------Helpers----------------------------------
// ----------------------------------------------------------------------------

BigInteger& BigInteger::RemoveLeadingZeros() {
  while (!data_.empty() && data_.back() == 0) {
    data_.pop_back();
  }

  if (data_.empty()) {
    is_negative_ = false;
  }
  return *this;
}

// Multiplication by exponential with power of base <=> shift of data array
BigInteger& BigInteger::BaseMultiplication(size_t power) {
  size_t prev_size = data_.size();
  data_.resize(prev_size + power);
  std::copy_backward(data_.begin(), data_.begin() + static_cast<int64_t>(prev_size), data_.end());
  std::fill(data_.begin(), data_.begin() + static_cast<int64_t>(power), 0);
  return *this;
}

BigInteger::operator bool() {
  return !data_.empty() && (data_.size() != 1 || data_[0] != 0);
}

bool BigInteger::IsNegative() const {
  return is_negative_;
}

BigInteger BigInteger::operator+() const {
  return *this;
}

BigInteger BigInteger::operator-() const {
  auto copy{*this};
  copy.is_negative_ = !is_negative_;
  return copy;
}

// ----------------------------------------------------------------------------
// ---------------------------Arithmetic operations----------------------------
// ----------------------------------------------------------------------------

BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs.is_negative_ && rhs.is_negative_) {
    return -((-lhs) + (-rhs));
  }
  if (lhs.is_negative_) {
    return rhs - (-lhs);
  }
  if (rhs.is_negative_) {
    return lhs - (-rhs);
  }

  // The only case positive + positive
  BigInteger res{};
  bool next_add = false;
  res.data_.reserve(std::max(lhs.data_.size(), rhs.data_.size()) + 1);
  for (size_t i = 0; i < std::max(lhs.data_.size(), rhs.data_.size()) || next_add; ++i) {
    res.data_.push_back((i < lhs.data_.size() ? lhs.data_[i] : 0) + (i < rhs.data_.size() ? rhs.data_[i] : 0) +
                        next_add);
    next_add = res.data_[i] >= BigInteger::kBase;
    if (next_add) {
      res.data_[i] -= BigInteger::kBase;
    }
  }

  return res;
}

BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs.is_negative_ && rhs.is_negative_) {
    return -rhs - (-lhs);
  }
  if (lhs.is_negative_) {
    return -(-lhs + rhs);
  }
  if (rhs.is_negative_) {
    return lhs + (-rhs);
  }

  // Case positive - positive
  if (lhs < rhs) {
    return -(rhs - lhs);
  }

  // Zero case
  if (rhs.data_.empty()) {
    return lhs;
  }

  // The only case y - x, where 0 < x < y
  BigInteger res{};
  bool next_add = false;
  res.data_.reserve(lhs.data_.size());
  for (size_t i = 0; i < lhs.data_.size(); ++i) {
    int tmp = lhs.data_[i] - (i < rhs.data_.size() ? rhs.data_[i] : 0) - next_add;
    next_add = tmp < 0;
    if (next_add) {
      tmp += BigInteger::kBase;
    }
    res.data_.push_back(static_cast<BigInteger::DigitType>(tmp));
  }

  res.RemoveLeadingZeros();
  return res;
}

BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs.data_.size() + rhs.data_.size() - 1 >= 7500) {
    throw BigIntegerOverflow{};
  }
  BigInteger res{};
  res.data_.resize(lhs.data_.size() + rhs.data_.size());
  for (size_t i = 0; i < lhs.data_.size(); ++i) {
    BigInteger::DigitType ost{};
    for (size_t j = 0; j < rhs.data_.size() || ost; ++j) {
      BigInteger::DoubleDigitType tmp{ost + res.data_[i + j] +
                                      static_cast<BigInteger::DoubleDigitType>(lhs.data_[i]) *
                                          (j < rhs.data_.size() ? rhs.data_[j] : 0)};
      res.data_[i + j] = static_cast<BigInteger::DigitType>(tmp % BigInteger::kBase);
      ost = static_cast<BigInteger::DigitType>(tmp / BigInteger::kBase);
    }
  }
  res.is_negative_ = (lhs.is_negative_) != (rhs.is_negative_);
  res.RemoveLeadingZeros();
  if (res.data_.size() >= 7500) {
    throw BigIntegerOverflow{};
  }
  return res;
}

BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs) {
  if (rhs == 0) {
    throw BigIntegerDivisionByZero{};
  }

  // Quotient
  BigInteger res{};
  res.data_.resize(lhs.data_.size());

  // Iteration dividend
  BigInteger current_dividend{};
  current_dividend.data_.reserve(lhs.data_.size());

  // Abs of divisor (rhs)
  BigInteger abs_divisor{rhs};
  abs_divisor.is_negative_ = false;

  for (int64_t i = static_cast<int64_t>(lhs.data_.size()) - 1; i >= 0; --i) {
    current_dividend.BaseMultiplication(1);
    current_dividend.data_[0] = lhs.data_[static_cast<size_t>(i)];
    // Zero reminder after previous iteration
    current_dividend.RemoveLeadingZeros();

    // Binary search to find greatest coefficient of divisor
    BigInteger::DigitType l_bound{0};
    BigInteger::DigitType r_bound{BigInteger::kBase};
    BigInteger::DigitType max_coefficient{0};
    while (l_bound <= r_bound) {
      BigInteger::DigitType middle = (l_bound + r_bound) / static_cast<BigInteger::DigitType>(2);
      BigInteger tmp{abs_divisor * middle};
      if (tmp <= current_dividend) {
        max_coefficient = middle;
        l_bound = middle + 1;
      } else {
        r_bound = middle - 1;
      }
    }

    res.data_[static_cast<size_t>(i)] = max_coefficient;
    current_dividend = current_dividend - abs_divisor * max_coefficient;
  }

  res.is_negative_ = lhs.is_negative_ != rhs.is_negative_;
  res.RemoveLeadingZeros();

  return res;
}

BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs) {
  if (rhs == 0) {
    throw BigIntegerDivisionByZero{};
  }

  return lhs - rhs * (lhs / rhs);
}

BigInteger operator+(int64_t lhs, const BigInteger& rhs) {
  return BigInteger{lhs} + rhs;
}

BigInteger operator-(int64_t lhs, const BigInteger& rhs) {
  return BigInteger{lhs} - rhs;
}

BigInteger operator*(int64_t lhs, const BigInteger& rhs) {
  return BigInteger{lhs} * rhs;
}

BigInteger operator/(int64_t lhs, const BigInteger& rhs) {
  return BigInteger{lhs} / rhs;
}

BigInteger operator%(int64_t lhs, const BigInteger& rhs) {
  return BigInteger{lhs} % rhs;
}

BigInteger operator+(const BigInteger& lhs, int64_t rhs) {
  return lhs + BigInteger{rhs};
}

BigInteger operator-(const BigInteger& lhs, int64_t rhs) {
  return lhs - BigInteger{rhs};
}

BigInteger operator*(const BigInteger& lhs, int64_t rhs) {
  return lhs * BigInteger{rhs};
}

BigInteger operator/(const BigInteger& lhs, int64_t rhs) {
  return lhs / BigInteger{rhs};
}

BigInteger operator%(const BigInteger& lhs, int64_t rhs) {
  return lhs % BigInteger{rhs};
}

// ----------------------------------------------------------------------------
// ---------------------------Compound Arithmetic------------------------------
// ----------------------------------------------------------------------------

BigInteger& BigInteger::operator+=(const BigInteger& other) {
  return *this = *this + other;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
  return *this = *this - other;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
  return *this = *this * other;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
  return *this = *this / other;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
  return *this = *this % other;
}

BigInteger& BigInteger::operator+=(int64_t other) {
  return *this = *this + BigInteger{other};
}

BigInteger& BigInteger::operator-=(int64_t other) {
  return *this = *this - BigInteger{other};
}

BigInteger& BigInteger::operator*=(int64_t other) {
  return *this = *this * BigInteger{other};
}

BigInteger& BigInteger::operator/=(int64_t other) {
  return *this = *this / BigInteger{other};
}

BigInteger& BigInteger::operator%=(int64_t other) {
  return *this = *this % BigInteger{other};
}

BigInteger& BigInteger::operator++() {
  return *this += 1ul;
}

BigInteger& BigInteger::operator--() {
  return *this -= 1ul;
}

BigInteger BigInteger::operator++(int) {
  auto copy = *this;
  ++(*this);
  return copy;
}

BigInteger BigInteger::operator--(int) {
  auto copy = *this;
  --(*this);
  return copy;
}

// ----------------------------------------------------------------------------
// ---------------------------Compare operations-------------------------------
// ----------------------------------------------------------------------------

bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs.is_negative_ != rhs.is_negative_) {
    return false;
  }

  // Check zero representation
  if ((lhs.data_.empty() && rhs.data_.size() == 1 && rhs.data_[0] == 0) ||
      (rhs.data_.empty() && lhs.data_.size() == 1 && lhs.data_[0] == 0)) {
    return true;
  }
  return std::equal(lhs.data_.begin(), lhs.data_.end(), rhs.data_.begin(), rhs.data_.end());
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs == rhs);
}

bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs.is_negative_ != rhs.is_negative_) {
    return lhs.is_negative_ > rhs.is_negative_;
  }

  // Check zero representation
  if ((lhs.data_.empty() && rhs.data_.size() == 1 && rhs.data_[0] == 0) ||
      (rhs.data_.empty() && lhs.data_.size() == 1 && lhs.data_[0] == 0)) {
    return false;
  }

  // Two negatives case
  if (lhs.is_negative_) {
    return -lhs > -rhs;
  }

  // Two positives case
  if (lhs.data_.size() != rhs.data_.size()) {
    return lhs.data_.size() < rhs.data_.size();
  }
  for (auto lhs_r_iter = lhs.data_.rbegin(), rhs_r_iter = rhs.data_.rbegin(); lhs_r_iter != lhs.data_.rend();
       ++lhs_r_iter, ++rhs_r_iter) {
    if (*lhs_r_iter != *rhs_r_iter) {
      return *lhs_r_iter < *rhs_r_iter;
    }
  }

  // Equal case
  return false;
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
  return lhs != rhs && !(lhs < rhs);
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs > rhs);
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs < rhs);
}

// ----------------------------------------------------------------------------
// -------------------------------------IO-------------------------------------
// ----------------------------------------------------------------------------

std::istream& operator>>(std::istream& is, BigInteger& value) {
  std::string input{};
  is >> input;
  value = BigInteger{input.c_str()};
  return is;
}

std::ostream& operator<<(std::ostream& os, BigInteger value) {
  if (value.data_.empty()) {
    os << 0;
  } else {
    if (value.is_negative_) {
      os << '-';
    }
    os << value.data_.back();
    char old_fill = os.fill('0');
    for (auto iter = value.data_.rbegin() + 1; iter != value.data_.rend(); ++iter) {
      os << std::setw(BigInteger::kCountDigitsBase) << *iter;
    }
    os.fill(old_fill);
  }
  return os;
}
