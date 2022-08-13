#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Shape.h"
#include "Material.h"

class Program;
class MatrixStack;

class Component
{
public:
	Component(const std::shared_ptr<Shape> shape,
						const std::shared_ptr<Program> prog);
	~Component();
  void updatePos(glm::vec3 _trans_from_parent,
                 glm::vec3 _rot,
                 glm::vec3 _trans_to_mesh,
                 glm::vec3 _scale);
	void updateTfP(glm::vec3 _trans_from_parent);
  void addChild(Component* child);
  Component* selectChild(int position);
  void selected_pulse(double amplitude, double freq);
	void isBunny(bool yes);
	void isTeapot(bool yes);
	void isSphere(bool yes);
	void isVase(bool yes);
	void togAnim(bool yes);
	void selected_spin();
	void selected_shear();
  void updateRot(glm::vec3 _rot);
	void setShear(glm::mat4 _shear);
  void rotatePiece(char axis, bool forward);
	void drawFP(Material* material,
							const std::shared_ptr<MatrixStack> MV,
							const std::shared_ptr<MatrixStack> P) const;
  void draw(Material* material,
            const std::shared_ptr<MatrixStack> MV,
            const std::shared_ptr<MatrixStack> P) const;
	int maxDepth();
  Component* DFS(int* depth);

private:
  std::shared_ptr<Shape> shape;
  std::vector<Component*> children;
  glm::vec3 selected;
	bool spin_anim;
	bool shear_anim;
	bool anim;
	glm::mat4 shear;
	bool bunny;
	bool teapot;
	bool sphere;
	bool vase;
	std::shared_ptr<Program> prog;

  glm::vec3 trans_from_parent;
  glm::vec3 rot;
  glm::vec3 trans_to_mesh;
  glm::vec3 scale;
};

#endif
