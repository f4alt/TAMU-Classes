#include "Sphere.h"
#include "Ray.h"
#include <cmath>

bool Sphere::intersect(const Ray& ray, const float min_t, float& t, glm::vec3& n) const
{
  // Task 4: Find scaled/translated sphere intersection(s)
  glm::vec3 line = ray.origin - this->center;   // world coords
  float a = dot(ray.direction, ray.direction);
  float b = 2.0f * dot(ray.direction, line);
  float c = dot(line, line) - pow(this->radius, 2.0);
  float d = pow(b, 2.0) - (4 * a * c);    // b^2 - 4ac

  if (d > 0) {
    float t1 = (-b + sqrt(d)) / (2.0 * a);
    float t2 = (-b - sqrt(d)) / (2.0 * a);
    t = std::min(t1, t2);
  }

  if (t >= min_t) {
    n = (ray.origin + t * ray.direction) - this->center;
    n = normalize(n);
    return true;
  }

  return false;
}
