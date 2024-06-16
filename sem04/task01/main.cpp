#include <iostream>

#include "rational.h"

int main() {
  Rational x = 5;          // дробь 5/1
  std::cout << x << '\n';  // вывод: 5
  x.SetDenominator(15);    // дробь 1/3 (5/15 сократилась)
  std::cout << x << '\n';  // вывод: 1/3
  std::cin >> x;  // ввод: 14/-6, дробь: -7/3 (общий множитель 2; знаменатель > 0)
  std::cout << x << '\n';
  x += Rational{6, -1};
  std::cout << x << '\n';
  auto y = x * Rational(1, 5);
  std::cout << y << '\n';
  y /= 5;
  std::cout << y << '\n';
  std::cout << (y == Rational{1, -3}) << '\n';
  std::cout << (Rational{4, 9} < 1) << '\n';
  std::cout << (Rational{1} == Rational{7});
  Rational{11, 0};

  // std::cout << x;
  // std::cout << x;
  // std::cout << x;
  // std::cout << x;
  // std::cout << x;
  // std::cout << x;
}