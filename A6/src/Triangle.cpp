#include <cmath>
#include <glm/glm.hpp>
#include <math.h>
#include <iostream>
#include "Triangle.h"
#include "Ray.h"

#define EPSILON 0.0001
#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2];

bool Triangle::intersect(const Ray& ray, const float min_t, float& t, glm::vec3& n) const {
  double u = 0;
  double v = 0;
  // lazy filter of triangle vertex
  float vert0[3];
  vert0[0] = vertices[0].x;
  vert0[1] = vertices[0].y;
  vert0[2] = vertices[0].z;
  float vert1[3];
  vert1[0] = vertices[1].x;
  vert1[1] = vertices[1].y;
  vert1[2] = vertices[1].z;
  float vert2[3];
  vert2[0] = vertices[2].x;
  vert2[1] = vertices[2].y;
  vert2[2] = vertices[2].z;
  // apply transformation E to ray

  float edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
  float det, inv_det;

  /* find vectors for two edges sharing vert0 */
  SUB(edge1, vert1, vert0);
  SUB(edge2, vert2, vert0);

  /* begin calculating determinant - also used to calculate U parameter */
  // CROSS(pvec, local_ray_dir, edge2);
  CROSS(pvec, ray.direction, edge2);

  /* if determinant is near zero, ray lies in plane of triangle */
  det = DOT(edge1, pvec);

  /* calculate distance from vert0 to ray origin */
  // SUB(tvec, local_ray_origin, vert0);
  SUB(tvec, ray.origin, vert0);
  inv_det = 1.0 / det;

  CROSS(qvec, tvec, edge1);

  if (det > EPSILON) {
     u = DOT(tvec, pvec);
     if (u < 0.0 || u > det)
      return false;

     /* calculate V parameter and test bounds */
     // v = DOT(local_ray_dir, qvec);
     v = DOT(ray.direction, qvec);
     if (v < 0.0 || u + v > det)
      return false;
  } else if (det < -EPSILON) {
     /* calculate U parameter and test bounds */
     u = DOT(tvec, pvec);
     if (u > 0.0 || u < det)
      return false;

     /* calculate V parameter and test bounds */
     // v = DOT(local_ray_dir, qvec) ;
     v = DOT(ray.direction, qvec);
     if (v > 0.0 || u + v < det)
      return false;
  } else return false;  /* ray is parallell to the plane of the triangle */

  u *= inv_det;
  v *= inv_det;
  float w = 1.0 - u - v;

  t = DOT(edge2, qvec) * inv_det;
  if (t < min_t) return false;
  CROSS(n, edge1, edge2);

  // glm::vec3 pos_interp;
  // pos_interp[0] = (vertices[0].x * u + vertices[0].y * v + vertices[0].z * w) / (u + v + w);
  // pos_interp[1] = (vertices[1].x * u + vertices[1].y * v + vertices[1].z * w) / (u + v + w);
  // pos_interp[2] = (vertices[2].x * u + vertices[2].y * v + vertices[2].z * w) / (u + v + w);


  // get normal
  // interpolate
  n[0] = (norm[0].x * w + norm[1].x * u + norm[2].x * v) / (u + v + w);
  n[1] = (norm[0].y * w + norm[1].y * u + norm[2].y * v) / (u + v + w);
  n[2] = (norm[0].z * w + norm[1].z * u + norm[2].z * v) / (u + v + w);
  // n = inverse(transpose(E)) * glm::vec4(n, 0.0);
  n = normalize(n);

  return true;
}
