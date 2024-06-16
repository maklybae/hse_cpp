#include <iostream>
#include <vector>

int main() {
  size_t n{};
  std::cin >> n;
  int k{};
  std::cin >> k;

  std::vector<std::vector<int>> graph(n);
  while (k--) {
    int request{};
    std::cin >> request;

    if (request == 1) {
      int from{};
      int to{};
      std::cin >> from >> to;

      graph[from - 1].push_back(to - 1);
      graph[to - 1].push_back(from - 1);
    } else {
      int to_print{};
      std::cin >> to_print;
      auto& neighbors = graph[to_print - 1];
      for (const int& neighbor : neighbors) {
        std::cout << (neighbor + 1) << ' ';
      }
      std::cout << '\n';
    }
  }
  return 0;
}