#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
  size_t n{};
  std::cin >> n;

  std::vector<std::pair<int, std::pair<int, int>>> arr(n);
  for (size_t i = 0; i < n; ++i) {
    arr[i].first = static_cast<int>(i) + 1;
    std::cin >> arr[i].second.first >> arr[i].second.second;
  }

  std::sort(arr.begin(), arr.end(), [](auto& x, auto& y) {
    if (x.second.first != y.second.first) {
      return x.second.first > y.second.first;
    }

    if (x.second.second != y.second.second) {
      return x.second.second < y.second.second;
    }

    return x.first < y.first;
  });

  std::for_each(arr.begin(), arr.end(), [](auto& x) { std::cout << x.first << '\n'; });
  return 0;
}