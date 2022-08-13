// #include <glm/glm.hpp>
// #include "first_hit.h"
// #include "blinn_phong_shading.h"
// #include "reflect.h"
// #include "Sphere.h"
// #include "PointLight.h"
//
// #define MARGIN .00001
//
// bool shootRay(
//   const Ray& ray,
//   const float min_t, // should be sent in 1.0 for initial call
//   const std::vector<Object*>& objects,
//   const std::vector<Light*>& lights,
//   const int num_recursive_calls,
//   glm::vec3& rgb) {
//
//   // reset rgb
//   rgb = glm::vec3(0.0);
//
//   int hit_id;
//   float t;
//   glm::vec3 normal;
//
//   if (first_hit(ray, min_t, objects, hit_id, t, normal) && num_recursive_calls < 5) {
//     // find ray colour using blinn_phong
//     rgb += blinn_phong_shading(ray, hit_id, t, normal, objects, lights);
//
//     if (objects[hit_id]->material->km[0] > MARGIN &&
//         objects[hit_id]->material->km[1] > MARGIN &&
//         objects[hit_id]->material->km[2] > MARGIN) {
//         // Generate reflected ray
//         Ray ray_reflect;
//         ray_reflect.direction = reflect(ray.direction, normal.normalized());
//         ray_reflect.origin = ray.origin + t * ray.direction;
//         // Generate refracted ray
//         //Ray ray_refract;
//
//         // recursively call shootRay
//         glm::vec3 reflect;
//         shootRay(ray_reflect, MARGIN, objects, lights, (num_recursive_calls + 1), reflect);
//         rgb += (objects[hit_id]->material->km.array() * reflect.array()).matrix();
//         return true;
//     }
//
//
//   } else if ( num_recursive_calls > 0 ) {
//     return true;
//   }
//
//   return false;
// }
