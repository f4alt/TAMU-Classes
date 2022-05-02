#include "Component.h"
#include <iostream>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

// constructor with two shapes
Component::Component(const std::shared_ptr<Shape> _shape,
                     const std::shared_ptr<Program> _prog) {
  shape = _shape;
  prog = _prog;
  spin_anim = false;
  shear_anim = false;
  anim = false;
  selected = glm::vec3(1, 1, 1);
  shear = glm::mat4(1.0f);
  bunny = false;
  teapot = false;
  sphere = false;
  vase = false;
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

// updates translation from parent
void Component::updateTfP(glm::vec3 _trans_from_parent) {
  trans_from_parent = _trans_from_parent;
}

// returns component of parent at position
Component* Component::selectChild(int position) {
  return children[position];
}

// pulses selected element using sin wave
void Component::selected_pulse(double a, double f) {
  double t = glfwGetTime();
  selected = glm::vec3(1 + (a/2) + (a/2) * sin(2*3.14*f*t));

  glm::vec3 offset(scale * selected);
  if (!bunny) {
    trans_to_mesh.y = -trans_from_parent.y -.186996 + (1.0 - offset.y) * .333099;
  }
}

void Component::isBunny(bool yes) {
  bunny = yes;
}

void Component::isTeapot(bool yes) {
  teapot = yes;
}

void Component::isSphere(bool yes) {
  sphere = yes;
}

void Component::isVase(bool yes) {
  vase = yes;
}

void Component::togAnim(bool yes) {
  anim = yes;
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

// draws first pass with minimal inputs and outputs to texture
void Component::drawFP(Material* material,
                       const std::shared_ptr<MatrixStack> MV,
                       const std::shared_ptr<MatrixStack> P) const {
  prog->bind();
  double t = glfwGetTime() * scale.x * 2;
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
       if (bunny && anim) {
         MV->rotate(t, 0, 1, 0);
       }

       // component specific shear animation
       if (teapot && anim) {
         glm::mat4 S(1.0f);
         S[1][2] = -0.5f*cos(t);
         MV->multMatrix(S);
       } else {
         MV->multMatrix(shear);
       }

       if (sphere && anim) {
         // translate MV
         float ay = 1.3;
         float as = 0.5;
         float p = 5.0;
         float t0 = 0.9;
         float y_trans = ay * (0.5 * sin((2 * M_PI / p) * (t + t0)) + 0.5);
         float squash_stretch = -as * (0.5 * cos((4 * M_PI / p) * (t + t0)) + 0.5) + 1;
         glm::vec3 bounce(0.0, y_trans, 0.0);
         glm::vec3 deform(squash_stretch, 1.0, squash_stretch);
         MV->translate(bounce);
         MV->scale(deform);
       }

       MV->pushMatrix();
           // Where is the current mesh with respect to currents joint
           MV->translate(trans_to_mesh);
           // currents scale
           MV->scale(scale * selected);

           // draw
           glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
         	 glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
         	 auto MVit = glm::transpose(glm::inverse(MV->topMatrix()));
         	 glUniformMatrix4fv(prog->getUniform("MVit"), 1, GL_FALSE, glm::value_ptr(MVit));
         	 glUniform3fv(prog->getUniform("ke"), 1, glm::value_ptr(material->getKa()));
         	 glUniform3fv(prog->getUniform("kd"), 1, glm::value_ptr(material->getKd()));
           if (vase && anim) {
             glUniform1f(prog->getUniform("t"), t*3);
           }
         	 shape->draw(prog);
       MV->popMatrix();
     MV->popMatrix();

  MV->popMatrix();
  prog->unbind();
}

// recursively draws elemet and children
void Component::draw(Material* material,
                     const std::shared_ptr<MatrixStack> MV,
                     const std::shared_ptr<MatrixStack> P) const {
  prog->bind();
  double t = glfwGetTime() * scale.x * 2;
  glm::vec3 lights_vec[4];
  MV->pushMatrix();

  material->fillLights(lights_vec, MV->topMatrix());
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
       if (bunny && anim) {
         MV->rotate(t, 0, 1, 0);
       }

       // component specific shear animation
       if (teapot && anim) {
         glm::mat4 S(1.0f);
         S[1][2] = -0.5f*cos(t);
         MV->multMatrix(S);
       } else {
         MV->multMatrix(shear);
       }

       if (sphere && anim) {
         // translate MV
         float ay = 1.3;
         float as = 0.5;
         float p = 5.0;
         float t0 = 0.9;
         float y_trans = ay * (0.5 * sin((2 * M_PI / p) * (t + t0)) + 0.5);
         float squash_stretch = -as * (0.5 * cos((4 * M_PI / p) * (t + t0)) + 0.5) + 1;
         glm::vec3 bounce(0.0, y_trans, 0.0);
         glm::vec3 deform(squash_stretch, 1.0, squash_stretch);
         MV->translate(bounce);
         MV->scale(deform);
       }

       MV->pushMatrix();
           // Where is the current mesh with respect to currents joint
           MV->translate(trans_to_mesh);
           // currents scale
           MV->scale(scale * selected);

           // draw
           glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P->topMatrix()[0][0]);
           glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, &MV->topMatrix()[0][0]);
           auto MVit = glm::transpose(glm::inverse(MV->topMatrix()));
           glUniformMatrix4fv(prog->getUniform("MVit"), 1, GL_FALSE, glm::value_ptr(MVit));
           glUniform3fv(prog->getUniform("lightInfo"), material->getNumLights() * 2, glm::value_ptr(lights_vec[0]));
           glUniform3fv(prog->getUniform("ka"), 1, glm::value_ptr(material->getKa()));
           glUniform3fv(prog->getUniform("kd"), 1, glm::value_ptr(material->getKd()));
           glUniform3fv(prog->getUniform("ks"), 1, glm::value_ptr(material->getKs()));
           if (anim) {
             glUniform1f(prog->getUniform("t"), t*3);
           }
           glUniform1f(prog->getUniform("s"), material->getS());
           shape->draw(prog);
       MV->popMatrix();
     MV->popMatrix();

     // recursive draw children
     for (auto i : children) {
       i->draw(material, MV, P);
     }
  MV->popMatrix();
  prog->unbind();
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
