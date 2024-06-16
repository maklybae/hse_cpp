#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

int main() {
  std::string a{};

  std::unordered_map<std::string, int> count{};
  while (std::cin >> a) {
    ++count[a];
  }

  std::vector<std::pair<std::string, int>> to_sort(count.begin(), count.end());
  std::sort(to_sort.begin(), to_sort.end(), [](const auto& x, const auto& y) {
    if (x.second != y.second) {
      return x.second > y.second;
    }
    return x.first < y.first;
  });

  for (const auto& pair : to_sort) {
    std::cout << pair.first << '\n';
  }

  return 0;
}