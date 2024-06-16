#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

int main() {
  size_t n{};
  std::cin >> n;

  std::priority_queue<int, std::vector<int>, std::greater<int>> queue{};
  while (n--) {
    int temp{};
    std::cin >> temp;
    queue.push(temp);
  }

  int64_t fee{};
  while (queue.size() > 1) {
    int temp_sum{queue.top()};
    queue.pop();
    temp_sum += queue.top();
    queue.pop();
    queue.push(temp_sum);
    fee += temp_sum;
  }

  std::cout << fee << '\n';
  return 0;
}