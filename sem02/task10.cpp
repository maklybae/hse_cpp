#include <iostream>
#include <utility>

void PrintArray(const int *array, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    std::cout << array[i] << ' ';
  }
  std::cout << '\n';
}

void Sort(int *begin, int *end) {
  size_t size = end - begin + 1;
  for (size_t first = 0; first < size - 1; ++first) {
    for (size_t second = first + 1; second < size; ++second) {
      if (begin[first] > begin[second]) {
        std::swap(begin[first], begin[second]);
      }
    }
  }
}

int main() {
  size_t n;
  std::cin >> n;

  int *array = new int[n];

  for (size_t i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  Sort(array, &array[n - 1]);
  PrintArray(array, n);
  delete[] array;
  return 0;
}