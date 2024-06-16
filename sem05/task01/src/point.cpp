#include "../point.h"

#include <algorithm>
#include <string>

#include "../line.h"
#include "../segment.h"
#include "../vector.h"

geometry::Vector geometry::operator-(const Point& first, const Point& second) {
  return {first.GetX() - second.GetX(), first.GetY() - second.GetY()};
}

bool geometry::operator==(const Point& first, const Point& second) {
  return first.GetX() == second.GetX() && first.GetY() == second.GetY();
}

geometry::Point& geometry::Point::Move(const Vector& vec) {
  x_ += vec.GetX();
  y_ += vec.GetY();
  return *this;
}

bool geometry::Point::ContainsPoint(const Point& to_check) const {
  return GetX() == to_check.GetX() && GetY() == to_check.GetY();
}

bool geometry::Point::CrossesSegment(const Segment& seg) const {
  if (seg.IsPoint()) {
    return seg.GetStart() == *this;
  }

  auto minmax_x = std::minmax({seg.GetStart().GetX(), seg.GetEnd().GetX()});
  auto minmax_y = std::minmax({seg.GetStart().GetY(), seg.GetEnd().GetY()});
  return Line{seg.GetStart(), seg.GetEnd()}.ContainsPoint(*this) &&
         (minmax_x.first <= this->GetX() && this->GetX() <= minmax_x.second) &&
         (minmax_y.first <= this->GetY() && this->GetY() <= minmax_y.second);
}

geometry::Point* geometry::Point::Clone() const {
  return new Point{x_, y_};
}

std::string geometry::Point::ToString() const {
  return "Point(" + std::to_string(GetX()) + ", " + std::to_string(GetY()) + ")";
}