#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <climits>
#include "Image.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

struct vertex {
	float x, y, z;
	float r, g, b;
};

struct boundbox {
	float xmin=INT_MAX,
	xmax=-1,
	ymin=INT_MAX,
	ymax=-1;
};

struct triangle {
	vector<vertex> vertices;
	boundbox bb;
};

int main(int argc, char **argv)
{
	if(argc < 4) {
		cout << "Usage: L01 filename width height" << endl;
		return 0;
	}
	// Output filename
	string filename(argv[1]);
	// Width of image
	int width = atoi(argv[2]);
	// Height of image
	int height = atoi(argv[3]);
	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);
	// take in vertices - lets just hard code them for now into a triangle
	triangle tri1;
	tri1.vertices.push_back({100, 100, 0, 255, 0, 0});
	tri1.vertices.push_back({400, 100, 0, 0, 255, 0});
	tri1.vertices.push_back({200, 300, 0, 0, 0, 255});

	// set tri bounding box
	for (int i=0; i < 3; i++) {
		if (tri1.vertices[i].x < tri1.bb.xmin) {
			tri1.bb.xmin = tri1.vertices[i].x;
		}
		if (tri1.vertices[i].x > tri1.bb.xmax) {
			tri1.bb.xmax = tri1.vertices[i].x;
		}
		if (tri1.vertices[i].y < tri1.bb.ymin) {
			tri1.bb.ymin = tri1.vertices[i].y;
		}
		if (tri1.vertices[i].y > tri1.bb.ymax) {
			tri1.bb.ymax = tri1.vertices[i].y;
		}
	};

	// check tri bounding box
	int z = 0;
	for (int x = tri1.bb.xmin; x <= tri1.bb.xmax; x++) {
		for (int y =tri1.bb.ymin; y <= tri1.bb.ymax; y++) {
			// image->setPixel(x, y, 80, 0, 0);
			// 1 - 0
			vertex v0 = {tri1.vertices[1].x - tri1.vertices[0].x, tri1.vertices[1].y - tri1.vertices[0].y, tri1.vertices[1].z - tri1.vertices[0].z, 0, 0, 0};
			// 2 - 0
			vertex v1 = {tri1.vertices[2].x - tri1.vertices[0].x, tri1.vertices[2].y - tri1.vertices[0].y, tri1.vertices[2].z - tri1.vertices[0].z, 0, 0, 0};
			// point - 0
			vertex v2 = {x - tri1.vertices[0].x, y - tri1.vertices[0].y, z - tri1.vertices[0].z, 0, 0, 0};
			// calculate dot products
			float d00 = v0.x * v0.x + v0.y * v0.y + v0.z * v0.z;
			float d01 = v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
			float d11 = v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
			float d20 = v2.x * v0.x + v2.y * v0.y + v2.z * v0.z;
			float d21 = v2.x * v1.x + v2.y * v1.y + v2.z * v1.z;
			float denom = d00 * d11 - d01 * d01;
			// calculate weights
			float v = (d11 * d20 - d01 * d21) / denom;
    	float w = (d00 * d21 - d01 * d20) / denom;
    	float u = 1.0f - v - w;
			// calculate rgb with weights
			float red = tri1.vertices[0].r * u + tri1.vertices[1].r * v + tri1.vertices[2].r * w / (u + v + w);
			float green = tri1.vertices[0].g * u + tri1.vertices[1].g * v + tri1.vertices[2].g * w / (u + v + w);
			float blue = tri1.vertices[0].b * u + tri1.vertices[1].b * v + tri1.vertices[2].b * w / (u + v + w);

			if (red < 0 || green < 0 || blue < 0) {
				continue;
			} else {
				image->setPixel(x, y, red, green, blue);
			}


			// cout << u << " | " << v << " | " << w << endl;
			// cout << red << " | " << green << " | " << blue << endl;
		}
	}

	// draw triangle pixels to make sure we cover the shape
	for (int i=0; i < 3; i++) {
		image->setPixel(tri1.vertices[i].x, tri1.vertices[i].y, 255, 255, 255);
	}

	// Write image to file
	image->writeToFile(filename);
	return 0;
}
