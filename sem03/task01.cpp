#include <iostream>

void Rec(int n, int from, int to) {
  if (n == 0) {
    return;
  }

  for (int i = 1; i <= 3; ++i) {
    if (i != to && i != from) {
      Rec(n - 1, from, i);
      std::cout << n << ' ' << from << ' ' << to << '\n';
      Rec(n - 1, i, to);
      break;
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  Rec(n, 1, 3);

  return 0;
}