#include "../segment.h"

#include <string>

#include "../vector.h"

geometry::Segment& geometry::Segment::Move(const Vector& vec) {
  start_.Move(vec);
  end_.Move(vec);
  return *this;
}

bool geometry::Segment::ContainsPoint(const Point& point) const {
  return point.CrossesSegment(*this);
}

bool geometry::Segment::CrossesSegment(const Segment& to_check) const {
  // Проверка проекций на оси.
  auto proj_check{[](int first_st, int first_end, int second_st, int second_end) {
    return std::max(std::min(first_st, first_end), std::min(second_st, second_end)) <=
           std::min(std::max(first_st, first_end), std::max(second_st, second_end));
  }};
  // Проверка знака площади.
  auto area_sign{[](const Point& first, const Point& second, const Point& third) {
    int area = (second - first) ^ (third - first);
    return area > 0 ? 1 : (area < 0 ? -1 : 0);  // Знак area -1, 0, +1
  }};
  // Проверка проекций (bounding box) и знаков площадей (точки лежат по разные стороны от отрезка).
  return proj_check(this->GetStart().GetX(), this->GetEnd().GetX(), to_check.GetStart().GetX(),
                    to_check.GetEnd().GetX()) &&
         proj_check(this->GetStart().GetY(), this->GetEnd().GetY(), to_check.GetStart().GetY(),
                    to_check.GetEnd().GetY()) &&
         area_sign(this->GetStart(), this->GetEnd(), to_check.GetStart()) *
                 area_sign(this->GetStart(), this->GetEnd(), to_check.GetEnd()) <=
             0 &&
         area_sign(to_check.GetStart(), to_check.GetEnd(), this->GetStart()) *
                 area_sign(to_check.GetStart(), to_check.GetEnd(), this->GetEnd()) <=
             0;
}

geometry::Segment* geometry::Segment::Clone() const {
  return new Segment{start_, end_};
}

std::string geometry::Segment::ToString() const {
  return "Segment(" + GetStart().ToString() + ", " + GetEnd().ToString() + ")";
}