#include <cstdlib>
#include <iostream>
#include <string>

int main() {
  std::string input;
  std::cin >> input;

  int cur = 0;
  int to_delete = 0;
  for (char c : input) {
    if (c == '(') {
      ++cur;
    } else if (c == ')') {
      if (cur > 0) {
        --cur;
      } else {
        ++to_delete;
      }
    }
  }

  std::cout << to_delete + std::abs(cur);
  return 0;
}