#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  size_t n{};
  std::cin >> n;

  std::unordered_map<std::string, int> clients{};

  while (n--) {
    int request{};
    std::cin >> request;

    std::string name{};
    std::cin >> name;

    if (request == 1) {
      int sum{};
      std::cin >> sum;

      clients[name] += sum;
    } else {
      auto iterator = clients.find(name);
      if (iterator == clients.end()) {
        std::cout << "ERROR\n";
      } else {
        std::cout << iterator->second << '\n';
      }
    }
  }
  return 0;
}