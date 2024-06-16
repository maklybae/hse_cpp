#include <iostream>

void PrintReverse(int counter) {
  int x;
  std::cin >> x;
  if (--counter) {
    PrintReverse(counter);
  }
  std::cout << x << ' ';
}

int main() {
  int n;
  std::cin >> n;
  PrintReverse(n);
  std::cout << '\n';
  return 0;
}