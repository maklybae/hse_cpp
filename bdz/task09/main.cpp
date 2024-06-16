#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  std::unordered_map<std::string, int> dict{};
  std::string input{};
  while (std::cin >> input) {
    std::cout << dict[input]++ << ' ';
  }
  return 0;
}