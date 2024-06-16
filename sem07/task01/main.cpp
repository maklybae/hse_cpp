#include "unique_ptr.h"

int main() {
  UniquePtr<int> uptr1{new int{1}};
  UniquePtr<int> uptr2{new int{2}};

  uptr1.Swap(uptr2);

  return 0;
}