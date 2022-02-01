#include <iostream>
#include <string>
#include <climits>
#include <cfloat>
#include <memory>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Image.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

double RANDOM_COLORS[7][3] = {
	{0.0000,    0.4470,    0.7410},
	{0.8500,    0.3250,    0.0980},
	{0.9290,    0.6940,    0.1250},
	{0.4940,    0.1840,    0.5560},
	{0.4660,    0.6740,    0.1880},
	{0.3010,    0.7450,    0.9330},
	{0.6350,    0.0780,    0.1840},
};

int main(int argc, char **argv)
{
	if(argc < 5) {
		cout << "Usage: A1 meshfile filename width height task" << endl;
		return 0;
	}
	// input mesh
	string meshName(argv[1]);
	// Output filename
	string filename(argv[2]);
	// Width of image
	int width = atoi(argv[3]);
	// Height of image
	int height = atoi(argv[4]);
	// task number
	int task = atoi(argv[5]);
	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);

	// Load geometry
	vector<float> posBuf; // list of vertex positions
	vector<float> norBuf; // list of vertex normals
	vector<float> texBuf; // list of vertex texture coords
	vector<triangle*> sorted_buf;
	// vector<float> z_buf;
	float zmax = -FLT_MAX;
	float world_dim[6] = {FLT_MAX, -FLT_MAX, FLT_MAX, -FLT_MAX, FLT_MAX, -FLT_MAX};
	int color_iterator =0;
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if(!rc) {
		cerr << errStr << endl;
	} else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for(size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for(size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
					// cout << attrib.vertices[3*idx.vertex_index+0] << ",";
					// cout << attrib.vertices[3*idx.vertex_index+1] << ",";
					// cout << attrib.vertices[3*idx.vertex_index+2] << endl;
					// update world extremes for scaling
					world_dim[0] = min(world_dim[0], (float)(attrib.vertices[3*idx.vertex_index+0]));
					world_dim[1] = max(world_dim[1], (float)(attrib.vertices[3*idx.vertex_index+0]));
					world_dim[2] = min(world_dim[2], (float)(attrib.vertices[3*idx.vertex_index+1]));
					world_dim[3] = max(world_dim[3], (float)(attrib.vertices[3*idx.vertex_index+1]));
					world_dim[4] = min(world_dim[4], (float)(attrib.vertices[3*idx.vertex_index+2]));
					world_dim[5] = max(world_dim[5], (float)(attrib.vertices[3*idx.vertex_index+2]));
					if(!attrib.normals.empty()) {
						norBuf.push_back(attrib.normals[3*idx.normal_index+0]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+1]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+2]);
					}
					if(!attrib.texcoords.empty()) {
						texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+0]);
						texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+1]);
					}
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}
	cout << "Number of vertices: " << posBuf.size()/3 << endl;

	// verify world mins and maxs
	// for (int i=0; i < 6; i++) {
	// 	cout << world_dim[i] << " ";
	// }
	// cout << endl;

	// sort posBuf into scaled triangles
	float scale = min(width / (world_dim[1] - world_dim[0]), height / (world_dim[3] - world_dim[2]));
	float tx = .5 * width - (scale * (world_dim[0] + world_dim[1]) / 2);
	float ty = .5 * height - (scale * (world_dim[2] + world_dim[3]) / 2);
	for (size_t i=0; i < posBuf.size(); i+=9) {
		triangle* temp = new triangle();
		// verify scale and translation
		// cout << "scale:" << scale << endl;
		// cout << "tx:" << tx << endl;
		// cout << "ty:" << ty << endl;

		temp->vertices.push_back({posBuf[i  ] * scale + tx,
															posBuf[i+1] * scale + ty,
															posBuf[i+2],
															RANDOM_COLORS[color_iterator%7][0]*255,
															RANDOM_COLORS[color_iterator%7][1]*255,
															RANDOM_COLORS[color_iterator%7][2]*255
															});
		color_iterator++;
		temp->vertices.push_back({posBuf[i+3] * scale + tx,
															posBuf[i+4] * scale + ty,
															posBuf[i+5],
															RANDOM_COLORS[color_iterator%7][0]*255,
															RANDOM_COLORS[color_iterator%7][1]*255,
															RANDOM_COLORS[color_iterator%7][2]*255
															});
		color_iterator++;
		temp->vertices.push_back({posBuf[i+6] * scale + tx,
															posBuf[i+7] * scale + ty,
															posBuf[i+8],
															RANDOM_COLORS[color_iterator%7][0]*255,
															RANDOM_COLORS[color_iterator%7][1]*255,
															RANDOM_COLORS[color_iterator%7][2]*255
															});
		color_iterator++;
		sorted_buf.push_back(temp);
		// z_buf.push_back(posBuf[i+2]);
	}
	world_dim[0] = world_dim[0] * scale + tx;
	world_dim[1] = world_dim[1] * scale + tx;
	world_dim[2] = world_dim[2] * scale + ty;
	world_dim[3] = world_dim[3] * scale + ty;
	// cout << world_dim[0] << "," << world_dim[1] << " | " << world_dim[2] << "," << world_dim[3] << endl;

	switch (task) {
		case 1:
		{
			color_iterator = 0;
			for (auto tri : sorted_buf) {
				image->setBoundingBox(tri);
				for (int x = tri->bb.xmin; x < tri->bb.xmax; x++) {
					for (int y =tri->bb.ymin; y < tri->bb.ymax; y++) {
						image->setPixel(x, y, RANDOM_COLORS[color_iterator%7][0]*255, RANDOM_COLORS[color_iterator%7][1]*255, RANDOM_COLORS[color_iterator%7][2]*255);
					}
				}
				color_iterator++;
			}
			break;
		}
		case 2:
		{
			color_iterator = 0;
			for (auto tri : sorted_buf) {
				image->setBoundingBox(tri);
				float ret[3] = {0, 0, 0};
				for (int x = tri->bb.xmin; x < tri->bb.xmax; x++) {
					for (int y =tri->bb.ymin; y < tri->bb.ymax; y++) {
						if (image->calculateBarycentric(tri, x, y, ret)) {
							image->setPixel(x, y, RANDOM_COLORS[color_iterator%7][0]*255, RANDOM_COLORS[color_iterator%7][1]*255, RANDOM_COLORS[color_iterator%7][2]*255);
						}
					}
				}
				color_iterator++;
			}
			break;
		}
		case 3:
		{
			for (auto tri : sorted_buf) {
				image->setBoundingBox(tri);
				float ret[3] = {0, 0, 0};
				for (int x = tri->bb.xmin; x < tri->bb.xmax; x++) {
					for (int y =tri->bb.ymin; y < tri->bb.ymax; y++) {
						if (image->calculateBarycentric(tri, x, y, ret)) {
							image->setPixel(x, y, ret[0], ret[1], ret[2]);
						}
					}
				}
			}
			break;
		}
		case 4:
		{
			// triangle* world_tri = new triangle();
			// world_tri->vertices.push_back({world_dim[0], world_dim[2], 0, 0, 0, 255});
			// world_tri->vertices.push_back({world_dim[1], world_dim[3], 0, 255, 0, 0});
			// world_tri->vertices.push_back({world_dim[0], world_dim[3], 0, 255, 0, 0});
			// // vertex v0 = {0, 0, 0, 0, 0, 0};
			// // vertex v1 = {world_dim[1] - world_dim[0], world_dim[3] - world_dim[1], 0, 0, 0, 0};
			// // vertex v2 = {0, world_dim[3] - world_dim[1], 0, 0, 0, 0};
			// // world_tri.push_back
			// image->setBoundingBox(world_tri);
			// cout << world_tri->bb.xmin << endl;
			// cout << world_tri->bb.xmax << endl;
			// cout << world_tri->bb.ymin << endl;
			// cout << world_tri->bb.ymax << endl;
			// float ret[3] = {255, 255, 255};
			// for (auto tri : sorted_buf) {
				// for (int x = world_dim[0]; x < world_dim[1]; x++) {
				// 	for (int y = world_dim[2]; y < world_dim[3]; y++) {
						// if (image->calculateBarycentric(world_tri, x, y, ret)) {
							// image->setPixel(x, y, ret[0], ret[1], ret[2]);
						// }
				// 	}
				// }
			// }
			break;
		}
		case 5:
		{
			for (auto tri : sorted_buf) {
				zmax = -FLT_MAX;
				image->setBoundingBox(tri);
				float ret[3] = {0, 0, 0};
				for (int x = tri->bb.xmin; x < tri->bb.xmax; x++) {
					for (int y =tri->bb.ymin; y < tri->bb.ymax; y++) {
						if (image->calculateBarycentric(tri, x, y, ret)) {
							if (tri->vertices[0].z > zmax) {
								image->setPixel(x, y, ret[0], ret[1], ret[2]);
								zmax = tri->vertices[0].z;
							}
						}
					}
				}
			}
	}
	}

	// Write image to file
	image->writeToFile(filename);

	// cleanup memory
	for (auto p : sorted_buf) {
		delete p;
	}

	return 0;
}
