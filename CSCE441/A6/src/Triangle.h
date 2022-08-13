#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>
#include <vector>
#include <climits>
#include <cfloat>
#include "Object.h"

struct vtex {
	float x, y, z;
};

class Triangle : public Object
{
  public:
    std::vector<vtex> vertices;
    std::vector<vtex> norm;

    bool intersect (
      const Ray & ray, const float min_t, float& t, glm::vec3 & n) const;
};

#endif
