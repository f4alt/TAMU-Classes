#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include <memory>

struct Ray;

class Object {
  public:
    bool Ell = false;
    Material* material;
    virtual ~Object() {}
    virtual bool intersect(const Ray & ray,
                           const float min_t,
                           float& t,
                           glm::vec3& n) const = 0;
};

#endif
