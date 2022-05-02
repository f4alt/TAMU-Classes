#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "Object.h"
#include "Sphere.h"
#include <memory>
#include <vector>
#include <glm/glm.hpp>

// Forward declaration
class Triangle;
class TriangleMesh : public Object
{
  public:
    std::vector<Object*> triangles;       // mesh collection of triangles
    // std::vector<Object*> boundingSphere;  // just one sphere, but hit function takes a vector so this simplifies things
    Sphere* bb;

    bool intersect(
      const Ray& ray, const float min_t, float& t, glm::vec3& n) const;
};

#endif
