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

struct triple {
	int x, y, z;
};

struct boundbox {
	int xmin=INT_MAX,
	xmax=-1,
	ymin=INT_MAX,
	ymax=-1;
};

struct triangle {
	vector<triple> vertices;
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
	tri1.vertices.push_back({100, 100, 0});
	tri1.vertices.push_back({100, 200, 0});
	tri1.vertices.push_back({200, 300, 0});

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

	// draw bb in maroon
	for (int x = tri1.bb.xmin; x <= tri1.bb.xmax; x++) {
		for (int y =tri1.bb.ymin; y <= tri1.bb.ymax; y++) {
			image->setPixel(x, y, 80, 0, 0);
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
