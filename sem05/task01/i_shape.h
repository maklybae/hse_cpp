#ifndef I_SHAPE
#define I_SHAPE

#include <string>

#include "vector.h"

namespace geometry {
class Point;
class Segment;

class IShape {
 public:
  virtual IShape& Move(const Vector&) = 0;
  virtual bool ContainsPoint(const Point&) const = 0;
  virtual bool CrossesSegment(const Segment&) const = 0;

  // Не используем умный указаетель, так как не является ковариантным
  // возвразаемым типом.
  // Проблема: https://github.com/CppCodeReviewers/Covariant-Return-Types-and-Smart-Pointers
  // В условиях жестко ограниченной иерархии классов никакие из решений нам не подходят.
  // Заметим, что в geometry_main.cpp присутствует delete после клонирования - ура!!!
  virtual IShape* Clone() const = 0;
  virtual std::string ToString() const = 0;

  virtual ~IShape() = default;
};
}  // namespace geometry
#endif