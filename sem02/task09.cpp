#include <cmath>
#include <iostream>

bool IsPrime(int x) {
  for (int i = 2; i < static_cast<int>(std::sqrt(x)) + 1; ++i) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int x;
  std::cin >> x;

  std::cout << (IsPrime(x) ? "prime" : "composite");
  return 0;
}