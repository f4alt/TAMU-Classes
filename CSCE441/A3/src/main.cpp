#include <cassert>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Camera.h"
#include "GLSL.h"
#include "MatrixStack.h"
#include "Program.h"
#include "Shape.h"
#include "Component.h"
#include "Material.h"

using namespace std;

GLFWwindow *window; // Main application window
string RESOURCE_DIR = "./"; // Where the resources are loaded from
bool OFFLINE = false;

shared_ptr<Camera> camera;
std::vector<shared_ptr<Program>> progs;
int shader = 0;
std::vector<Material*> materials;
int material = 0;
int light_sel = 0;
Component* root_comp;
Component* teapot_comp;

bool keyToggles[256] = {false}; // only for English keyboards!

// This function is called when a GLFW error occurs
static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

// This function is called when a key is pressed
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

// This function is called when the mouse is clicked
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	// Get the current mouse position.
	double xmouse, ymouse;
	glfwGetCursorPos(window, &xmouse, &ymouse);
	// Get current window size.
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	if(action == GLFW_PRESS) {
		bool shift = (mods & GLFW_MOD_SHIFT) != 0;
		bool ctrl  = (mods & GLFW_MOD_CONTROL) != 0;
		bool alt   = (mods & GLFW_MOD_ALT) != 0;
		camera->mouseClicked((float)xmouse, (float)ymouse, shift, ctrl, alt);
	}
}

// This function is called when the mouse moves
static void cursor_position_callback(GLFWwindow* window, double xmouse, double ymouse)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if(state == GLFW_PRESS) {
		camera->mouseMoved((float)xmouse, (float)ymouse);
	}
}

static void char_callback(GLFWwindow *window, unsigned int key)
{
	keyToggles[key] = !keyToggles[key];
	bool forward = true;
	switch (key) {
		case ' ':
		{
			root_comp->selected_spin();
			teapot_comp->selected_shear();
			break;
		}
		case 'm':
		{
			if (material == 0) {
				material = 3;
			}
			material -= 1;
			break;
		}
		case 'M':
		{
			if (material == 2) {
				material = -1;
			}
			material += 1;
			break;
		}
		case 's':
		{
			if (shader == 0) {
				shader = 4;
			}
			shader -= 1;;
			break;
		}
		case 'S':
		{
			if (shader == 3) {
				shader = -1;
			}
			shader += 1;
			break;
		}
		case 'l':
		{
			if (light_sel == 0) {
				light_sel = 2;
			}
			light_sel -= 1;
			break;
		}
		case 'L':
		{
			if (light_sel == 1) {
				light_sel = -1;
			}
			light_sel += 1;
			break;
		}
		case 'x':
			forward = false;
		case 'X':
		{
			materials[material]->updateLightPos(light_sel, 'x', forward);
			break;
		}
		case 'y':
			forward = false;
		case 'Y':
		{
			materials[material]->updateLightPos(light_sel, 'y', forward);
			break;
		}
	}
}

// If the window is resized, capture the new size and reset the viewport
static void resize_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// https://lencerf.github.io/post/2019-09-21-save-the-opengl-rendering-to-image-file/
static void saveImage(const char *filepath, GLFWwindow *w)
{
	int width, height;
	glfwGetFramebufferSize(w, &width, &height);
	GLsizei nrChannels = 3;
	GLsizei stride = nrChannels * width;
	stride += (stride % 4) ? (4 - stride % 4) : 0;
	GLsizei bufferSize = stride * height;
	std::vector<char> buffer(bufferSize);
	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glReadBuffer(GL_BACK);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
	stbi_flip_vertically_on_write(true);
	int rc = stbi_write_png(filepath, width, height, nrChannels, buffer.data(), stride);
	if(rc) {
		cout << "Wrote to " << filepath << endl;
	} else {
		cout << "Couldn't write to " << filepath << endl;
	}
}

// This function is called once to initialize the scene and OpenGL
static void init()
{
	// Initialize time.
	glfwSetTime(0.0);

	// Set background color.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

	// load shaders and add to progs[]
	shared_ptr<Program> prog = make_shared<Program>();
	prog->setShaderNames(RESOURCE_DIR + "normal_vert.glsl", RESOURCE_DIR + "normal_frag.glsl");
	prog->setVerbose(true);
	prog->init();
	prog->addUniform("P");
	prog->addUniform("MV");
	prog->addUniform("MVit");
	prog->addAttribute("aPos");
	prog->addAttribute("aNor");
	prog->setVerbose(false);

	shared_ptr<Program> prog1 = make_shared<Program>();
	prog1->setShaderNames(RESOURCE_DIR + "blinn-phong_vert.glsl", RESOURCE_DIR + "blinn-phong_frag.glsl");
	prog1->setVerbose(true);
	prog1->init();
	prog1->addAttribute("aPos");
	prog1->addAttribute("aNor");
	prog1->addUniform("P");
	prog1->addUniform("MV");
	prog1->addUniform("MVit");
	prog1->addUniform("lightInfo");
	prog1->addUniform("ka");
	prog1->addUniform("kd");
	prog1->addUniform("ks");
	prog1->addUniform("s");
	prog1->setVerbose(false);

	shared_ptr<Program> prog2 = make_shared<Program>();
	prog2->setShaderNames(RESOURCE_DIR + "silhouette_vert.glsl", RESOURCE_DIR + "silhouette_frag.glsl");
	prog2->setVerbose(true);
	prog2->init();
	prog2->addUniform("P");
	prog2->addUniform("MV");
	prog2->addUniform("MVit");
	prog2->addAttribute("aPos");
	prog2->addAttribute("aNor");
	prog2->setVerbose(false);

	shared_ptr<Program> prog3 = make_shared<Program>();
	prog3->setShaderNames(RESOURCE_DIR + "cell_vert.glsl", RESOURCE_DIR + "cell_frag.glsl");
	prog3->setVerbose(true);
	prog3->init();
	prog3->addUniform("P");
	prog3->addUniform("MV");
	prog3->addUniform("MVit");
	prog3->addAttribute("aPos");
	prog3->addAttribute("aNor");
	prog3->addUniform("lightInfo");
	prog3->addUniform("ka");
	prog3->addUniform("kd");
	prog3->addUniform("ks");
	prog3->addUniform("s");
	prog3->setVerbose(false);

	progs.push_back(prog);
	progs.push_back(prog1);
	progs.push_back(prog2);
	progs.push_back(prog3);

	// create 2 lights, add to lights vector
	Light* light1 = new Light(glm::vec3(1.0f), glm::vec3(0.8f));
	Light* light2 = new Light(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.2f, 0.2f, 0.0f));

	vector<Light*> lights(2);
	lights[0] = light1;
	lights[1] = light2;

	// create 3 materials, add to materials vector
	Material* pink_shiny = new Material(lights,
																			glm::vec3(0.2f, 0.2f, 0.2f),
																			glm::vec3(0.8f, 0.7f, 0.7f),
																			glm::vec3(1.0f, 0.9f, 0.8f),
																			200.0f
																		 );

	Material* blue_greenshiny = new Material(lights,
																					 glm::vec3(0.0f, 0.0f, 0.0f),
																					 glm::vec3(0.0f, 0.0f, 1.0f),
																					 glm::vec3(0.0f, 1.0f, 0.0f),
																					 200.0f
																				  );

	Material* gray_dull = new Material(lights,
																		 glm::vec3(0.0f, 0.0f, 0.0f),
																		 glm::vec3(0.3f, 0.3f, 0.5f),
																		 glm::vec3(0.1f, 0.1f, 0.1f),
																		 0.0f
																	  );

	materials.push_back(pink_shiny);
	materials.push_back(blue_greenshiny);
	materials.push_back(gray_dull);

	camera = make_shared<Camera>();
	camera->setInitDistance(2.0f); // Camera's initial Z translation

	// load shapes
	shared_ptr<Shape> bunny = make_shared<Shape>();
	bunny->loadMesh(RESOURCE_DIR + "bunny.obj");
	bunny->init();

	shared_ptr<Shape> teapot = make_shared<Shape>();
	teapot->loadMesh(RESOURCE_DIR + "teapot.obj");
	teapot->init();

	// create components with shapes
	root_comp = new Component(bunny, bunny);
	root_comp->updatePos(glm::vec3(-.5, -.5, 0),
										 	 glm::vec3(0, 0, 0),
											 glm::vec3(0.0f, 0.0f, 0.0f),
											 glm::vec3(0.5f, 0.5f, 0.5f));

	teapot_comp = new Component(teapot, teapot);
	teapot_comp->updatePos(glm::vec3(.5, 0, 0),
										 	 	 glm::vec3(0, 3.14, 0),
											   glm::vec3(0.0f, 0.0f, 0.0f),
											 	 glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 S(1.0f);
	S[0][1] = -0.5f;
  teapot_comp->setShear(S);

	GLSL::checkError(GET_FILE_LINE);
}

// This function is called every frame to draw the scene.
static void render()
{
	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(keyToggles[(unsigned)'c']) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
	if(keyToggles[(unsigned)'z']) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	camera->setAspect((float)width/(float)height);

	// Matrix stacks
	auto P = make_shared<MatrixStack>();
	auto MV = make_shared<MatrixStack>();

	// Apply camera transforms
	P->pushMatrix();
	camera->applyProjectionMatrix(P);
	MV->pushMatrix();
	camera->applyViewMatrix(MV);

	// draw shapes
	progs[shader]->bind();
	root_comp->draw(progs[shader], materials[material], MV, P);
	teapot_comp->draw(progs[shader], materials[material], MV, P);
	progs[shader]->unbind();

	MV->popMatrix();
	P->popMatrix();

	GLSL::checkError(GET_FILE_LINE);

	if(OFFLINE) {
		saveImage("output.png", window);
		GLSL::checkError(GET_FILE_LINE);
		glfwSetWindowShouldClose(window, true);
	}
}

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Usage: A3 RESOURCE_DIR" << endl;
		return 0;
	}
	RESOURCE_DIR = argv[1] + string("/");

	// Optional argument
	if(argc >= 3) {
		OFFLINE = atoi(argv[2]) != 0;
	}

	// Set error callback.
	glfwSetErrorCallback(error_callback);
	// Initialize the library.
	if(!glfwInit()) {
		return -1;
	}
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
	GLSL::checkVersion();
	// Set vsync.
	glfwSwapInterval(1);
	// Set keyboard callback.
	glfwSetKeyCallback(window, key_callback);
	// Set char callback.
	glfwSetCharCallback(window, char_callback);
	// Set cursor position callback.
	glfwSetCursorPosCallback(window, cursor_position_callback);
	// Set mouse button callback.
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// Set the window resize call back.
	glfwSetFramebufferSizeCallback(window, resize_callback);
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
