#include "../line.h"

#include <numeric>
#include <string>
#include <tuple>

#include "../point.h"
#include "../segment.h"

std::tuple<int, int, int> geometry::Line::GetEquation() const {
  int a = GetFirst().GetY() - GetSecond().GetY();
  int b = GetSecond().GetX() - GetFirst().GetX();
  int c = -GetSecond().GetY() * b - GetSecond().GetX() * a;
  int gcd = std::gcd(a, std::gcd(b, c));
  if (a < 0) {
    gcd *= -1;
  }
  return std::make_tuple(a / gcd, b / gcd, c / gcd);
}

geometry::Line &geometry::Line::Move(const Vector &vec) {
  first_.Move(vec);
  second_.Move(vec);
  return *this;
}

bool geometry::Line::ContainsPoint(const Point &point) const {
  auto coef = GetEquation();
  return std::get<0>(coef) * point.GetX() + std::get<1>(coef) * point.GetY() + std::get<2>(coef) == 0;
}

bool geometry::Line::CrossesSegment(const Segment &to_check) const {
  auto area_sign{[](const Point &first, const Point &second, const Point &third) {
    int area = (second.GetX() - first.GetX()) * (third.GetY() - first.GetY()) -
               (second.GetY() - first.GetY()) * (third.GetX() - first.GetX());
    return area > 0 ? 1 : (area < 0 ? -1 : 0);  // Знак area -1, 0, +1
  }};
  return area_sign(this->GetFirst(), this->GetSecond(), to_check.GetStart()) *
             area_sign(this->GetFirst(), this->GetSecond(), to_check.GetEnd()) <=
         0;
}

geometry::Line *geometry::Line::Clone() const {
  return new Line(*this);
}

std::string geometry::Line::ToString() const {
  auto coef = GetEquation();
  return "Line(" + std::to_string(std::get<0>(coef)) + ", " + std::to_string(std::get<1>(coef)) + ", " +
         std::to_string(std::get<2>(coef)) + ")";
}
