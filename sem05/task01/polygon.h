#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "i_shape.h"
#include "point.h"

namespace geometry {
class Polygon : public IShape {
 private:
  std::vector<Point> points_{};

 public:
  Polygon() = default;
  explicit Polygon(const std::vector<Point>& points) : points_{points} {
  }
  Polygon(const Polygon&) = default;
  Polygon(Polygon&& polygon) = default;
  Polygon& operator=(const Polygon&) = default;
  Polygon& operator=(Polygon&&) = default;

  const std::vector<Point>& GetPoints() const {
    return points_;
  }
  size_t GetPointCount() const {
    return points_.size();
  }

  Polygon& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Polygon* Clone() const override;
  std::string ToString() const override;

  ~Polygon() override = default;
};
}  // namespace geometry

#endif