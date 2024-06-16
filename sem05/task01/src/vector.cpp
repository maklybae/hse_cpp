#include "../vector.h"

#include <string>

geometry::Vector geometry::Vector::operator+() const {
  return *this;
}
geometry::Vector geometry::Vector::operator-() const {
  return {-GetX(), -GetY()};
}

geometry::Vector geometry::operator+(const Vector& first, const Vector& second) {
  return {first.GetX() + second.GetX(), first.GetY() + second.GetY()};
}
geometry::Vector geometry::operator-(const Vector& first, const Vector& second) {
  return {first.GetX() - second.GetX(), first.GetY() - second.GetY()};
}

geometry::Vector geometry::operator*(int scalar, const Vector& vec) {
  return {scalar * vec.GetX(), scalar * vec.GetY()};
}
geometry::Vector geometry::operator*(const Vector& vec, int scalar) {
  return scalar * vec;
}
geometry::Vector geometry::operator/(const Vector& vec, int scalar) {
  return {vec.GetX() / scalar, vec.GetY() / scalar};
}

geometry::Vector& geometry::Vector::operator+=(const Vector& vec) {
  x_ += vec.GetX();
  y_ += vec.GetY();
  return *this;
}
geometry::Vector& geometry::Vector::operator-=(const Vector& vec) {
  x_ -= vec.GetX();
  y_ -= vec.GetY();
  return *this;
}
geometry::Vector& geometry::Vector::operator*=(int scalar) {
  x_ *= scalar;
  y_ *= scalar;
  return *this;
}
geometry::Vector& geometry::Vector::operator/=(int scalar) {
  x_ /= scalar;
  y_ /= scalar;
  return *this;
}

std::string geometry::Vector::ToString() const {
  return "Vector(" + std::to_string(GetX()) + ", " + std::to_string(GetY()) + ")";
}

bool geometry::operator==(const Vector& first, const Vector& second) {
  return first.GetX() == second.GetX() && first.GetY() == second.GetY();
}

int geometry::operator*(const Vector& first, const Vector& second) {
  return first.GetX() * second.GetX() + first.GetY() * second.GetY();
}

int geometry::operator^(const Vector& first, const Vector& second) {
  return first.GetX() * second.GetY() - first.GetY() * second.GetX();
}
