#include "../circle.h"

#include <cmath>
#include <string>

#include "../segment.h"

int geometry::Circle::EquationSubst(const Point &point) const {
  return (point.GetX() - GetCenter().GetX()) * (point.GetX() - GetCenter().GetX()) +
         (point.GetY() - GetCenter().GetY()) * (point.GetY() - GetCenter().GetY());
}

geometry::Circle &geometry::Circle::Move(const geometry::Vector &vec) {
  center_.Move(vec);
  return *this;
}

bool geometry::Circle::ContainsPoint(const geometry::Point &point) const {
  return EquationSubst(point) <= GetRadius() * GetRadius();
}

bool geometry::Circle::CrossesSegment(const geometry::Segment &to_check) const {
  int double_area = std::abs((to_check.GetStart() - GetCenter()) ^ (to_check.GetEnd() - GetCenter()));

  return double_area <= GetRadius() * to_check.Lenght() &&
         (EquationSubst(to_check.GetStart()) >= GetRadius() * GetRadius() ||
          EquationSubst(to_check.GetEnd()) >= GetRadius() * GetRadius());
}

geometry::Circle *geometry::Circle::Clone() const {
  return new Circle(*this);
}

std::string geometry::Circle::ToString() const {
  return "Circle(" + GetCenter().ToString() + ", " + std::to_string(GetRadius()) + ")";
}
