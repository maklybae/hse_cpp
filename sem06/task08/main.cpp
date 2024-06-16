#include <cstdint>
#include <iostream>
#include <map>
#include <string>

int main() {
  std::map<std::string, std::map<std::string, int64_t>> db{};

  std::string name{};
  while (std::cin >> name) {
    std::string item{};
    std::cin >> item;
    int64_t count{};
    std::cin >> count;
    db[name][item] += count;
  }

  for (const auto& buyer : db) {
    std::cout << buyer.first << ":\n";
    for (const auto& item : buyer.second) {
      std::cout << item.first << ' ' << item.second << '\n';
    }
  }
}