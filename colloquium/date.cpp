#include "date.h"

Date operator+(const Date& date, int count_days) {
  return Date{((date.GetDay() - 1 + count_days) % 30 + 30) % 30 + 1,
              ((date.GetMonth() - 1 + (count_days % 360 + 360) % 360 / 30) % 12 + 1),
              (date.GetYear() + count_days / 360)};
}

Date operator+(int count_days, const Date& date) {
  return date + count_days;
}

Date operator-(const Date& date, int count_days) {
  return date + (-count_days);
}

bool operator<(const Date& x, const Date& y) {
  if (x.GetYear() != y.GetYear()) {
    return x.GetYear() < y.GetYear();
  }
  if (x.GetMonth() != y.GetMonth()) {
    return x.GetMonth() < y.GetMonth();
  }
  return x.GetDay() < y.GetDay();
}

bool operator==(const Date& x, const Date& y) {
  return x.GetDay() == y.GetDay() && x.GetMonth() == y.GetMonth() && x.GetYear() == y.GetYear();
}

bool operator!=(const Date& x, const Date& y) {
  return !(x == y);
}

bool operator>(const Date& x, const Date& y) {
  return x != y && !(x < y);
}

bool operator<=(const Date& x, const Date& y) {
  return !(x > y);
}

bool operator>=(const Date& x, const Date& y) {
  return !(x < y);
}

int Date::GetDay() const {
  return day_;
}

int Date::GetMonth() const {
  return month_;
}

int Date::GetYear() const {
  return year_;
}

int Date::GetSumDays() const {
  return day_ + month_ * 30 + year_ * 360;
}

Date& Date::operator+=(int count_days) {
  *this = *this + count_days;
  return *this;
}

Date& Date::operator-=(int count_days) {
  *this = *this - count_days;
  return *this;
}
