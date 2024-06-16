#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
  size_t n{};
  std::cin >> n;

  std::vector<int16_t> arr(n);
  std::for_each(arr.begin(), arr.end(), [](int16_t& x) { std::cin >> x; });

  int to_find{};
  std::cin >> to_find;
  std::cout << std::count(arr.begin(), arr.end(), to_find);
  return 0;
}