#ifndef DATE_H
#define DATE_H

class Date {
 private:
  int day_{};
  int month_{};
  int year_{};

 public:
  Date() = default;
  Date(int day, int month, int year) : day_{day}, month_{month}, year_{year} {
  }

  int GetDay() const;
  int GetMonth() const;
  int GetYear() const;
  int GetSumDays() const;

  Date& operator+=(int);
  Date& operator-=(int);
};

Date operator+(const Date&, int);
Date operator+(int, const Date&);
Date operator-(const Date&, int);
bool operator<(const Date&, const Date&);
bool operator>(const Date&, const Date&);
bool operator==(const Date&, const Date&);
bool operator!=(const Date&, const Date&);
bool operator<=(const Date&, const Date&);
bool operator>=(const Date&, const Date&);

#endif