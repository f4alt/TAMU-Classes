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
#include "Texture.h"

using namespace std;

// generates random float between 0 and 1
float r0_1() {
	float ret = (rand() % 10 + 1) / 10.0;
	return ret;
}

GLFWwindow *window; // Main application window
string RESOURCE_DIR = "./"; // Where the resources are loaded from
bool OFFLINE = false;

shared_ptr<Camera> camera;
std::vector<shared_ptr<Program>> progs;
std::vector<Material*> materials;
std::vector<Component*> components;
const int numLights = 50;
std::vector<Light*> lights;
glm::vec3 lights_vec[numLights * 2];

// deferred rendering globals
shared_ptr<Program> progPass2;
int textureWidth = 640;
int textureHeight = 480;
GLuint framebufferID;
GLuint posTexture, norTexture, keTexture, kdTexture;
shared_ptr<Shape> shape2;

void genTextures() {
	// generate and bind the framebuffer
	glGenFramebuffers(1, &framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

	// create textureA
	glGenTextures(1, &posTexture);
	glBindTexture(GL_TEXTURE_2D, posTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, textureWidth, textureHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, posTexture, 0);

	// create textureB
	glGenTextures(1, &norTexture);
	glBindTexture(GL_TEXTURE_2D, norTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, textureWidth, textureHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, norTexture, 0);

	// create textureC
	glGenTextures(1, &keTexture);
	glBindTexture(GL_TEXTURE_2D, keTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, textureWidth, textureHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, keTexture, 0);

	// create textureD
	glGenTextures(1, &kdTexture);
	glBindTexture(GL_TEXTURE_2D, kdTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, textureWidth, textureHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, kdTexture, 0);


	// bind depth buffer for depth tests
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, textureWidth, textureHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	// attach the four textures as output to frame buffer
	GLenum attachments[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
	glDrawBuffers(4, attachments);

	// error checking
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		cerr << "Framebuffer is not ok" << endl;
	}

	// reset framebuffer back to onscreen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

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
	switch (key) {
		case 'w':
		case 'a':
		case 's':
		case 'd':
		case 'z':
		case 'Z':
		case 'u':
		case 'y':
		{
			camera->keyboardmove(key);
			break;
		}
	}
}

// If the window is resized, capture the new size and reset the viewport
static void resize_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	textureWidth = width;
	textureHeight = height;
	genTextures();
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

	// basic prog for pass one
	shared_ptr<Program> prog1 = make_shared<Program>();
	prog1 = make_shared<Program>();
	prog1->setShaderNames(RESOURCE_DIR + "pass1_simp_vert.glsl", RESOURCE_DIR + "pass1_frag.glsl");
	prog1->setVerbose(true);
	prog1->init();
	// vert
	prog1->addUniform("P");
	prog1->addUniform("MV");
	prog1->addUniform("MVit");
	prog1->addAttribute("aPos");
	prog1->addAttribute("aNor");
	prog1->addAttribute("aTex");
	// frag
	prog1->addUniform("ke");
	prog1->addUniform("kd");

	// prog for vase using GPU move calculations
	shared_ptr<Program> prog2 = make_shared<Program>();
	prog2 = make_shared<Program>();
	prog2->setShaderNames(RESOURCE_DIR + "vase_vert.glsl", RESOURCE_DIR + "pass1_frag.glsl");
	prog2->setVerbose(true);
	prog2->init();
	// vert
	prog2->addUniform("P");
	prog2->addUniform("MV");
	prog2->addUniform("MVit");
	prog2->addAttribute("aPos");
	prog2->addAttribute("aNor");
	prog2->addAttribute("aTex");
	prog2->addUniform("t");
	// frag
	prog2->addUniform("ke");
	prog2->addUniform("kd");


	progPass2 = make_shared<Program>();
	progPass2->setShaderNames(RESOURCE_DIR + "pass2_vert.glsl", RESOURCE_DIR + "pass2_frag.glsl");
	progPass2->setVerbose(true);
	progPass2->init();
	// vert
	progPass2->addUniform("P");
	progPass2->addUniform("MV");
	progPass2->addAttribute("aPos");
	progPass2->addAttribute("aTex");
	progPass2->addAttribute("aNor");
	// frag
	progPass2->addUniform("posTexture");
	progPass2->addUniform("norTexture");
	progPass2->addUniform("keTexture");
	progPass2->addUniform("kdTexture");
	progPass2->addUniform("windowSize");
	progPass2->addUniform("lightInfo");
	progPass2->bind();
	glUniform1i(progPass2->getUniform("posTexture"), 0);
	glUniform1i(progPass2->getUniform("norTexture"), 1);
	glUniform1i(progPass2->getUniform("keTexture"), 2);
	glUniform1i(progPass2->getUniform("kdTexture"), 3);
	progPass2->unbind();

	progs.push_back(prog1);
	progs.push_back(prog2);

	// create x lights centered at 9 0 9, add to lights vector
	srand(time(0));
	float ang = 360.0 / (float)numLights;
	for (int i=0; i < numLights; i++) {
		glm::vec3 light_pos((r0_1() * 10)*cos(ang * i) + 9,
											   0.3f,
											   (r0_1() * 10)*sin(ang * i) + 9);

	  glm::vec3 light_col(r0_1(), r0_1(), r0_1());

		Light* light = new Light(light_pos, light_col);
		lights.push_back(light);
	}

	// create x light materials with ke matching light source and 0 elsewhere
	for (int i=0; i < numLights; i++) {
		Material* temp = new Material(lights,
																	lights[i]->getCol(),
																	glm::vec3(0.0f),
																	glm::vec3(0.0f),
																	0.0f
																 );

		materials.push_back(temp);
	}


	// create 100 materials with random kd, add to materials vector
	for (int i=0; i < 100; i++) {
		Material* temp = new Material(lights,
																	glm::vec3(0.0f, 0.0f, 0.0f),
																	glm::vec3(r0_1(), r0_1(), r0_1()),
																	glm::vec3(1.0f, 1.0f, 1.0f),
																	10.0f
																 );

		materials.push_back(temp);
	}

	camera = make_shared<Camera>();
	camera->setInitDistance(5.0f); // Camera's initial Z translation

	// load shapes
	shared_ptr<Shape> bunny = make_shared<Shape>();
	bunny->loadMesh(RESOURCE_DIR + "bunny.obj");
	bunny->init();

	shared_ptr<Shape> teapot = make_shared<Shape>();
	teapot->loadMesh(RESOURCE_DIR + "teapot.obj");
	teapot->init();

	shared_ptr<Shape> cube = make_shared<Shape>();
	cube->loadMesh(RESOURCE_DIR + "cube.obj");
	cube->init();

	shape2 = make_shared<Shape>();
	shape2->loadMesh(RESOURCE_DIR + "cube.obj");
	shape2->init();

	shared_ptr<Shape> sphere = make_shared<Shape>();
	sphere->gen_sphere();
	sphere->init();

	shared_ptr<Shape> vase = make_shared<Shape>();
	vase->gen_vase();
	vase->init();

	// create single components
	Component* ground = new Component(cube, progs[0]);
	ground->updatePos(glm::vec3(9.0f, -0.1f, 9.0f),
										glm::vec3(0.0f, 0.0f, 0.0f),
										glm::vec3(0.0f, 0.0f, 0.0f),
										glm::vec3(25.0f, 0.5f, 25.0f));

	components.push_back(ground);

	// add x lightBalls with same position as lights
	for (int i=0; i < numLights; i++) {
		Component* light_src = new Component(sphere, progs[0]);
		light_src->updatePos(lights[i]->getPos(),
												 glm::vec3(0.0f, 0.0f, 0.0f),
												 glm::vec3(0.0f, 0.0f, 0.0f),
												 glm::vec3(0.01f));
		components.push_back(light_src);
	}


	// create components with shapes
	std::vector<shared_ptr<Shape> > ground_shapes = { bunny, teapot, sphere, vase };
	for (int i=0; i < 10; i++) {
		for (int j=0; j < 10; j++) {
			float scale_stagger = r0_1();
			if (scale_stagger <= .1 || scale_stagger > .6) {
				scale_stagger = .4;
			}
			int chosen_shape = rand() % ground_shapes.size();
			Component* temp = new Component(ground_shapes[chosen_shape], chosen_shape == 3 ? progs[1] : progs[0]);
			float bunny_trans = -.186996 + (1 - scale_stagger) * .333099;

			switch (chosen_shape) {
				case 0:
				{
					temp->updatePos(glm::vec3(2*i + r0_1(), bunny_trans, 2*j + r0_1()),
											 	  glm::vec3(0.0f, r0_1(), 0.0f),
												  glm::vec3(0.0f, 0.0f, 0.0f),
												  glm::vec3(scale_stagger));
					temp->isBunny(true);
					break;
				}
				case 1:
				{
					temp->updatePos(glm::vec3(2*i + r0_1(), 0.15f, 2*j + r0_1()),
													glm::vec3(0.0f, r0_1(), 0.0f),
													glm::vec3(0.0f, 0.0f, 0.0f),
													glm::vec3(scale_stagger));
					temp->isTeapot(true);
					break;
				}
				case 2:
				{
					temp->updatePos(glm::vec3(2*i + r0_1(), scale_stagger + .145, 2*j + r0_1()),
													glm::vec3(0.0f, 0.0f, 0.0f),
													glm::vec3(0.0f, 0.0f, 0.0f),
													glm::vec3(scale_stagger));
					temp->isSphere(true);
					break;
				}
				case 3:
				{
					temp->updatePos(glm::vec3(2*i + r0_1(), 0.15f, 2*j + r0_1()),
													glm::vec3(0.0f, 0.0, M_PI/2),
													glm::vec3(0.0f, 0.0f, 0.0f),
													glm::vec3(.1));
					temp->isVase(true);
					break;
				}
			}

			components.push_back(temp);
		}
	}

	genTextures();

	GLSL::checkError(GET_FILE_LINE);
}

// This function is called every frame to draw the scene.
static void render()
{
	auto P = make_shared<MatrixStack>();
	auto MV = make_shared<MatrixStack>();

	//////////////////////////////////////////////////////
	// Render to the framebuffer
	//////////////////////////////////////////////////////

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, posTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, norTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, keTexture);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, kdTexture);
	glActiveTexture(GL_TEXTURE0);

	glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
	glViewport(0, 0, textureWidth, textureHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	P->pushMatrix();
	MV->pushMatrix();

	camera->setAspect(1.0f);
	camera->applyProjectionMatrix(P);
	camera->applyViewMatrix(MV);

	materials[0]->fillLights(lights_vec, MV->topMatrix());

	// draw ground
	components[0]->drawFP(materials[numLights], MV, P);

	// draw light balls
	for (int i=0; i < numLights; i++) {
		components[1+i]->drawFP(materials[i], MV, P);
	}

	// draw rest
	for (int i=numLights+1; i < (int)components.size(); i++) {
		components[i]->togAnim(keyToggles[(unsigned)' ']);
		components[i]->drawFP(materials[i-1], MV, P);
	}

	MV->popMatrix();
	P->popMatrix();


	//////////////////////////////////////////////////////
	// Render to the screen
	//////////////////////////////////////////////////////

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	P->pushMatrix();
	MV->pushMatrix();
	MV->scale(glm::vec3(2.0f));

	progPass2->bind();
	glUniformMatrix4fv(progPass2->getUniform("P"), 1, GL_FALSE, value_ptr(P->topMatrix()));
	glUniformMatrix4fv(progPass2->getUniform("MV"), 1, GL_FALSE, value_ptr(MV->topMatrix()));
	glUniform3fv(progPass2->getUniform("lightInfo"), numLights * 2, glm::value_ptr(lights_vec[0]));
	glUniform2f(progPass2->getUniform("windowSize"), (float)width, (float)height);
	shape2->draw(progPass2);
	glActiveTexture(GL_TEXTURE0);
	progPass2->unbind();

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
		cout << "Usage: A5 RESOURCE_DIR" << endl;
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
