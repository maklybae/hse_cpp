#include <iostream>

int Gcd(int a, int b) {
  while (a > 0 && b > 0) {
    if (a > b) {
      a %= b;
    } else {
      b %= a;
    }
  }
  return a + b;
}

int main() {
  int n;
  std::cin >> n;

  int current;
  int previous;
  std::cin >> previous;
  --n;
  while (n--) {
    std::cin >> current;
    previous = Gcd(previous, current);
  }
  std::cout << previous << '\n';
  return 0;
}