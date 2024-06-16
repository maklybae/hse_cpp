#ifndef RANGE_H
#define RANGE_H
#define REVERSE_RANGE_IMPLEMENTED

#include <iterator>

class Range {
 private:
  const int start_{};
  const int end_{};
  const int step_{1};

 public:
  explicit Range(int end) : end_{end} {
  }
  Range(int start, int end) : start_{start}, end_{end} {
  }
  Range(int start, int end, int step) : start_{start}, end_{end}, step_{step} {
  }

  class Iterator;
  Iterator begin() const;                          // NOLINT
  Iterator end() const;                            // NOLINT
  std::reverse_iterator<Iterator> rbegin() const;  // NOLINT
  std::reverse_iterator<Iterator> rend() const;    // NOLINT

  class Iterator {
   private:
    int val_{};
    int step_{};

   public:
    using iterator_category = std::bidirectional_iterator_tag;  // NOLINT
    using value_type = int;                                     // NOLINT
    using difference_type = std::ptrdiff_t;                     // NOLINT
    using pointer = value_type*;                                // NOLINT
    using reference = value_type;                               // NOLINT

    Iterator() = default;
    Iterator(int val, int step) : val_{val}, step_{step} {
    }

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    value_type operator*();

    friend bool operator!=(const Iterator&, const Iterator&);
    friend bool operator!=(const std::reverse_iterator<Range::Iterator>& lhs,
                           const std::reverse_iterator<Range::Iterator>& rhs);
    friend std::reverse_iterator<Range::Iterator> Range::rbegin() const;
    friend std::reverse_iterator<Range::Iterator> Range::rend() const;
  };
};

#endif