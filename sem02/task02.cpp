#include <iostream>

void DeleteMatrix(int **matrix, size_t number_rows) {
  for (size_t i = 0; i < number_rows; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int main() {
  size_t n;
  size_t m;
  std::cin >> n;
  std::cin >> m;

  int **array = new int *[n];
  for (size_t i = 0; i < n; ++i) {
    array[i] = new int[m];
  }
  for (size_t i = 0; i < n; ++i) {
    array[i][0] = 1;
  }

  for (size_t j = 0; j < m; ++j) {
    array[0][j] = 1;
    std::cout << array[0][j] << ' ';
  }
  std::cout << '\n';

  for (size_t i = 1; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      if (j != 0) {
        array[i][j] = array[i - 1][j] + array[i][j - 1];
      }
      std::cout << array[i][j] << ' ';
    }
    std::cout << '\n';
  }

  DeleteMatrix(array, n);
  return 0;
}