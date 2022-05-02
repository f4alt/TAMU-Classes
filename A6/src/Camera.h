#pragma  once
#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Ray.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();
	void setInitDistance(glm::vec3 _pos) { position = _pos; }
	void setRotation(glm::vec2 _rot) { rotations = _rot; }
	void setFOV(float _fov) { fov = _fov; }
	void setAspect(float a) { aspect = a; };
	void setDimensions(float _width, float _height) { width = _width; height = _height; }
	void setImagePlaneDist(float dist) { imagePlaneDist = dist; }

	Ray genRay(int row, int col);


private:
	glm::vec3 position;
	glm::vec2 rotations;
	float fov;
	float aspect;
	float width;
	float height;

	float imagePlaneDist;	// dist from camera origin
};

#endif
