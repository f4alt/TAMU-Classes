#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "Object.h"

class Ellipsoid : public Object {
  public:
    glm::vec3 center;
    glm::vec3 scale;
  public:
    bool intersect(const Ray& ray,
                   const float min_t,
                   float& t,
                   glm::vec3& n) const;
};

#endif
