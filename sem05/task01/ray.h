#ifndef RAY_H
#define RAY_H

#include "i_shape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
class Ray : public IShape {
 private:
  Point start_{};
  Point inter_point_{};

 public:
  Ray() = default;
  Ray(const Point& start, const Point& inter_point) : start_{start}, inter_point_{inter_point} {
  }
  Ray(const Ray&) = default;
  Ray(Ray&&) = default;
  Ray& operator=(const Ray&) = default;
  Ray& operator=(Ray&&) = default;

  const Point& GetStart() const {
    return start_;
  }
  const Point& GetInterPoint() const {
    return inter_point_;
  }

  Ray& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Ray* Clone() const override;
  std::string ToString() const override;

  ~Ray() override = default;
};
}  // namespace geometry

#endif