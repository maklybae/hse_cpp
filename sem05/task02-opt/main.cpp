#include <iostream>
#include <string>
#include <vector>

int main() {
  int n{};
  std::cin >> n;

  if (n == 0) {
    return 0;
  }

  std::vector<int> vec(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }

  std::sort(vec.begin(), vec.end());
  std::string res{};
  int prev = vec[0];
  int start = vec[0];
  for (int i = 1; i < n; ++i) {
    if (vec[i] - prev <= 1) {
      prev = vec[i];
    } else {
      if (prev != start) {
        res += std::to_string(start) + "-" + std::to_string(prev) + ",";
      } else {
        res += std::to_string(start) + ",";
      }
      start = vec[i];
      prev = vec[i];
    }
  }

  if (start == prev) {
    res += std::to_string(start);
  } else {
    res += std::to_string(start) + "-" + std::to_string(prev);
  }

  std::cout << res;

  return 0;
}