#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H

#include <algorithm>
#include <list>
#include <vector>

template <class KeyT>
class UnorderedSet {
 private:
  size_t n_elements_{};
  size_t n_buckets_{};
  std::vector<std::list<KeyT>> data_{};

 public:
  UnorderedSet() = default;
  explicit UnorderedSet(size_t count) : n_buckets_{count}, data_{count} {
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  UnorderedSet(Iterator first, Iterator last);

  UnorderedSet(const UnorderedSet&) = default;
  UnorderedSet(UnorderedSet&& other);
  UnorderedSet& operator=(const UnorderedSet&) = default;
  UnorderedSet& operator=(UnorderedSet&& other);

  size_t Size() const;
  bool Empty() const;
  UnorderedSet& Clear();
  size_t BucketCount() const;
  size_t BucketSize(size_t id) const;
  size_t Bucket(const KeyT& key) const;
  double LoadFactor() const;

  UnorderedSet& Insert(const KeyT& key);
  UnorderedSet& Insert(KeyT&& key);

  UnorderedSet& Erase(const KeyT& key);

  bool Find(const KeyT& key) const;

  UnorderedSet& Rehash(size_t new_bucket_cout);
  UnorderedSet& Reserve(size_t new_bucket_count);

  ~UnorderedSet() = default;
};

template <class KeyT>
template <class Iterator, class>
inline UnorderedSet<KeyT>::UnorderedSet(Iterator first, Iterator last)
    : n_buckets_{static_cast<size_t>(std::distance(first, last))}, data_{n_buckets_} {
  for (auto iter = first; iter != last; ++iter) {
    Insert(*iter);
  }
}

template <class KeyT>
inline UnorderedSet<KeyT>::UnorderedSet(UnorderedSet&& other)
    : n_elements_{other.n_elements_}, n_buckets_{other.n_buckets_}, data_{std::move(other.data_)} {
  other.n_buckets_ = 0;
  other.n_elements_ = 0;
}

template <class KeyT>
inline UnorderedSet<KeyT>& UnorderedSet<KeyT>::operator=(UnorderedSet&& other) {
  if (this == &other) {
    return *this;
  }
  n_elements_ = other.n_elements_;
  n_buckets_ = other.n_buckets_;
  data_ = std::move(other.data_);
  other.n_buckets_ = other.n_elements_ = 0;
  return *this;
}

template <class KeyT>
size_t UnorderedSet<KeyT>::Size() const {
  return n_elements_;
}

template <class KeyT>
inline bool UnorderedSet<KeyT>::Empty() const {
  return n_elements_ == 0;
}

template <class KeyT>
inline UnorderedSet<KeyT>& UnorderedSet<KeyT>::Clear() {
  for (auto& list : data_) {
    list.clear();
  }
  n_elements_ = 0;
  return *this;
}

template <class KeyT>
inline size_t UnorderedSet<KeyT>::BucketCount() const {
  return n_buckets_;
}

template <class KeyT>
inline size_t UnorderedSet<KeyT>::BucketSize(size_t id) const {
  return id < n_buckets_ ? data_[id].size() : 0;
}

template <class KeyT>
inline size_t UnorderedSet<KeyT>::Bucket(const KeyT& key) const {
  return n_buckets_ > 0 ? std::hash<KeyT>{}(key) % n_buckets_ : 0;
}

template <class KeyT>
inline double UnorderedSet<KeyT>::LoadFactor() const {
  return n_buckets_ > 0 ? static_cast<double>(n_elements_) / n_buckets_ : 0.0;
}

template <class KeyT>
inline UnorderedSet<KeyT>& UnorderedSet<KeyT>::Insert(const KeyT& key) {
  if (n_elements_ == n_buckets_) {
    Reserve(n_buckets_ > 0 ? n_buckets_ * 2 : 1);
  }
  auto bucket = Bucket(key);
  data_[bucket].push_front(key);
  ++n_elements_;
  return *this;
}

template <class KeyT>
inline UnorderedSet<KeyT>& UnorderedSet<KeyT>::Insert(KeyT&& key) {
  if (n_elements_ == n_buckets_) {
    Reserve(n_buckets_ > 0 ? n_buckets_ * 2 : 1);
  }
  auto bucket = Bucket(key);
  data_[bucket].push_front(std::move(key));
  ++n_elements_;
  return *this;
}

template <class KeyT>
inline UnorderedSet<KeyT>& UnorderedSet<KeyT>::Erase(const KeyT& key) {
  auto bucket = Bucket(key);
  auto iter = std::find(data_[bucket].begin(), data_[bucket].end(), key);
  data_[bucket].erase(iter);
  --n_elements_;
  return *this;
}

template <class KeyT>
inline bool UnorderedSet<KeyT>::Find(const KeyT& key) const {
  if (n_buckets_ == 0) {
    return false;
  }
  auto bucket = Bucket(key);
  return std::find(data_[bucket].begin(), data_[bucket].end(), key) != data_[bucket].end();
}

template <class KeyT>
inline UnorderedSet<KeyT>& UnorderedSet<KeyT>::Rehash(size_t new_bucket_cout) {
  if (new_bucket_cout == n_buckets_ || new_bucket_cout < n_elements_) {
    return *this;
  }
  std::vector<std::list<KeyT>> tmp(new_bucket_cout);
  for (auto iter_list = data_.begin(); iter_list != data_.end(); ++iter_list) {
    if (!iter_list->empty()) {
      for (auto iter_node = iter_list->begin(); iter_node != iter_list->end(); ++iter_node) {
        size_t new_hash = std::hash<KeyT>{}(*iter_node) % new_bucket_cout;
        tmp[new_hash].push_front(std::move(*iter_node));
      }
    }
  }
  data_ = tmp;
  n_buckets_ = new_bucket_cout;
  return *this;
}

template <class KeyT>
inline UnorderedSet<KeyT>& UnorderedSet<KeyT>::Reserve(size_t new_bucket_count) {
  if (new_bucket_count > n_buckets_) {
    Rehash(new_bucket_count);
  }
  return *this;
}

#endif