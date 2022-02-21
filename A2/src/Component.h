#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Shape.h"

class Program;
class MatrixStack;

class Component
{
public:
	Component(const std::shared_ptr<Shape> cube,
            const std::shared_ptr<Shape> sphere);
	~Component();
  void updatePos(glm::vec3 _trans_from_parent,
                 glm::vec3 _rot,
                 glm::vec3 _trans_to_mesh,
                 glm::vec3 _scale);
  void addChild(Component* child);
  Component* selectChild(int position);
  void selected_pulse();
  void updateRot(glm::vec3 _rot);
  void rotatePiece(char axis, bool forward);
  void draw(const std::shared_ptr<Program> prog,
            const std::shared_ptr<MatrixStack> MV,
            const std::shared_ptr<MatrixStack> P) const;
  int DFS(int depth);

private:
  std::shared_ptr<Shape> cube;
  std::shared_ptr<Shape> sphere;
  std::vector<Component*> children;
  glm::vec3 selected;

  glm::vec3 trans_from_parent;
  glm::vec3 rot;
  glm::vec3 trans_to_mesh;
  glm::vec3 scale;
};

#endif
