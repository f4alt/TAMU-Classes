#include <iostream>
#include <string>
#include <climits>
#include <cfloat>
#include <memory>
#include <glm/glm.hpp>
#include <thread>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Camera.h"
#include "Image.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Object.h"
#include "Sphere.h"
#include "TriangleMesh.h"
#include "Triangle.h"
#include "Ellipsoid.h"
#include "Plane.h"
#include "RT_helpers.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

// globals
shared_ptr<Camera> camera;
vector<Object*> objects;
vector<Light*> lights;
glm::mat4 E(1.0f);
vector<thread> threads;
shared_ptr<Image> image;

void multitThread(int row, int width, int height) {
	for (int col=0; col < height; col++) {
		Ray ray;
		ray = camera->genRay(row, col);
		ray.origin = inverse(E) * glm::vec4(ray.origin, 1.0);
		ray.direction = inverse(E) * glm::vec4(ray.direction, 0.0);
		ray.direction = normalize(ray.direction);

		glm::vec3 rgb(0.0, 0.0, 0.0);
		shootRay(ray, 1.0, objects, lights, 0, rgb);
		// set color
		auto clamp = [](double s){ return std::max(std::min(s,1.0),0.0);};
		image->setPixel(width-row-1, height-col-1, 255.0*clamp(rgb[0]), 255.0*clamp(rgb[1]), 255.0*clamp(rgb[2]));
	}
}

int main(int argc, char **argv)
{
	// argument intake
	if(argc < 4) {
		cout << "Usage: ./A6 <SCENE> <IMAGE SIZE> <IMAGE FILENAME>" << endl;
		return 0;
	}
	// scene choice
	int scene = atoi(argv[1]);
	if (scene < 0 || scene > 8) {
		cout << "ERROR: bad scene choice - must be between 1 and 8" << endl;
		return 0;
	}
	// Width of image
	int width = atoi(argv[2]);
	// Height of image
	int height = atoi(argv[2]);
	// Output filename
	string filename(argv[3]);
	if (filename.find(".png") == std::string::npos) {
		cout << "ERROR: filename must be .png" << endl;
		return 0;
	}

	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	image = make_shared<Image>(width, height);

	// setup camera
	camera = make_shared<Camera>();
	// camera->setInitDistance(glm::vec3(0.0f, 0.0f, 5.0f)); // Camera's initial Z translation
	// camera->setRotation(glm::vec2(90.0*M_PI/180.0, 0.0f));	// none
	// camera->setFOV((float)(60.0*M_PI/180.0));
	// camera->setAspect((float)width/(float)height);	// since image is square, aspect is 1.0
	camera->setDimensions(width, height);
	// camera->setImagePlaneDist(1.0f);	// image plane is 1 infront of camera

	// generate objects depending on scene
	switch (scene) {
		case 0:
		{
			// generate two lights
			Light* l1 = new Light(glm::vec3(-1.0f, 2.0f, 1.0f), 0.5);
			Light* l2 = new Light(glm::vec3(0.5f, -0.5f, 0.0f), 0.5);
			lights.push_back(l1);
			lights.push_back(l2);

			// generate materials
			Material* red_mat = new Material();
			red_mat->kd = glm::vec3(1.0, 0.0, 0.0);
			red_mat->ks = glm::vec3(1.0, 1.0, 0.5);
			red_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			red_mat->km = glm::vec3(0.25, 0.25, 0.25);
			red_mat->exponent = 100.0;

			Material* white_mat = new Material();
			white_mat->kd = glm::vec3(1.0, 1.0, 1.0);
			white_mat->ks = glm::vec3(0.0, 0.0, 0.0);
			white_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			white_mat->exponent = 0.0;

			Material* blue_mat = new Material();
			blue_mat->kd = glm::vec3(0.0, 0.0, 1.0);
			blue_mat->ks = glm::vec3(1.0, 1.0, 0.5);
			blue_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			blue_mat->km = glm::vec3(0.25, 0.25, 0.25);
			blue_mat->exponent = 100.0;

			Material* green_mirror = new Material();
			green_mirror->kd = glm::vec3(0.0, 0.5, 0.0);
			green_mirror->ks = glm::vec3(0.0, 0.0, 0.0);
			green_mirror->ka = glm::vec3(0.0, 0.0, 0.0);
			green_mirror->km = glm::vec3(0.75, 0.75, 0.75);
			green_mirror->exponent = 0.0;

			Material* cyan_mirror = new Material();
			cyan_mirror->kd = glm::vec3(0.0, 0.5, 0.5);
			cyan_mirror->ks = glm::vec3(0.0, 0.0, 0.0);
			cyan_mirror->ka = glm::vec3(0.0, 0.0, 0.0);
			cyan_mirror->km = glm::vec3(0.75, 0.75, 0.75);
			cyan_mirror->exponent = 0.0;

			// generate scene objects
			Plane* floor_plane = new Plane();
			floor_plane->point = glm::vec3(0.0, -1.0, 0.0);
			floor_plane->normal = glm::vec3(0.0, 1.0, 0.0);
			objects.push_back(floor_plane);
			objects[0]->material = white_mat;

			Plane* back_wall_plane = new Plane();
			back_wall_plane->point = glm::vec3(0.0, 0.0, -3.0);
			back_wall_plane->normal = glm::vec3(0.0, 0.0, 1.0);
			objects.push_back(back_wall_plane);
			objects[1]->material = white_mat;

			Sphere* red_sph = new Sphere();
			red_sph->center = glm::vec3(0.5, -0.7, 0.5);
			red_sph->radius = 0.3;
			objects.push_back(red_sph);
			objects[2]->material = red_mat;

			Sphere* blue_sph = new Sphere();
			blue_sph->center = glm::vec3(1.0, -0.7, 0.0);
			blue_sph->radius = 0.3;
			objects.push_back(blue_sph);
			objects[3]->material = blue_mat;

			Sphere* mirror1 = new Sphere();
			mirror1->center = glm::vec3(-0.5, 0.0, -0.5);
			mirror1->radius = 1.0;
			objects.push_back(mirror1);
			objects[4]->material = green_mirror;

			Sphere* mirror2 = new Sphere();
			mirror2->center = glm::vec3(1.5, 0.0, -1.5);
			mirror2->radius = 1.0;
			objects.push_back(mirror2);
			objects[5]->material = cyan_mirror;
			break;
		}
		case 8:
		{
			camera->setInitDistance(glm::vec3(0.0f, 0.0f, 3.0f)); // Camera's initial Z translation
			camera->setFOV((float)(60.0*M_PI/180.0));
			auto M = std::make_shared<MatrixStack>();
			M->translate(0.0, 0.0, 0.0);
			glm::vec3 axis = normalize(glm::vec3(0.0f, 1.0f, 0.0f));
			M->rotate(1.5708, axis);
			M->scale(1.0, 1.0, 1.0);
			E = M->topMatrix();
		}
		case 1:
		case 2:
		{
			// generate one light inbetween camera and sphere
			Light* l1 = new Light(glm::vec3(-2.0f, 1.0f, 1.0f), 1.0);
			lights.push_back(l1);

			// create red green blue mats
			Material* red_mat = new Material();
			red_mat->kd = glm::vec3(1.0, 0.0, 0.0);
			red_mat->ks = glm::vec3(1.0, 1.0, 0.5);
			red_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			red_mat->exponent = 100.0;

			Material* green_mat = new Material();
			green_mat->kd = glm::vec3(0.0, 1.0, 0.0);
			green_mat->ks = glm::vec3(1.0, 1.0, 0.5);
			green_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			green_mat->exponent = 100.0;

			Material* blue_mat = new Material();
			blue_mat->kd = glm::vec3(0.0, 0.0, 1.0);
			blue_mat->ks = glm::vec3(1.0, 1.0, 0.5);
			blue_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			blue_mat->exponent = 100.0;

			// create reg green blue spheres
			Sphere* red_sph = new Sphere();
			red_sph->center = glm::vec3(-0.5, -1.0, 1.0);
			red_sph->radius = 1.0;
			objects.push_back(red_sph);
			objects[0]->material = red_mat;

			Sphere* green_sph = new Sphere();
			green_sph->center = glm::vec3(0.5, -1.0, -1.0);
			green_sph->radius = 1.0;
			objects.push_back(green_sph);
			objects[1]->material = green_mat;

			Sphere* blue_sph = new Sphere();
			blue_sph->center = glm::vec3(0.0, 1.0, 0.0);
			blue_sph->radius = 1.0;
			objects.push_back(blue_sph);
			objects[2]->material = blue_mat;
			break;
		}
		case 3:
		{
			// generate two lights
			Light* l1 = new Light(glm::vec3(1.0f, 2.0f, 2.0f), 0.5);
			Light* l2 = new Light(glm::vec3(-1.0f, 2.0f, -1.0f), 0.5);
			lights.push_back(l1);
			lights.push_back(l2);

			// generate materials
			// create red green blue mats
			Material* red_mat = new Material();
			red_mat->kd = glm::vec3(1.0, 0.0, 0.0);
			red_mat->ks = glm::vec3(1.0, 1.0, 0.5);
			red_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			red_mat->exponent = 100.0;

			Material* green_mat = new Material();
			green_mat->kd = glm::vec3(0.0, 1.0, 0.0);
			green_mat->ks = glm::vec3(1.0, 1.0, 0.5);
			green_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			green_mat->exponent = 100.0;

			Material* white_mat = new Material();
			white_mat->kd = glm::vec3(1.0, 1.0, 1.0);
			white_mat->ks = glm::vec3(0.0, 0.0, 0.0);
			white_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			white_mat->exponent = 0.0;

			// generate scene objects
			Sphere* green_sph = new Sphere();
			green_sph->center = glm::vec3(-0.5, 0.0, -0.5);
			green_sph->radius = 1.0;
			objects.push_back(green_sph);
			objects[0]->material = green_mat;

			Plane* floor_plane = new Plane();
			floor_plane->point = glm::vec3(0.0, -1.0, 0.0);
			floor_plane->normal = glm::vec3(0.0, 1.0, 0.0);
			objects.push_back(floor_plane);
			objects[1]->material = white_mat;

			Ellipsoid* red_ell = new Ellipsoid();
			red_ell->center = glm::vec3(0.5, 0.0, 0.5);
			red_ell->scale = glm::vec3(0.5, 0.6, 0.2);
			objects.push_back(red_ell);
			objects[2]->material = red_mat;
			objects[2]->Ell = true;
			break;
		}
		case 4:
		case 5:
		{
			// generate two lights
			Light* l1 = new Light(glm::vec3(-1.0f, 2.0f, 1.0f), 0.5);
			Light* l2 = new Light(glm::vec3(0.5f, -0.5f, 0.0f), 0.5);
			lights.push_back(l1);
			lights.push_back(l2);

			// generate materials
			Material* red_mat = new Material();
			red_mat->kd = glm::vec3(1.0, 0.0, 0.0);
			red_mat->ks = glm::vec3(1.0, 1.0, 0.5);
			red_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			red_mat->exponent = 100.0;

			Material* white_mat = new Material();
			white_mat->kd = glm::vec3(1.0, 1.0, 1.0);
			white_mat->ks = glm::vec3(0.0, 0.0, 0.0);
			white_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			white_mat->exponent = 0.0;

			Material* blue_mat = new Material();
			blue_mat->kd = glm::vec3(0.0, 0.0, 1.0);
			blue_mat->ks = glm::vec3(1.0, 1.0, 0.5);
			blue_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			blue_mat->exponent = 100.0;

			Material* mirror = new Material();
			mirror->kd = glm::vec3(0.0, 0.0, 0.0);
			mirror->ks = glm::vec3(0.0, 0.0, 0.0);
			mirror->ka = glm::vec3(0.0, 0.0, 0.0);
			mirror->km = glm::vec3(1.0, 1.0, 1.0);
			mirror->exponent = 0.0;

			// generate scene objects
			Plane* floor_plane = new Plane();
			floor_plane->point = glm::vec3(0.0, -1.0, 0.0);
			floor_plane->normal = glm::vec3(0.0, 1.0, 0.0);
			objects.push_back(floor_plane);
			objects[0]->material = white_mat;

			Plane* back_wall_plane = new Plane();
			back_wall_plane->point = glm::vec3(0.0, 0.0, -3.0);
			back_wall_plane->normal = glm::vec3(0.0, 0.0, 1.0);
			objects.push_back(back_wall_plane);
			objects[1]->material = white_mat;

			Sphere* red_sph = new Sphere();
			red_sph->center = glm::vec3(0.5, -0.7, 0.5);
			red_sph->radius = 0.3;
			objects.push_back(red_sph);
			objects[2]->material = red_mat;

			Sphere* blue_sph = new Sphere();
			blue_sph->center = glm::vec3(1.0, -0.7, 0.0);
			blue_sph->radius = 0.3;
			objects.push_back(blue_sph);
			objects[3]->material = blue_mat;

			Sphere* mirror1 = new Sphere();
			mirror1->center = glm::vec3(-0.5, 0.0, -0.5);
			mirror1->radius = 1.0;
			objects.push_back(mirror1);
			objects[4]->material = mirror;

			Sphere* mirror2 = new Sphere();
			mirror2->center = glm::vec3(1.5, 0.0, -1.5);
			mirror2->radius = 1.0;
			objects.push_back(mirror2);
			objects[5]->material = mirror;
			break;
		}
		case 6:
		{
			// generate light(s)
			Light* l1 = new Light(glm::vec3(-1.0f, 1.0f, 1.0f), 1.0);
			lights.push_back(l1);

			// create blue mat
			Material* blue_mat = new Material();
			blue_mat->kd = glm::vec3(0.0, 0.0, 1.0);
			blue_mat->ks = glm::vec3(1.0, 1.0, 0.5);
			blue_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			blue_mat->exponent = 100.0;

			// Load geometry
			string meshName = "../resources/bunny.obj";
			vector<float> texBuf; // list of vertex texture coords
			vector<Object*> tri_buf; // list of triangles sorted using posBuf

			float world_dim[6] = {FLT_MAX, -FLT_MAX, FLT_MAX, -FLT_MAX, FLT_MAX, -FLT_MAX};
			tinyobj::attrib_t attrib;
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;
			string errStr;
			bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
			if(!rc) {
				cerr << errStr << endl;
			} else {
				// Loop over shapes
				for(size_t s = 0; s < shapes.size(); s++) {
					// Loop over faces (polygons)
					size_t index_offset = 0;
					for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
						Triangle* temp = new Triangle();	// new triangle
						size_t fv = shapes[s].mesh.num_face_vertices[f];
						// Loop over vertices in the face.
						for(size_t v = 0; v < fv; v++) {
							// access to vertex
							tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
							temp->vertices.push_back({attrib.vertices[3*idx.vertex_index+0],
																			 	attrib.vertices[3*idx.vertex_index+1],
																			 	attrib.vertices[3*idx.vertex_index+2]});

							// update world extremes for scaling
							world_dim[0] = min(world_dim[0], (float)(attrib.vertices[3*idx.vertex_index+0]));
							world_dim[1] = max(world_dim[1], (float)(attrib.vertices[3*idx.vertex_index+0]));
							world_dim[2] = min(world_dim[2], (float)(attrib.vertices[3*idx.vertex_index+1]));
							world_dim[3] = max(world_dim[3], (float)(attrib.vertices[3*idx.vertex_index+1]));
							world_dim[4] = min(world_dim[4], (float)(attrib.vertices[3*idx.vertex_index+2]));
							world_dim[5] = max(world_dim[5], (float)(attrib.vertices[3*idx.vertex_index+2]));
							if(!attrib.normals.empty()) {
								temp->norm.push_back({attrib.normals[3*idx.normal_index+0],
																			attrib.normals[3*idx.normal_index+1],
																			attrib.normals[3*idx.normal_index+2]});
							}
							if(!attrib.texcoords.empty()) {
								texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+0]);
								texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+1]);
							}
						}
						index_offset += fv;
						// per-face material (IGNORE)
						shapes[s].mesh.material_ids[f];
						tri_buf.push_back(temp);
						tri_buf.back()->material = blue_mat;
					}
				}
			}
			cout << "Number of triangles: " << tri_buf.size() << endl;

			// create bounding sphere for object
			Sphere* boundingSphere = new Sphere();
			float bb_x = (world_dim[1] + world_dim[0]) / 2;
			float bb_y = (world_dim[3] + world_dim[2]) / 2;
			float bb_z = (world_dim[5] + world_dim[4]) / 2;
			// float bb_r = std::max(abs(world_dim[0] + bb_x), abs(world_dim[2] + bb_y));
			boundingSphere->center = glm::vec3(bb_x, bb_y, bb_z);
			boundingSphere->radius = 1.0;
			// std::vector<Object*> bs;
			// bs.push_back(boundingSphere);
			// bs[0]->material = blue_mat;

			// finally, create object
			TriangleMesh* bunny = new TriangleMesh();
			bunny->triangles = tri_buf;
			bunny->bb = boundingSphere;
			objects.push_back(bunny);
			objects[0]->material = blue_mat;
			break;
		}
		case 7:
		{
			// calculate transformation matrix E
			auto M = std::make_shared<MatrixStack>();
			M->translate(0.3, -1.5, 0.0);
			glm::vec3 axis = normalize(glm::vec3(1.0f, 0.0f, 0.0f));
			M->rotate(0.34906, axis);
			M->scale(1.5, 1.5, 1.5);
			E = M->topMatrix();

			// generate light(s)
			glm::vec3 light_vec = glm::vec3(1.0, 1.0, 2.0);
			light_vec = inverse(E) * glm::vec4(light_vec, 1.0);
			Light* l1 = new Light(light_vec, 1.0);
			lights.push_back(l1);

			// create blue mat
			Material* blue_mat = new Material();
			blue_mat->kd = glm::vec3(0.0, 0.0, 1.0);
			blue_mat->ks = glm::vec3(1.0, 1.0, 0.5);
			blue_mat->ka = glm::vec3(0.1, 0.1, 0.1);
			blue_mat->exponent = 100.0;

			// Load geometry
			string meshName = "../resources/bunny.obj";
			vector<float> texBuf; // list of vertex texture coords
			vector<Object*> tri_buf; // list of triangles sorted using posBuf

			float world_dim[6] = {FLT_MAX, -FLT_MAX, FLT_MAX, -FLT_MAX, FLT_MAX, -FLT_MAX};
			tinyobj::attrib_t attrib;
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;
			string errStr;
			bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
			if(!rc) {
				cerr << errStr << endl;
			} else {
				// Loop over shapes
				for(size_t s = 0; s < shapes.size(); s++) {
					// Loop over faces (polygons)
					size_t index_offset = 0;
					for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
						Triangle* temp = new Triangle();	// new triangle
						size_t fv = shapes[s].mesh.num_face_vertices[f];
						// Loop over vertices in the face.
						for(size_t v = 0; v < fv; v++) {
							// access to vertex
							tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
							temp->vertices.push_back({attrib.vertices[3*idx.vertex_index+0],
																				attrib.vertices[3*idx.vertex_index+1],
																				attrib.vertices[3*idx.vertex_index+2]});

							// update world extremes for scaling
							world_dim[0] = min(world_dim[0], (float)(attrib.vertices[3*idx.vertex_index+0]));
							world_dim[1] = max(world_dim[1], (float)(attrib.vertices[3*idx.vertex_index+0]));
							world_dim[2] = min(world_dim[2], (float)(attrib.vertices[3*idx.vertex_index+1]));
							world_dim[3] = max(world_dim[3], (float)(attrib.vertices[3*idx.vertex_index+1]));
							world_dim[4] = min(world_dim[4], (float)(attrib.vertices[3*idx.vertex_index+2]));
							world_dim[5] = max(world_dim[5], (float)(attrib.vertices[3*idx.vertex_index+2]));
							if(!attrib.normals.empty()) {
								temp->norm.push_back({attrib.normals[3*idx.normal_index+0],
																			attrib.normals[3*idx.normal_index+1],
																			attrib.normals[3*idx.normal_index+2]});
							}
							if(!attrib.texcoords.empty()) {
								texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+0]);
								texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+1]);
							}
						}
						index_offset += fv;
						// per-face material (IGNORE)
						shapes[s].mesh.material_ids[f];
						tri_buf.push_back(temp);
						tri_buf.back()->material = blue_mat;
					}
				}
			}
			cout << "Number of triangles: " << tri_buf.size() << endl;

			// create bounding sphere for object
			Sphere* boundingSphere = new Sphere();
			float bb_x = (world_dim[1] + world_dim[0]) / 2;
			float bb_y = (world_dim[3] + world_dim[2]) / 2;
			float bb_z = (world_dim[5] + world_dim[4]) / 2;
			// float bb_r = std::max(abs(world_dim[0] + bb_x), abs(world_dim[2] + bb_y));
			boundingSphere->center = glm::vec3(bb_x, bb_y, bb_z);
			boundingSphere->radius = 1.0;
			// std::vector<Object*> bs;
			// bs.push_back(boundingSphere);
			// bs[0]->material = blue_mat;

			// finally, create object
			TriangleMesh* bunny = new TriangleMesh();
			bunny->triangles = tri_buf;
			bunny->bb = boundingSphere;
			objects.push_back(bunny);
			objects[0]->material = blue_mat;
			break;
		}
	}

	// for each pixel (row, col) in image
	for (int row=0; row < width; row++) {
		threads.push_back(thread(multitThread, row, width, height));
	}

	// join all threads
	for (size_t i = 0; i < threads.size(); i++) {
		threads[i].join();
	}

	// Write image to file
	image->writeToFile(filename);

	// cleanup memory

	return 0;
}
