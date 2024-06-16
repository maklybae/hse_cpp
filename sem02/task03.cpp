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
  int m;
  std::cin >> n >> m;

  int **array = new int *[n];
  for (int i = 0; i < n; ++i) {
    array[i] = new int[m];
  }

  int cur = -1;
  for (int start = 0; start < n + m + 1; ++start) {
    for (int i = 0, j = start; i < n && j >= 0; ++i, --j) {
      if (j >= m) {
        continue;
      }
      array[i][j] = ++cur;
    }
  }

  PrintArray(array, n, m);
  DeleteMatrix(array, n);
  return 0;
}