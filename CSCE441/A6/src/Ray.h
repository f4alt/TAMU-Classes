#pragma  once
#ifndef RAY_H
#define RAY_H

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

struct Ray {
	glm::vec3 origin;
	glm::vec3 direction;
};

#endif
