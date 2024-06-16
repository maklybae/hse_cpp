#ifndef SHARED_PTR
#define SHARED_PTR
#define WEAK_PTR_IMPLEMENTED

#include <stdexcept>
#include <utility>

class BadWeakPtr : public std::runtime_error {
 public:
  using std::runtime_error::runtime_error;
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
 private:
  struct Counter {
   public:
    size_t strong_count_{};
    size_t weak_count_{};
  };
  T* ptr_{};
  Counter* counter_{};

 public:
  template <class U>
  friend class WeakPtr;

  SharedPtr() = default;
  explicit SharedPtr(T* ptr) : ptr_{ptr}, counter_{ptr ? new Counter{1, 0} : nullptr} {
  }
  explicit SharedPtr(const WeakPtr<T>& w_ptr) {
    if (w_ptr.Expired()) {
      throw BadWeakPtr{"Bad weak_ptr"};
    }
    ptr_ = w_ptr.ptr_;
    counter_ = w_ptr.counter_;
    if (counter_) {
      ++counter_->strong_count_;
    }
  }
  SharedPtr(const SharedPtr& other) : ptr_{other.ptr_}, counter_{other.counter_} {
    if (counter_) {
      ++counter_->strong_count_;
    }
  }
  SharedPtr& operator=(const SharedPtr& other) {
    if (this == &other) {
      return *this;
    }
    if (counter_ && !(--counter_->strong_count_)) {
      delete ptr_;
      if (!counter_->weak_count_) {
        delete counter_;
      }
    }
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    if (counter_) {
      ++counter_->strong_count_;
    }
    return *this;
  }
  SharedPtr(SharedPtr&& other) noexcept : ptr_{other.ptr_}, counter_{other.counter_} {
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }
  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    if (counter_ && !(--counter_->strong_count_)) {
      delete ptr_;
      if (!counter_->weak_count_) {
        delete counter_;
      }
    }
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
    return *this;
  }

  SharedPtr& Reset(T* ptr = nullptr) {
    *this = std::move(SharedPtr(ptr));
    return *this;
  }

  SharedPtr& Swap(SharedPtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(counter_, other.counter_);
    return *this;
  }

  T* Get() const {
    return ptr_;
  }
  size_t UseCount() const {
    return counter_ ? counter_->strong_count_ : 0;
  }
  T& operator*() const {
    return *ptr_;
  }
  T* operator->() const {
    return ptr_;
  }
  explicit operator bool() const {
    return ptr_ != nullptr;
  }

  ~SharedPtr() noexcept {
    if (counter_ && !(--counter_->strong_count_)) {
      delete ptr_;
      if (!counter_->weak_count_) {
        delete counter_;
      }
    }
  }
};

template <class T, class... Args>
SharedPtr<T> MakeShared(Args&&... args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
class WeakPtr {
 private:
  using Counter = SharedPtr<T>::Counter;
  T* ptr_{};
  Counter* counter_{};

 public:
  template <class U>
  friend class SharedPtr;

  WeakPtr() = default;
  WeakPtr(const WeakPtr& other) : ptr_{other.ptr_}, counter_{other.counter_} {
    if (counter_) {
      ++counter_->weak_count_;
    }
  }
  WeakPtr(WeakPtr&& other) noexcept : ptr_{other.ptr_}, counter_{other.counter_} {
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }
  WeakPtr& operator=(const WeakPtr& other) {
    if (this == &other) {
      return *this;
    }
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    if (counter_) {
      ++counter_->weak_count_;
    }
    return *this;
  }
  WeakPtr& operator=(WeakPtr&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
    return *this;
  }
  WeakPtr(const SharedPtr<T>& s_ptr) : ptr_{s_ptr.ptr_}, counter_{s_ptr.counter_} {  // NOLINT
    if (counter_) {
      ++counter_->weak_count_;
    }
  }
  WeakPtr& Swap(WeakPtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(counter_, other.counter_);
    return *this;
  }

  bool Expired() const {
    return !counter_ || !(counter_->strong_count_);
  }

  WeakPtr& Reset() {
    ptr_ = nullptr;
    if (counter_) {
      --counter_->weak_count_;
    }
    if (Expired() && (!counter_ || !counter_->weak_count_)) {
      delete counter_;
    }
    counter_ = nullptr;
    return *this;
  }

  size_t UseCount() const {
    return counter_ ? counter_->strong_count_ : 0;
  }

  SharedPtr<T> Lock() const {
    try {
      return SharedPtr(*this);
    } catch (BadWeakPtr) {
      return SharedPtr<T>{};
    }
  }

  ~WeakPtr() noexcept {
    if (counter_) {
      --counter_->weak_count_;
    }
    if (Expired() && (!counter_ || !counter_->weak_count_)) {
      delete counter_;
    }
  }
};

#endif