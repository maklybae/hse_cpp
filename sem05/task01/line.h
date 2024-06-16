#ifndef LINE_H
#define LINE_H

#include <tuple>

#include "i_shape.h"
#include "point.h"

namespace geometry {
class Line : public IShape {
 private:
  Point first_{};
  Point second_{};
  std::tuple<int, int, int> GetEquation() const;

 public:
  Line() = default;
  Line(const Point& first, const Point& second) : first_{first}, second_{second} {
  }
  Line(const Line&) = default;
  Line(Line&&) = default;
  Line& operator=(const Line&) = default;
  Line& operator=(Line&&) = default;

  const Point& GetFirst() const {
    return first_;
  }
  const Point& GetSecond() const {
    return second_;
  }

  Line& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Line* Clone() const override;
  std::string ToString() const override;

  ~Line() override = default;
};
}  // namespace geometry

#endif