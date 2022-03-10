#include "Component.h"
#include <iostream>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

// constructor with two shapes
Component::Component(const std::shared_ptr<Shape> _cube,
                     const std::shared_ptr<Shape> _sphere) {
  cube = _cube;
  sphere = _sphere;
  spin_anim = false;
  shear_anim = false;
  selected = glm::vec3(1, 1, 1);
  shear = glm::mat4(1.0f);
}

// deconstructor
Component::~Component() {
  for (auto i : children) {
    delete i;
  }
}

// updates all movement matricies
void Component::updatePos(glm::vec3 _trans_from_parent,
                          glm::vec3 _rot,
                          glm::vec3 _trans_to_mesh,
                          glm::vec3 _scale) {
  trans_from_parent = _trans_from_parent;
  rot = _rot;
  trans_to_mesh = _trans_to_mesh;
  scale = _scale;
}

// returns component of parent at position
Component* Component::selectChild(int position) {
  return children[position];
}

// pulses selected element using sin wave
void Component::selected_pulse() {
  double t = glfwGetTime();
  double a = .05;
  double f = 2.0;
  selected = glm::vec3(1 + (a/2) + (a/2) * sin(2*3.14*f*t),
                       1 + (a/2) + (a/2) * sin(2*3.14*f*t),
                       1 + (a/2) + (a/2) * sin(2*3.14*f*t));
}

// toggles spin selection
void Component::selected_spin() {
  spin_anim = !spin_anim;
}

void Component::setShear(glm::mat4 _shear) {
  shear = _shear;
}

// toggles shear selection
void Component::selected_shear() {
  shear_anim = !shear_anim;
}

// adds child to element
void Component::addChild(Component* child) {
  children.push_back(child);
}

// updates rotation matrix by given matrix
void Component::updateRot(glm::vec3 _rot) {
  rot += _rot;
}

// rotates piece around desired axis by .1
void Component::rotatePiece(char axis, bool forward) {
  double spin = .1;

  if (!forward) {
    spin = -spin;
  }

  if (axis == 'x' || axis == 'X') {
    rot.x += spin;
  } else if (axis == 'y' || axis == 'Y') {
    rot.y += spin;
  } else if (axis == 'z' || axis == 'Z') {
    rot.z += spin;
  }
}

// recursively draws elemet and children
void Component::draw(const std::shared_ptr<Program> prog,
                     Material* material,
                     const std::shared_ptr<MatrixStack> MV,
                     const std::shared_ptr<MatrixStack> P) const {

  double t = glfwGetTime();
  glm::vec3 lights_vec[4];
  MV->pushMatrix();
     // Where is the current joint with respect to the parent
     MV->translate(trans_from_parent);
     // filter rotation
     if (rot.x != 0) {
       MV->rotate(rot.x, 1, 0, 0);
     }
     if (rot.y != 0) {
       MV->rotate(rot.y, 0, 1, 0);
     }
     if (rot.z != 0) {
       MV->rotate(rot.z, 0, 0, 1);
     }

     MV->pushMatrix();
       // component specific spin animation
       if (spin_anim) {
         MV->rotate(t, 0, 1, 0);
       }

       // component specific shear animation
       if (shear_anim) {
         glm::mat4 S(1.0f);
         S[0][1] = -0.5f*cos(t);
         MV->multMatrix(S);
       } else {
         MV->multMatrix(shear);
       }

       MV->pushMatrix();
           // Where is the current mesh with respect to currents joint
           MV->translate(trans_to_mesh);
           // currents scale
           MV->scale(scale);
           // currents shear
           // draw
           glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P->topMatrix()[0][0]);
           glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, &MV->topMatrix()[0][0]);
           auto MVit = glm::transpose(glm::inverse(MV->topMatrix()));
           glUniformMatrix4fv(prog->getUniform("MVit"), 1, GL_FALSE, glm::value_ptr(MVit));
           material->fillLights(lights_vec);
           glUniform3fv(prog->getUniform("lightInfo"), 4, glm::value_ptr(lights_vec[0]));
           glUniform3fv(prog->getUniform("ka"), 1, glm::value_ptr(material->getKa()));
           glUniform3fv(prog->getUniform("kd"), 1, glm::value_ptr(material->getKd()));
           glUniform3fv(prog->getUniform("ks"), 1, glm::value_ptr(material->getKs()));
           glUniform1f(prog->getUniform("s"), material->getS());
           cube->draw(prog);
       MV->popMatrix();
     MV->popMatrix();
     // Draw children
     for (auto i : children) {
       i->draw(prog, material, MV, P);
     }
  MV->popMatrix();
}

// returns max depth of tree
int Component::maxDepth() {
  int depth = 0;
  if (children.empty()) {
    return 0;
  }
  depth += children.size();
  for (auto i : children) {
    depth += i->maxDepth();
  }
  return depth;
}

// returns component at desired depth
Component* Component::DFS(int* depth) {
  Component* ret;
  if (*depth == 0) {
    return this;
  }
  if (*depth > 0 && children.empty()) {
    return nullptr;
  }
  for (size_t i=0; i < children.size() && *depth > 0; i++) {
    *depth -= 1;
    ret = children[i]->DFS(depth);
  }
  return ret;
}
