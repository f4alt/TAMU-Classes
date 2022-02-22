#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLSL.h"
#include "MatrixStack.h"
#include "Program.h"
#include "Shape.h"
#include "Component.h"

using namespace std;

GLFWwindow *window; // Main application window
string RES_DIR = ""; // Where data files live
shared_ptr<Program> prog;
shared_ptr<Program> progIM; // immediate mode
shared_ptr<Shape> shape;
shared_ptr<Shape> joint;
// shared_ptr<Component> root_comp;
Component* root_comp;
Component* curr_comp;
int depth=0;

static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	switch (codepoint) {
		case 'x':
		case 'y':
		case 'z':
			curr_comp->rotatePiece(codepoint, false);
			break;
		case 'X':
		case 'Y':
		case 'Z':
			curr_comp->rotatePiece(codepoint, true);
			break;
		case '.':
		{
			depth++;
			if (depth > root_comp->maxDepth()) {
				depth = 0;
			}
			int* _depth = new int(depth);
			curr_comp = root_comp->DFS(_depth);
			break;
		}
		case ',':
		{
			depth--;
			if (depth < 0) {
				depth = root_comp->maxDepth();
			}
			int* _depth = new int(depth);
			curr_comp = root_comp->DFS(_depth);
		}
	}
}

static void init()
{
	GLSL::checkVersion();

	// Check how many texture units are supported in the vertex shader
	int tmp;
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &tmp);
	cout << "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = " << tmp << endl;
	// Check how many uniforms are supported in the vertex shader
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &tmp);
	cout << "GL_MAX_VERTEX_UNIFORM_COMPONENTS = " << tmp << endl;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &tmp);
	cout << "GL_MAX_VERTEX_ATTRIBS = " << tmp << endl;

	// Set background color.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

	// Initialize mesh.
	shape = make_shared<Shape>();
	shape->loadMesh(RES_DIR + "cube.obj");
	shape->init();

	joint = make_shared<Shape>();
	joint->loadMesh(RES_DIR + "sphere.obj");
	joint->init();

	// root component with cube shape and sphere joint
	// initialize all starting positions
	root_comp = new Component(shape, joint);
	root_comp->updatePos(glm::vec3(0, 2, -10),
										 	 glm::vec3(0, 0, 0),
											 glm::vec3(0, 0, 0),
											 glm::vec3(2, 3, 1));

	Component* head = new Component(shape, joint);
	head->updatePos(glm::vec3(0, 1.5, 0),
							    glm::vec3(0, 0, 0),
							    glm::vec3(0, .5, 0),
								  glm::vec3(1, 1, 1));

	Component* right_arm = new Component(shape, joint);
	right_arm->updatePos(glm::vec3(1, 1.2, 0),
									     glm::vec3(0, 0, 0),
									     glm::vec3(1, 0, 0),
										   glm::vec3(2, .5, .75));

	Component* right_arm_lower = new Component(shape, joint);
	right_arm_lower->updatePos(glm::vec3(2, 0, 0),
														 glm::vec3(0, 0, 0),
														 glm::vec3(.875, 0, 0),
														 glm::vec3(1.75, .4, .5));

	Component* right_leg = new Component(shape, joint);
	right_leg->updatePos(glm::vec3(.5, -1.5, 0),
											 glm::vec3(0, 0, 0),
											 glm::vec3(0, -1, 0),
											 glm::vec3(.75, 2, .75));

	Component* right_leg_lower = new Component(shape, joint);
	right_leg_lower->updatePos(glm::vec3(0, -2, 0),
														 glm::vec3(0, 0, 0),
														 glm::vec3(0, -.875, 0),
														 glm::vec3(.5, 1.75, .5));

	Component* left_leg = new Component(shape, joint);
	left_leg->updatePos(glm::vec3(-.5, -1.5, 0),
									    glm::vec3(0, 0, 0),
									    glm::vec3(0, -1, 0),
										  glm::vec3(.75, 2, .75));

	Component* left_leg_lower = new Component(shape, joint);
	left_leg_lower->updatePos(glm::vec3(0, -2, 0),
														glm::vec3(0, 0, 0),
														glm::vec3(0, -.875, 0),
														glm::vec3(.5, 1.75, .5));

	Component* left_arm = new Component(shape, joint);
	left_arm->updatePos(glm::vec3(-1, 1.2, 0),
									    glm::vec3(0, 0, 0),
									    glm::vec3(-1, 0, 0),
										  glm::vec3(2, .5, .75));

	Component* left_arm_lower = new Component(shape, joint);
	left_arm_lower->updatePos(glm::vec3(-2, 0, 0),
														glm::vec3(0, 0, 0),
														glm::vec3(-.875, 0, 0),
														glm::vec3(1.75, .4, .5));

	// attach pieces to their parent, and ultimately everything to torso "root_comp"
	right_arm->addChild(right_arm_lower);
	right_leg->addChild(right_leg_lower);
	left_leg->addChild(left_leg_lower);
	left_arm->addChild(left_arm_lower);
  root_comp->addChild(head);
	root_comp->addChild(right_arm);
	root_comp->addChild(right_leg);
	root_comp->addChild(left_leg);
	root_comp->addChild(left_arm);

	// initially set current to the torso
	curr_comp = root_comp;

	// Initialize the GLSL programs.
	prog = make_shared<Program>();
	prog->setVerbose(true);
	prog->setShaderNames(RES_DIR + "nor_vert.glsl", RES_DIR + "nor_frag.glsl");
	prog->init();
	prog->addUniform("P");
	prog->addUniform("MV");
	prog->addAttribute("aPos");
	prog->addAttribute("aNor");
	prog->setVerbose(false);

	progIM = make_shared<Program>();
	progIM->setVerbose(true);
	progIM->setShaderNames(RES_DIR + "simple_vert.glsl", RES_DIR + "simple_frag.glsl");
	progIM->init();
	progIM->addUniform("P");
	progIM->addUniform("MV");
	progIM->setVerbose(false);

	// If there were any OpenGL errors, this will print something.
	// You can intersperse this line in your code to find the exact location
	// of your OpenGL error.
	GLSL::checkError(GET_FILE_LINE);
}

static void render()
{
	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float aspect = width/(float)height;
	glViewport(0, 0, width, height);

	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Create matrix stacks.
	auto P = make_shared<MatrixStack>();
	auto MV = make_shared<MatrixStack>();
	// Apply projection.
	P->pushMatrix();
	P->multMatrix(glm::perspective((float)(45.0*M_PI/180.0), aspect, 0.01f, 100.0f));
	// Apply camera transform.
	MV->pushMatrix();
	MV->translate(glm::vec3(0, 0, -3));

	// Draw root component
	prog->bind();
	curr_comp->selected_pulse();
	root_comp->draw(prog, MV, P);
	prog->unbind();

	// Pop matrix stacks.
	MV->popMatrix();
	P->popMatrix();

	GLSL::checkError(GET_FILE_LINE);
}

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Please specify the resource directory." << endl;
		return 0;
	}
	RES_DIR = argv[1] + string("/");

	// Set error callback.
	glfwSetErrorCallback(error_callback);
	// Initialize the library.
	if(!glfwInit()) {
		return -1;
	}
	// https://en.wikipedia.org/wiki/OpenGL
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// Create a windowed mode window and its OpenGL context.
	window = glfwCreateWindow(640, 480, "Christopher McGregor", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current.
	glfwMakeContextCurrent(window);
	// Initialize GLEW.
	glewExperimental = true;
	if(glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		return -1;
	}
	glGetError(); // A bug in glewInit() causes an error that we can safely ignore.
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
	// Set vsync.
	glfwSwapInterval(1);
	// Set keyboard callback.
	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window, character_callback);
	// Initialize scene.
	init();
	// Loop until the user closes the window.
	while(!glfwWindowShouldClose(window)) {
		// Render scene.
		render();
		// Swap front and back buffers.
		glfwSwapBuffers(window);
		// Poll for and process events.
		glfwPollEvents();
	}
	// Quit program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
