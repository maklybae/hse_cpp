#include "string_view.h"

#include <algorithm>

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return Size();
}

char StringView::operator[](size_t index) const {
  return ptr_[index];
}

char StringView::At(size_t index) const {
  if (index >= Size()) {
    throw StringViewOutOfRange{};
  }
  return (*this)[index];
}

char StringView::Front() const {
  return ptr_[0];
}

char StringView::Back() const {
  return ptr_[size_ - 1];
}

bool StringView::Empty() const {
  return size_ == 0;
}

const char* StringView::Data() const {
  return ptr_;
}

StringView& StringView::Swap(StringView& to_swap) {
  StringView temp = *this;
  *this = to_swap;
  to_swap = temp;
  return *this;
}

StringView& StringView::RemovePrefix(size_t prefix_size) {
  ptr_ = ptr_ + prefix_size;
  size_ -= prefix_size;
  return *this;
}

StringView& StringView::RemoveSuffix(size_t suffix_size) {
  size_ -= suffix_size;
  return *this;
}

StringView StringView::Substr(size_t pos, size_t count) {
  if (pos >= Size()) {
    throw StringViewOutOfRange{};
  }
  return {ptr_ + pos, std::min(count, Size() - pos)};
}
