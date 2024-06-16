#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <utility>

template <class T>
class UniquePtr {
 private:
  T* data_{};

 public:
  UniquePtr() = default;
  explicit UniquePtr(T* ptr) : data_{ptr} {
  }

  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;

  UniquePtr(UniquePtr&& uptr) noexcept : data_{std::move(uptr.data_)} {
    uptr.data_ = nullptr;
  }
  UniquePtr& operator=(UniquePtr&& uptr) noexcept {
    if (data_ == uptr.data_) {
      return *this;
    }
    delete data_;
    data_ = std::move(uptr.data_);
    uptr.data_ = nullptr;
    return *this;
  }

  T* Release() {
    T* to_return = data_;
    data_ = nullptr;
    return to_return;
  }

  UniquePtr& Reset(T* ptr = nullptr) {
    delete data_;
    data_ = ptr;
    return *this;
  }

  UniquePtr& Swap(UniquePtr& to_swap) {
    UniquePtr tmp{std::move(to_swap)};
    to_swap = std::move(*this);
    *this = std::move(tmp);
    return *this;
  }

  T* Get() const {
    return data_;
  }

  T& operator*() const {
    return *data_;
  }

  T* operator->() const {
    return data_;
  }

  explicit operator bool() const {
    return data_;
  }

  ~UniquePtr() {
    delete data_;
  }
};

#endif