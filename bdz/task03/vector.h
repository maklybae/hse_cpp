#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <type_traits>

template <class T>
class Vector {
 private:
  size_t size_{};
  size_t capacity_{};
  T* ptr_{};

 public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;
  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Vector() = default;
  explicit Vector(size_t count);
  Vector(size_t count, const T& value);
  Vector(const Vector& other);
  Vector(Vector&& other) noexcept;
  Vector(std::initializer_list<T> list);
  Vector& operator=(const Vector& other);
  Vector& operator=(Vector&& other) noexcept;

  Vector& Reserve(size_t new_cap);

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) {
    try {
      for (auto it = first; it != last; ++it) {
        PushBack(*it);
      }
    } catch (...) {
      delete[] ptr_;
      ptr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
      throw;
    }
  }

  size_t Size() const noexcept {
    return size_;
  }
  size_t Capacity() const noexcept {
    return capacity_;
  }
  bool Empty() const noexcept {
    return size_ == 0;
  }

  T* Data() noexcept {
    return ptr_;
  }
  const T* Data() const noexcept {
    return ptr_;
  }

  T& operator[](size_t pos) noexcept {
    return ptr_[pos];
  }
  const T& operator[](size_t pos) const noexcept {
    return ptr_[pos];
  }
  T& At(size_t pos);
  const T& At(size_t pos) const;
  T& Front() noexcept {
    return ptr_[0];
  }
  const T& Front() const noexcept {
    return ptr_[0];
  }
  T& Back() noexcept {
    return ptr_[size_ - 1];
  }
  const T& Back() const noexcept {
    return ptr_[size_ - 1];
  }

  Vector& Swap(Vector& other) noexcept;

  Vector& Resize(size_t new_size);
  Vector& Resize(size_t new_size, const T& value);

  Vector& ShrinkToFit();

  Vector& Clear();

  Vector& PushBack(const T& value);
  Vector& PushBack(T&& value);
  Vector& PopBack() noexcept;

  Iterator begin() noexcept {  // NOLINT
    return ptr_;
  }
  ConstIterator begin() const noexcept {  // NOLINT
    return ptr_;
  }
  Iterator end() noexcept {  // NOLINT
    return ptr_ + size_;
  }
  ConstIterator end() const noexcept {  // NOLINT
    return ptr_ + size_;
  }
  ConstIterator cbegin() const noexcept {  // NOLINT
    return ptr_;
  }
  ConstIterator cend() const noexcept {  // NOLINT
    return ptr_ + size_;
  }
  ReverseIterator rbegin() noexcept {  // NOLINT
    return std::make_reverse_iterator(end());
  }
  ConstReverseIterator rbegin() const noexcept {  // NOLINT
    return std::make_reverse_iterator(end());
  }
  ReverseIterator rend() noexcept {  // NOLINT
    return std::make_reverse_iterator(begin());
  }
  ConstReverseIterator rend() const noexcept {  // NOLINT
    return std::make_reverse_iterator(begin());
  }
  ConstReverseIterator crbegin() const noexcept {  // NOLINT
    return std::make_reverse_iterator(end());
  }
  ConstReverseIterator crend() const noexcept {  // NOLINT
    return std::make_reverse_iterator(begin());
  }

  ~Vector() {
    delete[] ptr_;
  }
};

#include "vector.tpp"

#endif