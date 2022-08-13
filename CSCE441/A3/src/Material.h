#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "Light.h"

class Material
{
public:
	Material();
  Material(std::vector<Light*> _lights,
           glm::vec3 _ka,
           glm::vec3 _kd,
           glm::vec3 _ks,
           float _s)
  { lights = _lights;
    ka = _ka;
    kd = _kd;
    ks = _ks;
    s = _s;
  }
	~Material();
  void fillLights(glm::vec3* lights_vec) {
    lights_vec[0] = lights[0]->getPos();
    lights_vec[1] = lights[0]->getCol();
    lights_vec[2] = lights[1]->getPos();
    lights_vec[3] = lights[1]->getCol();
  }
  glm::vec3 getKa() { return ka; };
  glm::vec3 getKd() { return kd; };
  glm::vec3 getKs() { return ks; };
  float getS() { return s; };
  void updateParams(std::vector<Light*> _lights,
                    glm::vec3 _ka,
                    glm::vec3 _kd,
                    glm::vec3 _ks,
                    float _s)
  { lights = _lights;
    ka = _ka;
    kd = _kd;
    ks = _ks;
    s = _s;
  }
  void updateLightPos(int light, char axis, bool forward) {
    lights[light]->updatePos(axis, forward);
  };
  void updateKa(glm::vec3 _ka) { ka = _ka; };
  void updateKd(glm::vec3 _kd) { kd = _kd; };
  void updateKs(glm::vec3 _ks) { ks = _ks; };
  void updateS(float _s) { s = _s; };

private:
  std::vector<Light*> lights;
  glm::vec3 ka;
  glm::vec3 kd;
  glm::vec3 ks;
  float s;
};

#endif
