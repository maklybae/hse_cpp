#include "../ray.h"

#include <string>

#include "../line.h"
#include "../point.h"
#include "../segment.h"
#include "../vector.h"

geometry::Ray &geometry::Ray::Move(const Vector &vec) {
  start_.Move(vec);
  inter_point_.Move(vec);
  return *this;
}

bool geometry::Ray::ContainsPoint(const Point &point) const {
  return Line{GetStart(), GetInterPoint()}.ContainsPoint(point) &&
         (point - GetStart()) * (GetInterPoint() - GetStart()) >= 0;
}

bool geometry::Ray::CrossesSegment(const Segment &to_check) const {
  if (!Line(GetStart(), GetInterPoint()).CrossesSegment(to_check)) {
    return false;
  }

  auto start_start = GetStart() - to_check.GetStart();
  auto direction = GetInterPoint() - GetStart();
  auto segment_vec = to_check.GetEnd() - to_check.GetStart();
  auto area1 = start_start ^ segment_vec;
  auto area2 = direction ^ segment_vec;

  return ContainsPoint(to_check.GetStart()) || ContainsPoint(to_check.GetEnd()) || (area1 > 0) != (area2 > 0);
}

geometry::Ray *geometry::Ray::Clone() const {
  return new Ray{*this};
}

std::string geometry::Ray::ToString() const {
  return "Ray(" + GetStart().ToString() + ", " + (GetInterPoint() - GetStart()).ToString() + ")";
}
