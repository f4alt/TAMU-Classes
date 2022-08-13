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
shared_ptr<Program> prog_TEST;
std::vector<Material*> materials;
std::vector<Component*> components;

// texture components (add to class later?)
shared_ptr<Texture> texture0;
vector<float> posBuf;
vector<float> texBuf;
vector<unsigned int> indBuf;
map<string,GLuint> bufIDs;
int indCount;
glm::mat3 T1(25.0f);

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
	prog->setShaderNames(RESOURCE_DIR + "vert.glsl", RESOURCE_DIR + "frag.glsl");
	prog->setVerbose(true);
	prog->init();
	prog->addAttribute("aPos");
	prog->addAttribute("aTex");
	prog->addUniform("MV");
	prog->addUniform("P");
	prog->addUniform("T1");
	prog->addUniform("texture0");
	prog->addUniform("texture1");
	prog->setVerbose(false);

	shared_ptr<Program> prog1 = make_shared<Program>();
	prog1->setShaderNames(RESOURCE_DIR + "blinn-phong_vert.glsl", RESOURCE_DIR + "blinn-phong_frag.glsl");
	prog1->setVerbose(true);
	prog1->init();
	prog1->addAttribute("aPos");
	prog1->addAttribute("aNor");
	prog1->addAttribute("aTex");
	prog1->addUniform("P");
	prog1->addUniform("MV");
	prog1->addUniform("MVit");
	prog1->addUniform("lightInfo");
	prog1->addUniform("ka");
	prog1->addUniform("kd");
	prog1->addUniform("ks");
	prog1->addUniform("s");
	prog1->addUniform("T1");
	prog1->addUniform("texture0");
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

	// load textures
	texture0 = make_shared<Texture>();
	texture0->setFilename(RESOURCE_DIR + "diamond_ore.jpg");
	texture0->init();
	texture0->setUnit(0);
	texture0->setWrapModes(GL_REPEAT, GL_REPEAT);

	//
	// Initialize geometry
	//
	// We need to fill in the position buffer, normal buffer, the texcoord
	// buffer, and the index buffer.
	// 0
	posBuf.push_back(-5.0f);
	posBuf.push_back(0.15f);
	posBuf.push_back(-7.0f);
	texBuf.push_back(0.0f);
	texBuf.push_back(0.0f);
	// 1
	posBuf.push_back(-5.0f);
	posBuf.push_back(0.15f);
	posBuf.push_back(23.0f);
	texBuf.push_back(1.0f);
	texBuf.push_back(0.0f);
	// 2
	posBuf.push_back(25.0f);
	posBuf.push_back(0.15f);
	posBuf.push_back(-7.0f);
	texBuf.push_back(0.0f);
	texBuf.push_back(1.0f);
	// 3
	posBuf.push_back(25.0f);
	posBuf.push_back(0.15f);
	posBuf.push_back(23.0f);
	texBuf.push_back(1.0f);
	texBuf.push_back(1.0f);
	// Index
	indBuf.push_back(0);
	indBuf.push_back(1);
	indBuf.push_back(2);
	indBuf.push_back(3);
	indBuf.push_back(2);
	indBuf.push_back(1);
	indCount = (int)indBuf.size();

	// Generate 3 buffer IDs and put them in the bufIDs map.
	GLuint tmp[3];
	glGenBuffers(3, tmp);
	bufIDs["bPos"] = tmp[0];
	bufIDs["bTex"] = tmp[1];
	bufIDs["bInd"] = tmp[2];

	glBindBuffer(GL_ARRAY_BUFFER, bufIDs["bPos"]);
	glBufferData(GL_ARRAY_BUFFER, posBuf.size()*sizeof(float), &posBuf[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, bufIDs["bTex"]);
	glBufferData(GL_ARRAY_BUFFER, texBuf.size()*sizeof(float), &texBuf[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIDs["bInd"]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indBuf.size()*sizeof(unsigned int), &indBuf[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// create 2 lights, add to lights vector
	Light* light1 = new Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	Light* light2 = new Light(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(1.0f));

	vector<Light*> lights(2);
	lights[0] = light1;
	lights[1] = light2;

	// create 100 materials with random ka, add to materials vector
	Material* HUD_mat = new Material(lights,
																	glm::vec3(0.2f, 0.2f, 0.2f),
																	glm::vec3(0.4f, 0.4f, 0.4f),
																	glm::vec3(0.7f, 0.7f, 0.7f),
																	200.0f
																	);

	Material* sun_mat = new Material(lights,
																	glm::vec3(1.0f, 1.0f, 0.0f),
																	glm::vec3(0.4f, 0.4f, 0.4f),
																	glm::vec3(0.7f, 0.7f, 0.7f),
																	200.0f
																	);

	materials.push_back(HUD_mat);
	materials.push_back(sun_mat);


	srand(time(0));
	for (int i=0; i < 100; i++) {
		Material* temp = new Material(lights,
																	glm::vec3(0.2f, 0.2f, 0.2f),
																	glm::vec3(r0_1(), r0_1(), r0_1()),
																	glm::vec3(1.0f, 0.9f, 0.8f),
																	200.0f
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

	shared_ptr<Shape> sphere = make_shared<Shape>();
	sphere->loadMesh(RESOURCE_DIR + "sphere.obj");
	sphere->init();

	shared_ptr<Shape> frustum = make_shared<Shape>();
	frustum->loadMesh(RESOURCE_DIR + "frustum.obj");
	frustum->init();

	Component* ground = new Component(cube);
	ground->updatePos(glm::vec3(9.0f, -0.1f, 9.0f),
										glm::vec3(0.0f, 0.0f, 0.0f),
										glm::vec3(0.0f, 0.0f, 0.0f),
										glm::vec3(25.0f, 0.5f, 25.0f));

	Component* sun = new Component(sphere);
	sun->updatePos(glm::vec3(0.0f, 10.0f, 0.0f),
								 glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec3(0.5f, 0.5f, 0.5f));

	Component* POV = new Component(frustum);
	POV->updatePos(glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec3(1.0f, 1.0f, 1.0f));

	Component* HUD_bunny = new Component(bunny);
	HUD_bunny->updatePos(glm::vec3(0.75f, 0.6f, 0.0f),
											 glm::vec3(0.0f, 0.0f, 0.0f),
											 glm::vec3(0.0f, 0.0f, 0.0f),
											 glm::vec3(0.2f));

	Component* HUD_teapot = new Component(teapot);
	HUD_teapot->updatePos(glm::vec3(-0.7f, 0.7f, 0.0f),
												glm::vec3(0.0f, 0.0f, 0.0f),
												glm::vec3(0.0f, 0.0f, 0.0f),
												glm::vec3(0.2f));

	HUD_bunny->selected_spin();
	HUD_teapot->selected_spin();
	HUD_bunny->isHUD(true);
	HUD_teapot->isHUD(true);

	components.push_back(ground);
	components.push_back(sun);
	components.push_back(HUD_teapot);
	components.push_back(HUD_bunny);
	components.push_back(POV);

	std::vector<shared_ptr<Shape> > ground_shapes = { bunny, teapot };

	// create components with shapes
	for (int i=0; i < 10; i++) {
		for (int j=0; j < 10; j++) {
			int chosen_shape = rand() % 2;
			float scale_stagger = r0_1();
			if (scale_stagger < .2 || scale_stagger > .8) {
				scale_stagger = .5;
			}
			Component* temp = new Component(ground_shapes[chosen_shape]);
			float bunny_trans = -.186996 + (1 - scale_stagger) * .333099;
			temp->updatePos(glm::vec3(2*i + r0_1(), bunny_trans, 2*j + r0_1()),
									 	  glm::vec3(0.0f, r0_1(), 0.0f),
										  glm::vec3(0.0f, 0.0f, 0.0f),
										  glm::vec3(scale_stagger));

			if (chosen_shape == 1) {
				temp->updateTfP(glm::vec3(2*i + r0_1(), 0.15f, 2*j + r0_1()));
				temp->isBunny(true);
			}

			components.push_back(temp);
		}
	}

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
	if(keyToggles[(unsigned)'p']) {
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


	// ***** main viewport *****
	glViewport(0, 0, width, height);

	P->pushMatrix();
	MV->pushMatrix();

	// draw HUD components with material[0]
	progs[1]->bind();
	components[2]->draw(progs[1], materials[0], MV, P);
	components[3]->draw(progs[1], materials[0], MV, P);
	progs[1]->unbind();

	// Apply camera transforms
	camera->applyProjectionMatrix(P);
	camera->applyViewMatrix(MV);

	// draw ground with texture0
	progs[0]->bind();
	texture0->bind(progs[0]->getUniform("texture0"));
	glUniformMatrix4fv(progs[0]->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
	glUniformMatrix4fv(progs[0]->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
	auto MVit = glm::transpose(glm::inverse(MV->topMatrix()));
	glUniformMatrix4fv(progs[0]->getUniform("MVit"), 1, GL_FALSE, glm::value_ptr(MVit));
	glUniformMatrix3fv(progs[0]->getUniform("T1"), 1, GL_FALSE, glm::value_ptr(T1));
	glEnableVertexAttribArray(progs[0]->getAttribute("aPos"));
	glBindBuffer(GL_ARRAY_BUFFER, bufIDs["bPos"]);
	glVertexAttribPointer(progs[0]->getAttribute("aPos"), 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(progs[0]->getAttribute("aTex"));
	glBindBuffer(GL_ARRAY_BUFFER, bufIDs["bTex"]);
	glVertexAttribPointer(progs[0]->getAttribute("aTex"), 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIDs["bInd"]);
	glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_INT, (void *)0);
	texture0->unbind();
	progs[0]->unbind();

	// draw rest
	progs[1]->bind();
	// draw sun with material[1]
	components[1]->draw(progs[1], materials[1], MV, P);

	// draw remaining components (teapots and bunnys)
	for (int i=5; i < (int)components.size(); i++) {
		if (keyToggles[(unsigned)' ']) {
			if (i%3 == 1) {
				components[i]->selected_pulse(1.0, 0.15);
			} else if (i%3 == 2) {
				components[i]->selected_pulse(0.5, 0.25);
			} else {
				components[i]->selected_pulse(0.25, 0.5);
			}
		}
		components[i]->draw(progs[1], materials[i-3], MV, P);
	}
	progs[1]->unbind();

	MV->popMatrix();
	P->popMatrix();


	// ***** mini map top down view *****
	if (keyToggles[(unsigned)'t']) {
		double s = 0.5;
		glViewport(0, 0, s*width, s*height);
		glEnable(GL_SCISSOR_TEST);
		glScissor(0, 0, s*width, s*height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);

		P->pushMatrix();
		MV->pushMatrix();

		// Apply camera transforms
		camera->applyProjectionMatrix_TD(P);
		camera->applyViewMatrix_TD(MV);

		// draw ground with texture 0
		progs[0]->bind();
		texture0->bind(progs[0]->getUniform("texture0"));
		glUniformMatrix4fv(progs[0]->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
		glUniformMatrix4fv(progs[0]->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
		auto MVit = glm::transpose(glm::inverse(MV->topMatrix()));
		glUniformMatrix4fv(progs[0]->getUniform("MVit"), 1, GL_FALSE, glm::value_ptr(MVit));
		glUniformMatrix3fv(progs[0]->getUniform("T1"), 1, GL_FALSE, glm::value_ptr(T1));
		glEnableVertexAttribArray(progs[0]->getAttribute("aPos"));
		glBindBuffer(GL_ARRAY_BUFFER, bufIDs["bPos"]);
		glVertexAttribPointer(progs[0]->getAttribute("aPos"), 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
		glEnableVertexAttribArray(progs[0]->getAttribute("aTex"));
		glBindBuffer(GL_ARRAY_BUFFER, bufIDs["bTex"]);
		glVertexAttribPointer(progs[0]->getAttribute("aTex"), 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIDs["bInd"]);
		glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_INT, (void *)0);
		texture0->unbind();
		progs[0]->unbind();

		// draw rest
		progs[1]->bind();
		// draw sun with material[1]
		components[1]->draw(progs[1], materials[1], MV, P);

		// draw frustum
		MV->pushMatrix();
		camera->applyFrustumInvView(width/height, MV);
		components[4]->draw(progs[1], materials[1], MV, P);
		MV->popMatrix();

		// draw remaining shapes (teapots and bunnys)
		for (int i=5; i < (int)components.size(); i++) {
			if (keyToggles[(unsigned)' ']) {
				if (i%3 == 1) {
					components[i]->selected_pulse(1.0, 0.15);
				} else if (i%3 == 2) {
					components[i]->selected_pulse(0.5, 0.25);
				} else {
					components[i]->selected_pulse(0.25, 0.5);
				}
			}
			components[i]->draw(progs[1], materials[i-3], MV, P);
		}
		progs[1]->unbind();

		MV->popMatrix();
		P->popMatrix();
	}

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
		cout << "Usage: A4 RESOURCE_DIR" << endl;
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
