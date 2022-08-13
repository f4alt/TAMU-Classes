#include "Ellipsoid.h"
#include "Ray.h"
#include "MatrixStack.h"
#include <cmath>
#include <iostream>

bool Ellipsoid::intersect(const Ray& ray, const float min_t, float& t, glm::vec3& n) const
{
  // ellipse at .5, 1, 0 | scaled 1.0 should be
  /* mat4x4((0.693535, 0.639056, -0.332591, 0.000000),
            (-0.332591, 0.693535, 0.639056, 0.000000),
            (0.639056, -0.332591, 0.693535, 0.000000),
            (0.500000, 1.000000, 0.000000, 1.000000)) */
  // lazy conversion using L13 code
  auto M = std::make_shared<MatrixStack>();
	// M->translate(center[0], center[1], center[2]);
  M->translate(0.5, 0.0, 0.5);
	glm::vec3 axis = normalize(glm::vec3(1.0f, 1.0f, 1.0f));
	M->rotate(1.0f, axis);
	// M->scale(scale[0], scale[1], scale[2]);
  M->scale(0.5, 0.6, 0.2);
	glm::mat4 ellipsoid_E = M->topMatrix();
  // std::cout << ellipsoid_E[0][0] << ellipsoid_E[0][1] << ellipsoid_E[0][2] << ellipsoid_E[0][3] << std::endl;
  // std::cout << ellipsoid_E[1][0] << ellipsoid_E[1][1] << ellipsoid_E[1][2] << ellipsoid_E[1][3] << std::endl;
  // std::cout << ellipsoid_E[2][0] << ellipsoid_E[2][1] << ellipsoid_E[2][2] << ellipsoid_E[2][3] << std::endl;
  // std::cout << ellipsoid_E[3][0] << ellipsoid_E[3][1] << ellipsoid_E[3][2] << ellipsoid_E[3][3] << std::endl;


  glm::vec3 p_prime = inverse(ellipsoid_E) * glm::vec4(ray.origin, 1.0);
  glm::vec3 v_prime = inverse(ellipsoid_E) * glm::vec4(ray.direction, 0.0);
  glm::vec3 v_hat_prime = normalize(v_prime);

  float a = dot(v_hat_prime, v_hat_prime);
  float b = 2.0f * dot(v_hat_prime, p_prime);
  float c = dot(p_prime, p_prime) - 1.0;
  float d = pow(b, 2.0) - 4.0 * a * c;

  if (d > 0) {
    float t1 = (-b + sqrt(d)) / (2 * a);
    float t2 = (-b - sqrt(d)) / (2 * a);
    t = std::min(t1, t2);

    if (t >= min_t) {
      glm::vec3 x_prime = glm::vec3(p_prime) + t * v_hat_prime;
      glm::vec3 x = ellipsoid_E * glm::vec4(x_prime, 1.0);
      n = inverse(transpose(ellipsoid_E)) * glm::vec4(x_prime, 0.0);
      n = normalize(n);
      t = distance(x, glm::vec3(ray.origin));
      if (dot(ray.direction, (x-glm::vec3(ray.origin))) < 0) {
        t = -t;
      }
      return true;
    }
  }



  return false;
}
