#include <cassert>
#include <iostream>

#include "string_view.h"

void Equal(const StringView& actual, const char* expected, size_t n) {
  assert(actual.Data() == expected);
  assert(actual.Size() == n);
  assert(actual.Length() == n);
  assert(actual.Empty() == (n == 0));
  for (size_t i = 0; i < n; ++i) {
    assert(actual[i] == expected[i]);
  }
}

int main() {
  const char* str = "some_test_string";
  StringView sv = str;

  sv.Substr(2, 7).Swap(sv);
  Equal(sv, str + 2, 7);
}