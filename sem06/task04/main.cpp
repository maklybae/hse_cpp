#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  size_t n{};
  std::cin >> n;
  std::vector<int> arr(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  int m{};
  std::cin >> m;
  while (m--) {
    int request{};
    std::cin >> request;
    auto upper = std::upper_bound(arr.begin(), arr.end(), request);
    std::cout << std::distance(std::lower_bound(arr.begin(), arr.end(), request), upper) << '\n';
  }
  return 0;
}