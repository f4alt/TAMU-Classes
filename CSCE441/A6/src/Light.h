#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <memory>
#include <glm/glm.hpp>

class Light
{
public:
	Light(glm::vec3 _lightPos,
        float _lightint)
  {
    lightPos = _lightPos;
    intensity = _lightint;
  }
	~Light();
  glm::vec3 getPos() { return lightPos; };
  float getIntensity() { return intensity; };
  void updatePos(char axis, bool forward) {
    float inc = .1;

    if (!forward) {
      inc = -inc;
    }

    if (axis == 'x' || axis == 'X') {
      lightPos.x += inc;
    } else if (axis == 'y' || axis == 'Y') {
      lightPos.y += inc;
    } else if (axis == 'z' || axis == 'Z') {
      lightPos.z += inc;
    }
  }
	void direction(const glm::vec3& q, glm::vec3& d, float& max_t) const {
    d = this->lightPos - q;
    max_t = sqrt(pow(d[0], 2.0) + pow(d[1], 2.0) + pow(d[2], 2.0));
		// max_t = std::numeric_limits<float>::infinity();
    d = normalize(d);
	}

private:
  glm::vec3 lightPos;
  float intensity;
};

#endif
