#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

using namespace std;

Camera::Camera() :
	position(0.0f, 0.0f, 5.0f),
	rotations(0.0f, 0.0f),
	fov((float)(45.0*M_PI/180.0)),
	aspect(1.0f),
	width(512.0f),
	height(512.0f),
	imagePlaneDist(1.0f)
{
}

Camera::~Camera()
{
}

Ray Camera::genRay(int row, int col) {
	float fov_scale = tan(fov/2) * imagePlaneDist * 2;

	glm::vec3 dir;
	dir[0] = (((width-1) / 2.0) - row) * (fov_scale / width);
	dir[1] = (((height-1) / 2.0) - col) * (fov_scale / height);
  dir[2] = position.z - imagePlaneDist;

	Ray ray;
	ray.origin = position;
	ray.direction = normalize(dir - position);

	return ray;
}
