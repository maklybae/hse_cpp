#include <iostream>

#include "task04.h"

int main() {
  int a[]{1, 2, 2, 3, 3, 4, 2, 5, 6};
  auto res = IsSortedUntil(a, a + 9);
  std::cout << (res == a + 6);
  return 0;
}