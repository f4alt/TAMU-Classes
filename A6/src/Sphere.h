#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere : public Object {
  public:
    glm::vec3 center;
    float radius;
  public:
    bool intersect(const Ray& ray,
                   const float min_t,
                   float& t,
                   glm::vec3& n) const;
};

#endif
