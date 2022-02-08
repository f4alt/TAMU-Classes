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

void Image::setBoundingBox(triangle* tri1) {
	for (int i=0; i < 3; i++) {
		if (tri1->vertices[i].x < tri1->bb.xmin) {
			tri1->bb.xmin = tri1->vertices[i].x;
		}
		if (tri1->vertices[i].x > tri1->bb.xmax) {
			tri1->bb.xmax = tri1->vertices[i].x;
		}
		if (tri1->vertices[i].y < tri1->bb.ymin) {
			tri1->bb.ymin = tri1->vertices[i].y;
		}
		if (tri1->vertices[i].y > tri1->bb.ymax) {
			tri1->bb.ymax = tri1->vertices[i].y;
		}
	}
	// cout << tri1->bb.xmin << ",";
	// cout << tri1->bb.xmax << " | ";
	// cout << tri1->bb.ymin << ",";
	// cout << tri1->bb.ymax << " - ";
	// cout << floor(tri1->bb.xmin) << ",";
	// cout << ceil(tri1->bb.xmax) << " | ";
	// cout << floor(tri1->bb.ymin) << ",";
	// cout << ceil(tri1->bb.ymax) << endl;
}

bool Image::calculateBarycentric_RGB(triangle* tri, int x, int y, float* ret) {
	int z = 0;

	vertex v0 = {tri->vertices[1].x - tri->vertices[0].x, tri->vertices[1].y - tri->vertices[0].y, tri->vertices[1].z - tri->vertices[0].z, 0, 0, 0};
	// 2 - 0
	vertex v1 = {tri->vertices[2].x - tri->vertices[0].x, tri->vertices[2].y - tri->vertices[0].y, tri->vertices[2].z - tri->vertices[0].z, 0, 0, 0};
	// point - 0
	vertex v2 = {(float)x - tri->vertices[0].x, (float)y - tri->vertices[0].y, z - tri->vertices[0].z, 0, 0, 0};
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

	// cout << red << "," << green << "," << blue << endl;
	ret[0] = red;
	ret[1] = green;
	ret[2] = blue;
	if (u >= 0 && v >= 0 && w >= 0) {
		return true;
	} else {
		return false;
	}
}

bool Image::calculateBarycentric_Z(triangle* tri, int x, int y, float* ret, vector<float>* zBuf) {
	if (x < 0 || x >= width || y < 0 || y >= height) {
		return false;
	}
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

	ret[0] = u;
	ret[1] = v;
	ret[2] = w;

	// cout << tri->vertices[0].x << "," << tri->vertices[1].x << "," << tri->vertices[2].x << " | ";
	// cout << tri->vertices[0].y << "," << tri->vertices[1].y << "," << tri->vertices[2].y << " || ";
	// cout << x << "," << y << " ||| ";
	// cout << u << "," << v << "," << w << endl;
	// cout << z << endl;

	// Since the origin (0, 0) of the image is the upper left corner, we need
	// to flip the row to make the origin be the lower left corner.
	y = height - y - 1;
	// index corresponding to row and col, (assuming single component image)
	int index = y*width + x;
	// Multiply by 3 to get the index for the rgb components.
	assert(index >= 0);
	assert(index < (int)zBuf->size());
	if (u >= -0.000001 && v >= -0.000001 && w >= -0.000001 && z >= zBuf->at(index)) {
		zBuf->at(index) = z;
		ret[3] = z;
		return true;
	} else {
		return false;
	}
}
