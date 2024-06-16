#include <iostream>

void PrintArray(const int *const *array, int n, int m) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << array[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

void DeleteMatrix(int **matrix, size_t number_rows) {
  for (size_t i = 0; i < number_rows; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int main() {
  int n;
  std::cin >> n;

  int **array = new int *[n];
  for (int i = 0; i < n; ++i) {
    array[i] = new int[n];
  }

  for (int start = 0; start < 2 * n - 1; ++start) {
    for (int i = 0, j = start; i < n && j >= 0; ++i, --j) {
      if (j >= n) {
        continue;
      }
      if (start == n - 1) {
        array[i][j] = 1;
      } else {
        array[i][j] = start < n - 1 ? 0 : 2;
      }
    }
  }

  PrintArray(array, n, n);
  DeleteMatrix(array, n);
  return 0;
}