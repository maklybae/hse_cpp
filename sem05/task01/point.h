#ifndef POINT_H
#define POINT_H

#include "i_shape.h"
#include "vector.h"

namespace geometry {

class Point : public IShape {
 private:
  int x_{};
  int y_{};

 public:
  Point() = default;
  Point(int x, int y) : x_{x}, y_{y} {
  }
  Point(const Point&) = default;
  Point(Point&&) = default;
  Point& operator=(const Point&) = default;
  Point& operator=(Point&&) = default;

  int GetX() const {
    return x_;
  };
  int GetY() const {
    return y_;
  }

  Point& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Point* Clone() const override;
  std::string ToString() const override;

  ~Point() override = default;
};

Vector operator-(const Point&, const Point&);
bool operator==(const Point&, const Point&);
}  // namespace geometry

#endif