#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <memory>
#include <glm/glm.hpp>

class Light
{
public:
	Light(glm::vec3 _lightPos,
        glm::vec3 _lightCol)
  {
    lightPos = _lightPos;
    lightCol = _lightCol;
  }
	~Light();
  glm::vec3 getPos() { return lightPos; };
  glm::vec3 getCol() { return lightCol; };
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

private:
  glm::vec3 lightPos;
  glm::vec3 lightCol;
};

#endif
