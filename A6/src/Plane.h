#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane : public Object {
  public:
    glm::vec3 point;
    glm::vec3 normal;
  public:
    bool intersect(const Ray& ray,
                   const float min_t,
                   float& t,
                   glm::vec3& n) const;
};

#endif
