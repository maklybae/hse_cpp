#include <iostream>

bool IsDigit(char c) {
  return '0' <= c && c <= '9';
}

int main() {
  char c;
  std::cin >> c;

  std::cout << (IsDigit(c) ? "yes" : "no");

  return 0;
}