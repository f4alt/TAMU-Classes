#include "Component.h"
#include <iostream>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include <GLFW/glfw3.h>

using namespace std;

Component::Component(const std::shared_ptr<Shape> _cube,
                     const std::shared_ptr<Shape> _sphere) {
  cube = _cube;
  sphere = _sphere;
  selected = glm::vec3(1, 1, 1);
}

Component::~Component() {
  for (auto i : children) {
    delete i;
  }
}

void Component::updatePos(glm::vec3 _trans_from_parent,
               glm::vec3 _rot,
               glm::vec3 _trans_to_mesh,
               glm::vec3 _scale) {
  trans_from_parent = _trans_from_parent;
  rot = _rot;
  trans_to_mesh = _trans_to_mesh;
  scale = _scale;
}

Component* Component::selectChild(int position) {
  return children[position];
}

void Component::selected_pulse() {
  double t = glfwGetTime();
  double a = .05;
  double f = 2.0;
  selected = glm::vec3(1 + (a/2) + (a/2) * sin(2*3.14*f*t),
                       1 + (a/2) + (a/2) * sin(2*3.14*f*t),
                       1 + (a/2) + (a/2) * sin(2*3.14*f*t));
}

void Component::addChild(Component* child) {
  children.push_back(child);
}

void Component::updateRot(glm::vec3 _rot) {
  rot += _rot;
}

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


void Component::draw(const std::shared_ptr<Program> prog,
                     const std::shared_ptr<MatrixStack> MV,
                     const std::shared_ptr<MatrixStack> P) const {
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

     // draw slighty scaled down sphere at joint
     MV->pushMatrix();
     MV->scale(glm::vec3(.85, .85, .85));
     glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P->topMatrix()[0][0]);
     glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, &MV->topMatrix()[0][0]);
     sphere->draw(prog);
     MV->popMatrix();

     MV->pushMatrix();
         // Where is the current mesh with respect to currents joint
         MV->translate(trans_to_mesh);
         // currents scale
         MV->scale(scale * selected);
         // draw
         glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P->topMatrix()[0][0]);
         glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, &MV->topMatrix()[0][0]);
         cube->draw(prog);
     MV->popMatrix();
     // Draw children
     for (auto i : children) {
       i->draw(prog, MV, P);
     }
  MV->popMatrix();
}

int Component::DFS(int depth) {
  cout << depth << endl;
  if (children.size() == 0) {
    return 0;
  }
  for (int i=0; i < children.size(); i++) {
    children[i]->DFS(children.size() + i);
  }
}
