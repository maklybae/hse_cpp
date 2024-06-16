#ifndef ARRAY_H
#define ARRAY_H
#define ARRAY_TRAITS_IMPLEMENTED

#include <algorithm>
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T, size_t N>
class Array {
 public:
  T data_[N];

  T& operator[](size_t idx) {
    return data_[idx];
  }
  const T& operator[](size_t idx) const {
    return data_[idx];
  }

  T& At(size_t idx) {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    }
    return (*this)[idx];
  }
  const T& At(size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    }
    return (*this)[idx];
  }

  T& Front() {
    return (*this)[0];
  }
  const T& Front() const {
    return (*this)[0];
  }

  T& Back() {
    return (*this)[N - 1];
  }
  const T& Back() const {
    return (*this)[N - 1];
  }

  T* Data() {
    return data_;
  }
  const T* Data() const {
    return data_;
  }

  size_t Size() const {
    return N;
  }
  bool Empty() const {
    return N == 0;
  }

  Array& Fill(const T& value) {
    std::fill(std::begin(data_), std::begin(data_) + N, value);
    return *this;
  }

  Array& Swap(Array& to_swap) {
    std::swap(*this, to_swap);
    return *this;
  }
};

template <class T>
size_t GetSize(const T&) {
  return 0;
}

template <class T, size_t N>
size_t GetSize(const T (&)[N]) {
  return N;
}

template <class T>
size_t GetRank(const T&) {
  return 0;
}

template <class T, size_t N>
size_t GetRank(const T (&array)[N]) {
  return 1 + GetRank(array[0]);
}

template <class T>
size_t GetNumElements(const T&) {
  return 1;
}

template <class T, size_t N>
size_t GetNumElements(const T (&array)[N]) {
  return GetSize(array) * GetNumElements(array[0]);
}

#endif