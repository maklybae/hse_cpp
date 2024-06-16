#ifndef VECTOR_TPP
#define VECTOR_TPP

#include <algorithm>
#include <exception>
#include <memory>

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
Vector<T>::Vector(size_t count) {
  Reserve(count);
  size_ = count;
  try {
    std::uninitialized_default_construct(ptr_, ptr_ + size_);
  } catch (...) {
    ::operator delete(reinterpret_cast<void*>(ptr_));
    throw;
  }
}

template <class T>
Vector<T>::Vector(size_t count, const T& value) {
  Reserve(count);
  size_ = count;
  try {
    std::uninitialized_fill(ptr_, ptr_ + size_, value);
  } catch (...) {
    ::operator delete(reinterpret_cast<void*>(ptr_));
    throw;
  }
}

template <class T>
Vector<T>::Vector(const Vector<T>& other) {
  Reserve(other.capacity_);
  size_ = other.size_;
  try {
    std::uninitialized_copy(other.ptr_, other.ptr_ + other.size_, ptr_);
  } catch (...) {
    ::operator delete(reinterpret_cast<void*>(ptr_));
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
Vector<T>::Vector(std::initializer_list<T> list) {
  Reserve(list.size());
  size_ = list.size();
  try {
    std::uninitialized_copy(list.begin(), list.end(), ptr_);
  } catch (...) {
    ::operator delete(reinterpret_cast<void*>(ptr_));
    throw;
  }
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
  if (this == &other) {
    return *this;
  }

  T* new_ptr = nullptr;
  if (other.ptr_) {
    new_ptr = reinterpret_cast<T*>(::operator new(sizeof(T) * other.capacity_));
    try {
      std::uninitialized_copy(other.ptr_, other.ptr_ + other.size_, new_ptr);
    } catch (...) {
      ::operator delete(reinterpret_cast<void*>(new_ptr));
      throw;
    }
  }
  std::destroy(ptr_, ptr_ + size_);
  ::operator delete(reinterpret_cast<void*>(ptr_));
  ptr_ = new_ptr;
  capacity_ = other.capacity_;
  size_ = other.size_;
  return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  std::destroy(ptr_, ptr_ + size_);
  ::operator delete(reinterpret_cast<void*>(ptr_));
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
  if (new_cap <= capacity_) {
    return *this;
  }
  T* new_ptr = reinterpret_cast<T*>(::operator new(sizeof(T) * new_cap));
  try {
    std::uninitialized_move(ptr_, ptr_ + size_, new_ptr);
  } catch (...) {
    ::operator delete(reinterpret_cast<void*>(new_ptr));
    throw;
  }

  std::destroy(ptr_, ptr_ + size_);
  ::operator delete(reinterpret_cast<void*>(ptr_));
  ptr_ = new_ptr;
  capacity_ = new_cap;
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
  if (new_size == size_) {
    return *this;
  }
  if (new_size < size_) {
    std::destroy(ptr_ + new_size, ptr_ + size_);
  } else if (new_size <= capacity_) {
    std::uninitialized_default_construct(ptr_ + size_, ptr_ + new_size);
  } else {
    size_t new_cap = 2 * new_size;
    T* new_ptr = reinterpret_cast<T*>(::operator new(sizeof(T) * new_cap));
    try {
      std::uninitialized_default_construct(new_ptr + size_, new_ptr + new_size);
    } catch (...) {
      ::operator delete(reinterpret_cast<void*>(new_ptr));
      throw;
    }
    std::uninitialized_move(ptr_, ptr_ + size_, new_ptr);
    std::destroy(ptr_, ptr_ + size_);
    ::operator delete(reinterpret_cast<void*>(ptr_));
    ptr_ = new_ptr;
    capacity_ = new_cap;
  }
  size_ = new_size;
  return *this;
}

template <class T>
Vector<T>& Vector<T>::Resize(size_t new_size, const T& value) {
  if (new_size == size_) {
    return *this;
  }
  if (new_size < size_) {
    std::destroy(ptr_ + new_size, ptr_ + size_);
  } else if (new_size <= capacity_) {
    std::uninitialized_fill(ptr_ + size_, ptr_ + new_size, value);
  } else {
    size_t new_cap = 2 * new_size;
    T* new_ptr = reinterpret_cast<T*>(::operator new(sizeof(T) * new_cap));
    try {
      std::uninitialized_fill(new_ptr + size_, new_ptr + new_size, value);
    } catch (...) {
      ::operator delete(reinterpret_cast<void*>(new_ptr));
      throw;
    }
    std::uninitialized_move(ptr_, ptr_ + size_, new_ptr);
    std::destroy(ptr_, ptr_ + size_);
    ::operator delete(reinterpret_cast<void*>(ptr_));
    ptr_ = new_ptr;
    capacity_ = new_cap;
  }
  size_ = new_size;
  return *this;
}

template <class T>
Vector<T>& Vector<T>::ShrinkToFit() {
  Vector<T> tmp;
  tmp.Reserve(size_);
  tmp.size_ = size_;
  std::uninitialized_move(ptr_, ptr_ + size_, tmp.ptr_);
  *this = std::move(tmp);
  return *this;
}

template <class T>
Vector<T>& Vector<T>::Clear() {
  std::destroy(ptr_, ptr_ + size_);
  size_ = 0;
  return *this;
}

template <class T>
template <class... Args>
Vector<T>& Vector<T>::EmplaceBack(Args&&... args) {
  if (size_ == capacity_) {
    size_t new_cap = std::max(1ul, 2 * capacity_);
    T* tmp = reinterpret_cast<T*>(::operator new(sizeof(T) * new_cap));
    try {
      new (tmp + size_) T(std::forward<Args>(args)...);
    } catch (...) {
      ::operator delete(reinterpret_cast<void*>(tmp));
      throw;
    }
    std::uninitialized_move(ptr_, ptr_ + size_, tmp);
    std::destroy(ptr_, ptr_ + size_);
    ::operator delete(reinterpret_cast<void*>(ptr_));
    ptr_ = tmp;
    ++size_;
    capacity_ = new_cap;
  } else {
    new (ptr_ + size_) T(std::forward<Args>(args)...);
    ++size_;
  }
  return *this;
}

template <class T>
Vector<T>& Vector<T>::PushBack(const T& value) {
  EmplaceBack(value);
  return *this;
}

template <class T>
Vector<T>& Vector<T>::PushBack(T&& value) {
  EmplaceBack(std::move(value));
  return *this;
}

template <class T>
Vector<T>& Vector<T>::PopBack() noexcept {
  --size_;
  std::destroy_at(ptr_ + size_);
  return *this;
}

template <class T>
Vector<T>::~Vector() {
  std::destroy(ptr_, ptr_ + size_);
  operator delete(reinterpret_cast<void*>(ptr_));
}

#endif