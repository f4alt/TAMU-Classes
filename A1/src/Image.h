#pragma once
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>
#include <vector>
#include <climits>

struct vertex {
	float x, y, z;
	double r, g, b;
};

struct boundbox {
	float xmin=INT_MAX,
	xmax=-1,
	ymin=INT_MAX,
	ymax=-1,
	zmin=INT_MAX,
	zmax=-1;
};

struct triangle {
	std::vector<vertex> vertices;
	boundbox bb;
};


class Image
{
public:
	Image(int width, int height);
	virtual ~Image();
	void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
	void writeToFile(const std::string &filename);
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	void setBoundingBox(triangle* tri);
	bool calculateBarycentric(triangle* tri, int px, int py, float* ret);

private:
	int width;
	int height;
	int comp;
	std::vector<unsigned char> pixels;
};

#endif
