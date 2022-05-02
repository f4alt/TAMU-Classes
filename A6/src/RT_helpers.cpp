#include <iostream>
#include "RT_helpers.h"
#include "MatrixStack.h"
#include "Sphere.h"

bool check_bb(const Ray ray,
              const float min_t,
              float t,
              glm::vec3 n,
              Sphere* bb) {
  // Task 4: Find scaled/translated sphere intersection(s)
  glm::vec3 line = ray.origin - bb->center;   // world coords
  float a = dot(ray.direction, ray.direction);
  float b = 2.0f * dot(ray.direction, line);
  float c = dot(line, line) - pow(bb->radius, 2.0);
  float d = pow(b, 2.0) - (4 * a * c);    // b^2 - 4ac
  float internal_t;

  if (d > 0) {
    float t1 = (-b + sqrt(d)) / (2.0 * a);
    float t2 = (-b - sqrt(d)) / (2.0 * a);
    internal_t = std::min(t1, t2);
  }

  if (internal_t >= min_t) {
    return true;
  }

  return false;
}

bool first_hit(
     const Ray& ray,
     const float min_t,
     const std::vector<Object*>& objects,
     int& hit_id,
     float& t,
     glm::vec3& n) {

  float temp_t = 0;
  t = 0;
  glm::vec3 temp_n;
  unsigned i = 0;
  bool hit = false;

  for (const auto & ob : objects) {
    if (ob->intersect(ray, min_t, temp_t, temp_n)) {
       if (temp_t < t || t == 0) {
           t = temp_t;
           n = temp_n;
           hit_id = i;
           hit = true;
       }
    }
    i++;
  }

  return hit;
}

glm::vec3 blinn_phong_shading(
          const Ray& ray,
          const int& hit_id,
          const float& t,
          const glm::vec3 & n,
          const std::vector<Object*> & objects,
          const std::vector<Light*> & lights) {
  glm::vec3 rgb = glm::vec3(0, 0, 0);

  glm::vec3 half;
  glm::vec3 dir;
  glm::vec3 norm_check;

  glm::vec3 point = ray.origin + t * ray.direction;
  float max_t;
  Ray check;
  check.origin = point;
  int hit_check;
  float t_check;

  // set ambient component
  rgb[0] += objects[hit_id]->material->ka[0] * 0.1;
  rgb[1] += objects[hit_id]->material->ka[1] * 0.1;
  rgb[2] += objects[hit_id]->material->ka[2] * 0.1;


  for (auto & light : lights){
    // Check for shadow from light source
    light->direction(point, dir, max_t);

    if (objects[hit_id]->Ell) {
      auto M = std::make_shared<MatrixStack>();
      M->translate(0.5, 0.0, 0.5);
      glm::vec3 axis = normalize(glm::vec3(1.0f, 1.0f, 1.0f));
      M->rotate(1.0f, axis);
      M->scale(0.5, 0.6, 0.2);
      glm::mat4 E = M->topMatrix();
      point = glm::inverse(E) * glm::vec4(point, 1.0);
      dir = glm::inverse(E) * glm::vec4(dir, 0.0);
      dir = glm::normalize(dir);
    }
    check.direction = dir;

    if (first_hit(check, 1e-6, objects, hit_check, t_check, norm_check)) {
      if (t_check < max_t) {
        // std::cout << "t_check:" << t_check << " | max_t:" << max_t << std::endl;
        continue;
      }
    }

    // Calc half vector
    half = normalize((normalize(-ray.direction) + dir));

    // Calc Lambertian
    rgb += (((objects[hit_id]->material->kd) * std::max(0.0f, dot(n, dir))) * (light->getIntensity()));

    // Calc Specular
    float exp = objects[hit_id]->material->exponent;
    glm::vec3 temp = glm::vec3(
            objects[hit_id]->material->ks[0] * std::pow(std::max(0.0f, dot(n, half)), exp),
            objects[hit_id]->material->ks[1] * std::pow(std::max(0.0f, dot(n, half)), exp),
            objects[hit_id]->material->ks[2] * std::pow(std::max(0.0f, dot(n, half)), exp));

    rgb += (temp * light->getIntensity());
  }

  return rgb;
}

bool shootRay(
  const Ray& ray,
  const float min_t, // should be sent in 1.0 for initial call
  const std::vector<Object*>& objects,
  const std::vector<Light*>& lights,
  const int num_recursive_calls,
  glm::vec3& rgb) {

  // reset rgb
  rgb = glm::vec3(0.0);

  int hit_id;
  float t;
  glm::vec3 normal;

  if (first_hit(ray, min_t, objects, hit_id, t, normal) && num_recursive_calls < 5) {
    // std::cout << "HIT" << std::endl;
    // find ray colour using blinn_phong
    rgb += blinn_phong_shading(ray, hit_id, t, normal, objects, lights);
    // rgb += normal;
    // std::cout << rgb[0] << " " << rgb[1] << " " << rgb[2] << std::endl;

    if (objects[hit_id]->material->km[0] > 1e-5 &&
        objects[hit_id]->material->km[1] > 1e-5 &&
        objects[hit_id]->material->km[2] > 1e-5) {
        // Generate reflected ray
        Ray ray_reflect;
        ray_reflect.direction = reflect(ray.direction, normalize(normal));
        ray_reflect.origin = ray.origin + t * ray.direction;

        // recursively call shootRay
        glm::vec3 reflect;
        shootRay(ray_reflect, 1e-4, objects, lights, (num_recursive_calls + 1), reflect);
        rgb += (objects[hit_id]->material->km * reflect);
        return true;
    }


  } else if ( num_recursive_calls > 0 ) {
    return true;
  }

  return false;
}
