#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

struct Material {
  glm::vec3 ka;
  glm::vec3 kd;
  glm::vec3 ks;
  glm::vec3 km = glm::vec3(0.0);

  float exponent;
};
#endif
