#include <iostream>
#include <vector>

int main() {
  int n{};
  std::cin >> n;
  std::vector<int> arr(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  int m{};
  std::cin >> m;
  std::vector<int> filter(m);
  for (size_t i = 0; i < m; ++i) {
    std::cin >> filter[i];
  }

  std::sort(arr.begin(), arr.end());
  std::sort(filter.begin(), filter.end());
  size_t arr_ptr{};
  size_t filter_ptr{};
  while (arr_ptr < n) {
    while (filter_ptr < m && filter[filter_ptr] < arr[arr_ptr]) {
      ++filter_ptr;
    }
    if (arr[arr_ptr] != filter[filter_ptr]) {
      std::cout << arr[arr_ptr] << ' ';
    }
    ++arr_ptr;
  }

  return 0;
}