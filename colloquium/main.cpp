#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>

#include "date.h"

int main() {
  // Сперва вводистя заданная дата
  int d{};
  int m{};
  int y{};
  std::cin >> d >> m >> y;
  Date fixed_date{d, m, y};

  // Вводится количество дат для добавления в set
  size_t n{};
  std::cin >> n;

  std::set<Date> dates{};
  for (size_t i = 0; i < n; ++i) {
    std::cin >> d >> m >> y;
    dates.emplace(d, m, y);
  }

  std::cout << "Элементы std::set\n";
  for (const auto& date : dates) {
    std::cout << date.GetDay() << ' ' << date.GetMonth() << ' ' << date.GetYear() << '\n';
  }

  std::vector<Date> dates_to_sort(dates.begin(), dates.end());
  std::sort(dates_to_sort.begin(), dates_to_sort.end(), [fixed_date](const Date& x, const Date& y) {
    return std::abs(fixed_date.GetSumDays() - x.GetSumDays()) < std::abs(fixed_date.GetSumDays() - y.GetSumDays());
  });

  std::cout << "Элементы после сортировки\n";
  for (const auto& date : dates_to_sort) {
    std::cout << date.GetDay() << ' ' << date.GetMonth() << ' ' << date.GetYear() << '\n';
  }
  return 0;
}