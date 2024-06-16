#ifndef SEGMENT_H
#define SEGMENT_H

#include "i_shape.h"
#include "point.h"

namespace geometry {

class Segment : public IShape {
 private:
  Point start_{};
  Point end_{};

 public:
  Segment() = default;
  Segment(const Point& start, const Point& end) : start_{start}, end_{end} {
  }
  Segment(const Segment&) = default;
  Segment(Segment&&) = default;
  Segment& operator=(const Segment&) = default;
  Segment& operator=(Segment&&) = default;

  const Point& GetStart() const {
    return start_;
  }
  const Point& GetEnd() const {
    return end_;
  }

  double Lenght() const {
    return (GetEnd() - GetStart()).Length();
  }

  Segment& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Segment* Clone() const override;
  std::string ToString() const override;

  bool IsPoint() const {
    return start_ == end_;
  }

  ~Segment() override = default;
};
}  // namespace geometry
#endif