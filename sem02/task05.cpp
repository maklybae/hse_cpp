#include <iostream>

void FillZeros(int **array, size_t n, size_t m) {
  for (size_t i = 0; i < n + 2; ++i) {
    for (size_t j = 0; j < m + 2; ++j) {
      array[i][j] = 0;
    }
  }
}

int CountBombs(const int *const *array, size_t x, size_t y) {
  int count = 0;
  for (size_t i = x - 1; i < x + 2; ++i) {
    for (size_t j = y - 1; j < y + 2; ++j) {
      count += static_cast<int>(array[i][j] == -1);
    }
  }
  return count;
}

void PrintMinesweeper(const int *const *array, size_t n, size_t m) {
  for (size_t i = 1; i < n + 1; ++i) {
    for (size_t j = 1; j < m + 1; ++j) {
      if (array[i][j] == -1) {
        std::cout << '*' << ' ';
      } else {
        std::cout << array[i][j] << ' ';
      }
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
  size_t n;
  size_t m;
  int w;
  std::cin >> n >> m >> w;

  int **array = new int *[n + 2];
  for (size_t i = 0; i < n + 2; ++i) {
    array[i] = new int[m + 2];
  }
  FillZeros(array, n, m);

  while (w--) {
    size_t x;
    size_t y;
    std::cin >> x >> y;
    array[x][y] = -1;
  }

  for (size_t i = 1; i < n + 1; ++i) {
    for (size_t j = 1; j < m + 1; ++j) {
      if (array[i][j] != -1) {
        array[i][j] = CountBombs(array, i, j);
      }
    }
  }

  PrintMinesweeper(array, n, m);
  DeleteMatrix(array, n + 2);
  return 0;
}