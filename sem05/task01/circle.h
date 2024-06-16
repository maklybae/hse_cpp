#ifndef CIRCLE_H
#define CIRCLE_H

#include "i_shape.h"
#include "point.h"

namespace geometry {
class Circle : public IShape {
 private:
  Point center_{};
  int radius_{};

 public:
  Circle() = default;
  Circle(const Point& center, int radius) : center_{center}, radius_{radius} {
  }
  Circle(const Circle&) = default;
  Circle(Circle&&) = default;
  Circle& operator=(const Circle&) = default;
  Circle& operator=(Circle&&) = default;

  const Point& GetCenter() const {
    return center_;
  }
  int GetRadius() const {
    return radius_;
  }

  int EquationSubst(const Point&) const;
  Circle& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Circle* Clone() const override;
  std::string ToString() const override;

  ~Circle() override = default;
};
}  // namespace geometry

#endif