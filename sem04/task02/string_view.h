#ifndef STRING_VIEW_H
#define STRING_VIEW_H

#include <cstddef>
#include <cstring>

class StringViewOutOfRange {};

class StringView {
 private:
  const char* ptr_{nullptr};
  std::size_t size_{0};

 public:
  StringView() = default;
  StringView(const char* ptr) : ptr_{ptr}, size_{std::strlen(ptr)} {  // NOLINT
  }
  StringView(const char* ptr, size_t size) : ptr_{ptr}, size_{size} {
  }

  size_t Size() const;
  size_t Length() const;

  char operator[](size_t index) const;
  char At(size_t index) const;
  char Front() const;
  char Back() const;

  bool Empty() const;
  const char* Data() const;

  StringView& Swap(StringView& to_swap);
  StringView& RemovePrefix(size_t prefix_size);
  StringView& RemoveSuffix(size_t suffix_size);
  StringView Substr(size_t pos, size_t count);
};

#endif