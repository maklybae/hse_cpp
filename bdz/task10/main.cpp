#include <iostream>
#include <string>
#include <vector>

int main() {
  size_t n{};
  std::cin >> n;

  std::vector<std::string> passwords(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> passwords[i];
  }

  int counter{};
  for (size_t i = 0; i < n - 1; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      counter += (passwords[i].find(passwords[j]) != std::string::npos);
      counter += (passwords[j].find(passwords[i]) != std::string::npos);
    }
  }
  std::cout << counter << '\n';
}