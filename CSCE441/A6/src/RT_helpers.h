#ifndef RT_HELPERS_H
#define RT_HELPERS_H

#include <glm/glm.hpp>
#include <vector>
#include "Ray.h"
#include "Object.h"
#include "Light.h"
#include "Sphere.h"

#define MARGIN .00001

// class RT_helpers {

  bool check_bb(const Ray ray,
                const float min_t,
                float t,
                glm::vec3 n,
                Sphere* bb);

  bool shootRay(
      const Ray& ray,
      const float min_t, // should be sent in 1.0 for initial call
      const std::vector<Object*>& objects,
      const std::vector<Light*>& lights,
      const int num_recursive_calls,
      glm::vec3& rgb);

  bool first_hit(
       const Ray& ray,
       const float min_t,
       const std::vector<Object*> & objects,
       int& hit_id,
       float& t,
       glm::vec3& n);

   glm::vec3 blinn_phong_shading(
        const Ray& ray,
        const int& hit_id,
        const float& t,
        const glm::vec3 & n,
        const std::vector<Object*> & objects,
        const std::vector<Light*> & lights);


// };


#endif
