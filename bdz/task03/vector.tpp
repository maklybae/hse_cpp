#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "vector.h"

template <class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
}

template <class T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
  return !(lhs == rhs);
}

template <class T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs) {
  for (size_t i = 0; i < std::min(lhs.Size(), rhs.Size()); ++i) {
    if (lhs[i] != rhs[i]) {
      return lhs[i] < rhs[i];
    }
  }
  return lhs.Size() < rhs.Size();
}

template <class T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
  return !(lhs < rhs) && lhs != rhs;
}

template <class T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
  return !(lhs > rhs);
}

template <class T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
  return !(lhs < rhs);
}

template <class T>
Vector<T>::Vector(size_t count) : size_{count}, capacity_{count} {
  ptr_ = count > 0 ? new T[count] : nullptr;
}

template <class T>
Vector<T>::Vector(size_t count, const T& value) : size_{count}, capacity_{count} {
  try {
    ptr_ = (count > 0 ? new T[count] : nullptr);
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    throw;
  }
  try {
    std::fill(ptr_, ptr_ + size_, value);
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    throw;
  }
}

template <class T>
Vector<T>::Vector(const Vector<T>& other) : size_{other.size_}, capacity_{other.capacity_} {
  try {
    ptr_ = (other.capacity_ > 0 ? new T[other.capacity_] : nullptr);
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    throw;
  }
  try {
    std::copy(other.ptr_, other.ptr_ + other.size_, ptr_);
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    throw;
  }
}

template <class T>
Vector<T>::Vector(Vector<T>&& other) noexcept : size_{other.size_}, capacity_{other.capacity_}, ptr_{other.ptr_} {
  other.ptr_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> list) : size_{list.size()}, capacity_{list.size()} {
  try {
    ptr_ = (list.size() > 0 ? new T[list.size()] : nullptr);
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    throw;
  }
  try {
    std::copy(std::make_move_iterator(list.begin()), std::make_move_iterator(list.end()), ptr_);
  } catch (...) {
    delete[] ptr_;
    ptr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    throw;
  }
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
  *this = std::move(Vector(other));
  return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  delete[] ptr_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  ptr_ = other.ptr_;
  other.size_ = 0;
  other.capacity_ = 0;
  other.ptr_ = nullptr;
  return *this;
}

template <class T>
Vector<T>& Vector<T>::Reserve(size_t new_cap) {
  if (capacity_ >= new_cap) {
    return *this;
  }
  T* new_ptr{};
  try {
    new_ptr = new T[new_cap];
    std::copy(std::make_move_iterator(ptr_), std::make_move_iterator(ptr_ + size_), new_ptr);
    delete[] ptr_;
    capacity_ = new_cap;
    ptr_ = new_ptr;
  } catch (...) {
    delete[] new_ptr;
    throw;
  }
  return *this;
}

template <class T>
T& Vector<T>::At(size_t pos) {
  if (pos >= size_) {
    throw std::out_of_range{"Index out of range"};
  }
  return ptr_[pos];
}

template <class T>
const T& Vector<T>::At(size_t pos) const {
  if (pos >= size_) {
    throw std::out_of_range{"Index out of range"};
  }
  return ptr_[pos];
}

template <class T>
Vector<T>& Vector<T>::Swap(Vector<T>& other) noexcept {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(ptr_, other.ptr_);
  return *this;
}

template <class T>
Vector<T>& Vector<T>::Resize(size_t new_size) {
  // In Vector+ destructor on unused.
  if (new_size <= capacity_) {
    // In Vector+ is harder.
    size_ = new_size;
  } else {
    T* new_ptr{};
    try {
      new_ptr = new T[2 * new_size];
      if (ptr_) {
        std::copy(std::make_move_iterator(ptr_), std::make_move_iterator(ptr_ + size_), new_ptr);
      }
      size_ = new_size;
      delete[] ptr_;
      ptr_ = new_ptr;
      capacity_ = new_size * 2;
    } catch (...) {
      delete[] new_ptr;
      throw;
    }
  }
  return *this;
}

template <class T>
Vector<T>& Vector<T>::Resize(size_t new_size, const T& value) {
  size_t prev_size = size_;
  Resize(new_size);

  if (new_size > prev_size) {
    std::fill(ptr_ + prev_size, ptr_ + size_, value);
  }

  return *this;
}

template <class T>
Vector<T>& Vector<T>::ShrinkToFit() {
  capacity_ = size_;
  T* new_ptr{};
  try {
    new_ptr = capacity_ > 0 ? new T[capacity_] : nullptr;
    if (new_ptr) {
      std::copy(std::make_move_iterator(ptr_), std::make_move_iterator(ptr_ + size_), new_ptr);
    }
    delete[] ptr_;
    ptr_ = new_ptr;
  } catch (...) {
    delete[] new_ptr;
  }
  return *this;
}

template <class T>
Vector<T>& Vector<T>::Clear() {
  size_ = 0;
  return *this;
}

template <class T>
Vector<T>& Vector<T>::PushBack(const T& value) {
  if (size_ == capacity_) {
    size_t tmp_cap = (capacity_ > 0 ? capacity_ * 2 : 1);
    T* new_ptr = new T[tmp_cap];
    if (ptr_) {
      std::copy(std::make_move_iterator(ptr_), std::make_move_iterator(ptr_ + size_), new_ptr);
    }
    try {
      new_ptr[size_] = value;
    } catch (...) {
      if (size_) {
        std::copy(std::make_move_iterator(new_ptr), std::make_move_iterator(new_ptr + size_), ptr_);
      }
      delete[] new_ptr;
      throw;
    }
    delete[] ptr_;
    ptr_ = new_ptr;
    ++size_;
    capacity_ = tmp_cap;
  } else {
    ptr_[size_] = value;
    ++size_;
  }
  return *this;
}

template <class T>
Vector<T>& Vector<T>::PushBack(T&& value) {
  if (size_ == capacity_) {
    size_t tmp_cap = (capacity_ > 0 ? capacity_ * 2 : 1);
    T* new_ptr = new T[tmp_cap];
    if (ptr_) {
      std::copy(std::make_move_iterator(ptr_), std::make_move_iterator(ptr_ + size_), new_ptr);
    }
    try {
      new_ptr[size_] = std::move(value);
    } catch (...) {
      if (size_) {
        std::copy(std::make_move_iterator(new_ptr), std::make_move_iterator(new_ptr + size_), ptr_);
      }
      delete[] new_ptr;
      throw;
    }
    delete[] ptr_;
    ptr_ = new_ptr;
    ++size_;
    capacity_ = tmp_cap;
  } else {
    ptr_[size_] = std::move(value);
    ++size_;
  }
  return *this;
}

template <class T>
Vector<T>& Vector<T>::PopBack() noexcept {
  if (size_ > 0) {
    --size_;
  }
  return *this;
}

#endif