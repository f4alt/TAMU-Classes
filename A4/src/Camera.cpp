#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "MatrixStack.h"

Camera::Camera() :
	aspect(1.0f),
	fovy((float)(45.0*M_PI/180.0)),
	znear(0.1f),
	zfar(1000.0f),
	rotations(0.0, 0.0),
	translations(0.0f, 0.0f, -5.0f),
	rfactor(0.01f),
	tfactor(0.001f),
	sfactor(0.005f),
	p(10.0f, 0.35f, 10.0f),
	f(sin(0.0f), 0.0f, cos(0.0f)),
	yaw(0.0f),
	pitch(0.0f),
	pitch_cap(60.0f),
	fovy_cap(20.0*M_PI/180.0, 100.0*M_PI/180.0)
{
}

Camera::~Camera()
{
}

void Camera::mouseClicked(float x, float y, bool shift, bool ctrl, bool alt)
{
	mousePrev.x = x;
	mousePrev.y = y;
	if(shift) {
		state = Camera::TRANSLATE;
	} else if(ctrl) {
		state = Camera::SCALE;
	} else {
		state = Camera::ROTATE;
	}
}

void Camera::mouseMoved(float x, float y)
{
	glm::vec2 mouseCurr(x, y);
	glm::vec2 dv = mouseCurr - mousePrev;
	switch(state) {
		case Camera::ROTATE:
			yaw -= rfactor * dv.x;
			f.x = sin(yaw);
			f.z = cos(yaw);

			pitch -= rfactor * dv.y;
			if (pitch > pitch_cap * rfactor) {
				pitch = pitch_cap * rfactor;
			}
			if (pitch < -pitch_cap * rfactor) {
				pitch = -pitch_cap * rfactor;
			}
			f.y = pitch;
			break;
		case Camera::TRANSLATE:
			translations.x -= translations.z * tfactor * dv.x;
			translations.y += translations.z * tfactor * dv.y;
			break;
		case Camera::SCALE:
			translations.z *= (1.0f - sfactor * dv.y);
			break;
	}
	mousePrev = mouseCurr;
}

void Camera::keyboardmove(char direction) {
	float incr = 0.1f;
	if (direction == 's' || direction == 'a' || direction == 'z') {
		incr *= -1;
	}

	glm::vec3 r = glm::cross(f, glm::vec3(0.0f, 1.0f, 0.0f));
	switch (direction) {
		case 'w':
		case 's':
		{
			p.x += incr * f.x;
			p.z += incr * f.z;
			break;
		}
		case 'a':
		case 'd':
		{
			p.x += incr * r.x;
			p.z += incr * r.z;
			break;
		}
		case 'z':
		case 'Z':
		{
			if (fovy+incr >= fovy_cap.x && fovy+incr <= fovy_cap.y) {
				fovy += incr;
			}
			break;
		}
		case 'u':
		{
			p.y += .01;
			break;
		}
		case 'y':
		{
			p.y -= .01;
			break;
		}
	}
}

void Camera::applyProjectionMatrix(std::shared_ptr<MatrixStack> P) const
{
	// Modify provided MatrixStack
	P->multMatrix(glm::perspective(fovy, aspect, znear, zfar));
}

void Camera::applyViewMatrix(std::shared_ptr<MatrixStack> MV) const
{
	glm::vec3 eye = p;
	glm::vec3 target = p + f;
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	MV->multMatrix(glm::lookAt(eye, target, up));
}

void Camera::applyProjectionMatrix_TD(std::shared_ptr<MatrixStack> P) const
{
	// Modify provided MatrixStack
	P->multMatrix(glm::ortho(-12.0, 12.0, -12.0, 12.0, -20.0, 20.0));
}

void Camera::applyViewMatrix_TD(std::shared_ptr<MatrixStack> MV) const
{
	MV->translate(9.0f, -9.0f, 0.0f);
	MV->rotate(M_PI/2, glm::vec3(1.0f, 0.0f, 0.0f));
	MV->rotate(M_PI, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::applyFrustumInvView(float a, std::shared_ptr<MatrixStack> MV) const {
	glm::vec3 eye = p;
	glm::vec3 target = p + f;
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	// apply inverse camera
	MV->multMatrix(glm::inverse(glm::lookAt(eye, target, up)));

	// apply scale for fov
	float sx = a * tan(fovy/2);
	float sy = tan(fovy/2);
	glm::mat4 S(1.0f);
	S[0][0] = sx;
	S[0][1] = sy;
	MV->multMatrix(S);
}
