#include "../polygon.h"

#include <string>

#include "../point.h"
#include "../ray.h"
#include "../segment.h"

geometry::Polygon &geometry::Polygon::Move(const Vector &vec) {
  for (size_t i = 0; i < GetPointCount(); ++i) {
    points_[i].Move(vec);
  }
  return *this;
}

bool geometry::Polygon::ContainsPoint(const Point &point) const {
  Point direction_point{point};
  direction_point.Move(Vector{1, 1});
  Ray test_ray{point, direction_point};
  int intersection_count{};

  for (size_t i = 0; i < GetPointCount(); ++i) {
    auto test_seg = Segment{points_[i], points_[(i + 1) % GetPointCount()]};

    if (test_seg.ContainsPoint(point)) {
      return true;
    }

    if (test_ray.ContainsPoint(points_[i]) && test_ray.ContainsPoint(points_[(i + 1) % GetPointCount()])) {
      intersection_count += 0;
    } else if (test_ray.ContainsPoint(points_[i])) {
      intersection_count += points_[i].GetY() > points_[(i + 1) % GetPointCount()].GetY();
    } else if (test_ray.ContainsPoint(points_[(i + 1) % GetPointCount()])) {
      intersection_count += points_[(i + 1) % GetPointCount()].GetY() > points_[i].GetY();
    } else {
      intersection_count += test_ray.CrossesSegment(test_seg);
    }
  }
  return intersection_count % 2 == 1;
}

bool geometry::Polygon::CrossesSegment(const Segment &to_check) const {
  for (size_t i = 0; i < GetPointCount(); ++i) {
    auto test_seg = Segment{points_[i], points_[(i + 1) % GetPointCount()]};

    if (test_seg.CrossesSegment(to_check) || points_[i].CrossesSegment(to_check)) {
      return true;
    }
  }
  return false;
}

geometry::Polygon *geometry::Polygon::Clone() const {
  return new Polygon(*this);
}

std::string geometry::Polygon::ToString() const {
  std::string info{"Polygon("};
  for (size_t i = 0; i < GetPointCount() - 1; ++i) {
    info += points_[i].ToString() + ", ";
  }
  return info + points_.back().ToString() + ")";
}
