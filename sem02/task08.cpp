#include <cmath>
#include <iomanip>
#include <iostream>

double GetLength(int64_t x1, int64_t y1, int64_t x2, int64_t y2) {
  return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
  int64_t x1;
  int64_t y1;
  int64_t x2;
  int64_t y2;
  int64_t x3;
  int64_t y3;
  std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

  std::cout << std::fixed << std::setprecision(6)
            << GetLength(x1, y1, x2, y2) + GetLength(x2, y2, x3, y3) + GetLength(x3, y3, x1, y1);

  return 0;
}