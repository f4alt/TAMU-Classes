#include "Plane.h"
#include "Ray.h"
#include <cmath>

#define MARGIN 1e-5

bool Plane::intersect( const Ray& ray, const float min_t, float& t, glm::vec3& n) const {
  // Using parametric equation of plane, calculate intersection
  float denom = dot(this->normal, ray.direction);

  if (std::abs(denom) > MARGIN) {
    float num = dot(this->normal, this->point - ray.origin);
    t = num / denom;
    if (t >= min_t) {
      n = normalize(this->normal);
      return true;
    }
  }

  return false;
}
