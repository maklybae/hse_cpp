#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n{};
  std::cin >> n;

  std::string first_word{};
  std::string second_word{};
  std::unordered_map<std::string, std::string> dict{};
  while (n--) {
    std::cin >> first_word >> second_word;

    dict[first_word] = second_word;
    dict[second_word] = first_word;
  }

  size_t m{};
  std::cin >> m;
  while (m--) {
    std::cin >> first_word;
    std::cout << dict[first_word] << '\n';
  }
  return 0;
}