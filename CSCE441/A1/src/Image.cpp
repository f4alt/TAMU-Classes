#include <iostream>
#include <cassert>
#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

Image::Image(int w, int h) :
	width(w),
	height(h),
	comp(3),
	pixels(width*height*comp, 0)
{
}

Image::~Image()
{
}

void Image::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	// The pixel data is laid out row by row. Each row consists of 'width'
	// columns, and each column consists of 3 unsigned chars.

	// First check for bounds
	if(y < 0 || y >= height) {
		cout << "Row " << y << " is out of bounds" << endl;
		return;
	}
	if(x < 0 || x >= width) {
		cout << "Col " << x << " is out of bounds" << endl;
		return;
	}

	// Since the origin (0, 0) of the image is the upper left corner, we need
	// to flip the row to make the origin be the lower left corner.
	y = height - y - 1;
	// index corresponding to row and col, (assuming single component image)
	int index = y*width + x;
	// Multiply by 3 to get the index for the rgb components.
	assert(index >= 0);
	assert(3*index + 2 < (int)pixels.size());
	pixels[3*index + 0] = r;
	pixels[3*index + 1] = g;
	pixels[3*index + 2] = b;
}

void Image::writeToFile(const string &filename)
{
	// The distance in bytes from the first byte of a row of pixels to the
	// first byte of the next row of pixels
	int stride_in_bytes = width*comp*sizeof(unsigned char);
	int rc = stbi_write_png(filename.c_str(), width, height, comp, &pixels[0], stride_in_bytes);
	if(rc) {
		cout << "Wrote to " << filename << endl;
	} else {
		cout << "Couldn't write to " << filename << endl;
	}
}

void Image::setBoundingBox(triangle* tri) {
	for (int i=0; i < 3; i++) {
		if (tri->vertices[i].x < tri->bb.xmin) {
			tri->bb.xmin = tri->vertices[i].x;
		}
		if (tri->vertices[i].x > tri->bb.xmax) {
			tri->bb.xmax = tri->vertices[i].x;
		}
		if (tri->vertices[i].y < tri->bb.ymin) {
			tri->bb.ymin = tri->vertices[i].y;
		}
		if (tri->vertices[i].y > tri->bb.ymax) {
			tri->bb.ymax = tri->vertices[i].y;
		}
	}
}

// barycentric interpolation which solely returns weighted rgb calculations
bool Image::calculateBarycentric_RGB(triangle* tri, int x, int y, float* ret) {
	// break condition since we're using floor and ceil
	if (x < 0 || x >= width || y < 0 || y >= height) {
		return false;
	}

	// create vertex to do matrix dot product for faster barycentric calculations
	vertex v0 = {tri->vertices[1].x - tri->vertices[0].x, tri->vertices[1].y - tri->vertices[0].y, tri->vertices[1].z - tri->vertices[0].z, 0, 0, 0};
	// 2 - 0
	vertex v1 = {tri->vertices[2].x - tri->vertices[0].x, tri->vertices[2].y - tri->vertices[0].y, tri->vertices[2].z - tri->vertices[0].z, 0, 0, 0};
	// point - 0
	vertex v2 = {(float)x - tri->vertices[0].x, (float)y - tri->vertices[0].y, 0 - tri->vertices[0].z, 0, 0, 0};
	// calculate dot products
	float d00 = v0.x * v0.x + v0.y * v0.y;
	float d01 = v0.x * v1.x + v0.y * v1.y;
	float d11 = v1.x * v1.x + v1.y * v1.y;
	float d20 = v2.x * v0.x + v2.y * v0.y;
	float d21 = v2.x * v1.x + v2.y * v1.y;
	float denom = d00 * d11 - d01 * d01;
	// calculate weights
	float v = (d11 * d20 - d01 * d21) / denom;
	float w = (d00 * d21 - d01 * d20) / denom;
	float u = 1.0f - v - w;
	// calculate rgb with weights
	float red = tri->vertices[0].r * u + tri->vertices[1].r * v + tri->vertices[2].r * w / (u + v + w);
	float green = tri->vertices[0].g * u + tri->vertices[1].g * v + tri->vertices[2].g * w / (u + v + w);
	float blue = tri->vertices[0].b * u + tri->vertices[1].b * v + tri->vertices[2].b * w / (u + v + w);

	// set r g b returns
	ret[0] = red;
	ret[1] = green;
	ret[2] = blue;

	// check values to return with correct calculation.
	// Note: we use a error range since we're comparing floats using ints
	if (u >= -.000015 && v >= -.000015 && w >= -.000015) {
		return true;
	} else {
		return false;
	}
}

// barycentric interpolation using z buffer.
// returns true if point is valid
// updates u, v, w weights 0 as well as z height from camera in ret
bool Image::calculateBarycentric_Z(triangle* tri, int x, int y, float* ret, vector<float>* zBuf) {
	// break condition since we're using floor and ceil of floats
	if (x < 0 || x >= width || y < 0 || y >= height) {
		return false;
	}
	// precomputation vector conversion for quicker calculations
	// 1 - 0
	vertex v0 = {tri->vertices[1].x - tri->vertices[0].x, tri->vertices[1].y - tri->vertices[0].y, 0, 0, 0, 0};
	// 2 - 0
	vertex v1 = {tri->vertices[2].x - tri->vertices[0].x, tri->vertices[2].y - tri->vertices[0].y, 0, 0, 0, 0};
	// point - 0
	vertex v2 = {(float)x - tri->vertices[0].x, (float)y - tri->vertices[0].y, 0 - tri->vertices[0].z, 0, 0, 0};
	// calculate dot products
	float d00 = v0.x * v0.x + v0.y * v0.y;
	float d01 = v0.x * v1.x + v0.y * v1.y;
	float d11 = v1.x * v1.x + v1.y * v1.y;
	float d20 = v2.x * v0.x + v2.y * v0.y;
	float d21 = v2.x * v1.x + v2.y * v1.y;
	float denom = d00 * d11 - d01 * d01;
	// calculate weights
	float v = (d11 * d20 - d01 * d21) / denom;
	float w = (d00 * d21 - d01 * d20) / denom;
	float u = 1.0f - v - w;
	// calculate z coord
	float z = u * tri->vertices[0].z + v * tri->vertices[1].z + w * tri->vertices[2].z / (u + v + w);

	// return u,v,w
	ret[0] = u;
	ret[1] = v;
	ret[2] = w;

	// index on zbuffer using pixel x and y
	// Since the origin (0, 0) of the image is the upper left corner, we need
	// to flip the row to make the origin be the lower left corner.
	y = height - y - 1;
	// index corresponding to row and col, (assuming single component image)
	int index = y*width + x;
	// Multiply by 3 to get the index for the rgb components.
	assert(index >= 0);
	assert(index < (int)zBuf->size());

	// return true on good values
	if (u >= -0.000015 && v >= -0.000015 && w >= -0.000015 && z >= zBuf->at(index)) {
		zBuf->at(index) = z;
		ret[3] = z;
		return true;
	} else {
		return false;
	}
}
