#include <iostream>

int main() {
  size_t n;
  std::cin >> n;

  int* array = new int[(n + 4) * (n + 4)];

  for (size_t i = 0; i != (n + 4) * (n + 4); ++i) {
    array[i] = 0;
  }

  for (size_t i = 0; i != (n + 4); ++i) {
    array[i] = 1;
    array[(n + 3) * (n + 4) + i] = 1;
  }

  for (size_t i = 0; i != (n + 4); ++i) {
    array[i * (n + 4)] = 1;
    array[i * (n + 4) + (n + 3)] = 1;
  }

  int cur_x = 2;
  int cur_y = 2;
  int vec_i = 0;
  int vec_j = 1;
  bool prev_changed = false;
  while (!prev_changed || array[(cur_x + vec_i) * (n + 4) + (cur_y + vec_j)] != 1) {
    prev_changed = false;
    array[cur_x * (n + 4) + cur_y] = 1;

    if (array[(cur_x + vec_i * 2) * (n + 4) + (cur_y + vec_j * 2)] == 1) {
      if (vec_i == 0 && vec_j == 1) {
        vec_i = 1;
        vec_j = 0;
      } else if (vec_i == 1 && vec_j == 0) {
        vec_i = 0;
        vec_j = -1;
      } else if (vec_i == 0 && vec_j == -1) {
        vec_i = -1;
        vec_j = 0;
      } else {
        vec_i = 0;
        vec_j = 1;
      }
      prev_changed = true;
    }

    cur_x += vec_i;
    cur_y += vec_j;
  }

  for (size_t i = 2; i < (n + 2); ++i) {
    for (size_t j = 2; j < (n + 2); ++j) {
      std::cout << array[i * (n + 4) + j];
    }
    std::cout << "\n";
  }

  delete[] array;
  return 0;
}