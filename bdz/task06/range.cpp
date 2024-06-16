#include "range.h"

#include <algorithm>
#include <iterator>

Range::Iterator& Range::Iterator::operator++() {
  val_ += step_;
  return *this;
}

Range::Iterator Range::Iterator::operator++(int) {
  auto copy = *this;
  ++(*this);
  return copy;
}

Range::Iterator& Range::Iterator::operator--() {
  val_ -= step_;
  return *this;
}

Range::Iterator Range::Iterator::operator--(int) {
  auto copy = *this;
  --(*this);
  return copy;
}

Range::Iterator::value_type Range::Iterator::operator*() {
  return val_;
}

bool operator!=(const std::reverse_iterator<Range::Iterator>& lhs, const std::reverse_iterator<Range::Iterator>& rhs) {
  if (lhs.base().step_ == 0) {
    return false;
  }
  return (lhs.base().step_ > 0 ? lhs.base().val_ > rhs.base().val_ : lhs.base().val_ < rhs.base().val_);
}

bool operator!=(const Range::Iterator& lhs, const Range::Iterator& rhs) {
  if (lhs.step_ == 0) {
    return false;
  }
  return (lhs.step_ > 0 ? lhs.val_ < rhs.val_ : lhs.val_ > rhs.val_);
}

Range::Iterator Range::begin() const {  // NOLINT
  return {start_, step_};
}
Range::Iterator Range::end() const {  // NOLINT
  return {end_, step_};
}

std::reverse_iterator<Range::Iterator> Range::rbegin() const {
  if (step_ == 0) {
    return std::make_reverse_iterator(end());
  }
  auto tmp = end();
  tmp.val_ = tmp.val_ + (tmp.step_ >= 0 ? 1 : -1) *
                            ((std::abs(step_) - std::abs(end_ - start_) % std::abs(step_)) % std::abs(step_));
  return std::make_reverse_iterator(tmp);
}

std::reverse_iterator<Range::Iterator> Range::rend() const {
  if (step_ == 0) {
    return std::make_reverse_iterator(begin());
  }
  auto tmp = begin();
  tmp.val_ = tmp.val_ + (tmp.step_ >= 0 ? 1 : -1) *
                            ((std::abs(step_) - std::abs(end_ - start_) % std::abs(step_)) % std::abs(step_));
  return std::make_reverse_iterator(tmp);
}
