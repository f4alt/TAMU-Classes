#include <glm/glm.hpp>
#include <iostream>

#include "TriangleMesh.h"
#include "Triangle.h"
#include "RT_helpers.h"

bool TriangleMesh::intersect(
  const Ray & ray, const float min_t, float& t, glm::vec3& n) const {
    int hit_id;

    // if (check_bb(ray, min_t, t, n, this->bb)) {
      return first_hit(ray, min_t, this->triangles, hit_id , t, n);
    // } else return false;
}
