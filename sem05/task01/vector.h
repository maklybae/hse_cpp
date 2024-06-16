#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <string>

namespace geometry {
class Vector {
 private:
  int x_{};
  int y_{};

 public:
  Vector() = default;
  Vector(int x, int y) : x_{x}, y_{y} {
  }
  Vector(const Vector&) = default;
  Vector(Vector&&) = default;
  Vector& operator=(Vector&&) = default;
  Vector& operator=(const Vector&) = default;

  int GetX() const {
    return x_;
  }
  int GetY() const {
    return y_;
  }
  double Length() const {
    return std::sqrt(x_ * x_ + y_ * y_);
  }

  Vector operator+() const;
  Vector operator-() const;

  Vector& operator+=(const Vector&);
  Vector& operator-=(const Vector&);
  Vector& operator*=(int);
  Vector& operator/=(int);

  std::string ToString() const;

  ~Vector() = default;
};

Vector operator+(const Vector&, const Vector&);
Vector operator-(const Vector&, const Vector&);

Vector operator*(const Vector&, int);
Vector operator*(int, const Vector&);
Vector operator/(const Vector&, int);

bool operator==(const Vector&, const Vector&);
int operator*(const Vector&, const Vector&);
int operator^(const Vector&, const Vector&);

}  // namespace geometry
#endif