#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>

int main() {
  std::unordered_map<int, int> count{};
  std::queue<int> q{};
  size_t real_size{};

  size_t m{};
  std::cin >> m;
  std::string input{};
  std::getline(std::cin >> std::ws, input);
  std::istringstream iss{input};

  int request{};
  while (iss >> request) {
    if (count.contains(request)) {
      std::cout << 0 << ' ';
      q.push(request);
      ++count[request];
    } else {
      if (real_size == m) {
        for (int cur = q.front(); count[cur] > 1; cur = q.front()) {
          q.pop();
          --count[cur];
        }
        count.erase(q.front());
        q.pop();
      } else {
        ++real_size;
      }
      q.emplace(request);
      ++count[request];
      std::cout << 1 << ' ';
    }
  }

  return 0;
}