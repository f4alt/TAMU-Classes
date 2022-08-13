#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;

    // Create a one dimensional array on the heap of pointers to Pixels
    //    that has width elements (i.e. the number of columns)
    Pixel** image = new Pixel*[width];

    bool fail = false;

    for (int i=0; i < width; ++i) { // loop through each column
      // assign that column to a one dimensional array on the heap of Pixels
      //  that has height elements (i.e. the number of rows)
      image[i] = new Pixel[height];

      if (image[i] == nullptr) { // failed to allocate
        fail = true;
      }
    }

    if (fail) { // if any allocation fails, clean up and avoid memory leak
      // deallocate any arrays created in for loop
      for (int i=0; i < width; ++i) {
        delete [] image[i]; // deleting nullptr is not a problem
      }
      delete [] image; // dlete array of pointers
      return nullptr;
    }

    // initialize cells
    //cout << "Initializing cells..." << endl;
    for (int row=0; row<height; ++row) {
      for (int col=0; col<width; ++col) {
        // cout << "(" << col << ", " << row << ")" << endl; //testline ******
        image[col][row] = { 0, 0, 0 };
      }
    }
    cout << "End createImage... " << endl;
    return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

// implement for part 1

int* createSeam(int length) {
  int* A = new int[length];
  for (int i = 0; i < length; i++) {
    A[i] = 0;
  }
  return A;
}

void deleteSeam(int* seam) {
  delete[] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  // int expected_RGB_amount = width * height * 3;
  int actual_RGB_amount = 0;
  int colorMax;
  string p3_check;
  const char* lowerp3 = "p3";
  const char* upperP3 = "P3";
  int file_width;
  int file_height;
  int value_check;

  ifstream fin;
  fin.open(filename);
  // file doesn't open error
  if (!fin) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }
  // p3 not found
  fin >> p3_check;
  if (p3_check != lowerp3) {
    if (p3_check != upperP3) {
      cout << "Error: type is " << p3_check << " instead of P3" << endl;
      return false;
    }
  }
  // bad width
  fin >> file_width >> file_height;
  if (!fin.good()) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if (file_width != width) {
    cout << "Error: input width (" << width << ") does not match value in file (" << file_width << ")" << endl;
    return false;
  }
  // bad height
  if (file_height != height) {
    cout << "Error: input height (" << height << ") does not match value in file (" << file_height << ")" << endl;
    return false;
  }
  // consume the brightness line
  fin >> colorMax;
  // non or bad integer in file

    fin >> value_check;
  for (int i = 0; i < file_height; i++) {
    for (int j = 0; j < file_width; j++) {
      if (!fin.good() && !fin.eof()) {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if (value_check > 255 || value_check < 0) {
        cout << "Error: invalid color value " << value_check << endl;
        return false;
      }
      actual_RGB_amount++;
      image[j][i].r = value_check;

      fin >> value_check;
      if (!fin.good() && !fin.eof()) {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if (value_check > 255 || value_check < 0) {
        cout << "Error: invalid color value " << value_check << endl;
        return false;
      }
      actual_RGB_amount++;
      image[j][i].g = value_check;

      if (fin.eof()) {
        cout << "Error: not enough color values" << endl;
        return false;
      }

      fin >> value_check;
      if (!fin.good() && !fin.eof()) {
        cout << "Error: read non-integer value" << endl;
        return false;
      } else if (!fin.good() && fin.eof()) {
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if (value_check > 255 || value_check < 0) {
        cout << "Error: invalid color value " << value_check << endl;
        return false;
      }

      image[j][i].b = value_check;
      actual_RGB_amount++;

      fin >> value_check;

      if (j == (file_width - 1) && i == (file_height - 1) && !fin.eof()) {
        cout << "Error: too many color values" << endl;
        return false;
      }
    }
  }

  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {
  ofstream fout(filename);
  if (!fout) {
    cout << "Error: failed to open output file - " << filename << endl;
    return false;
  }
  if(fout.is_open()) {
    fout << "P3\n";
    fout << width << " " << height << endl;
    fout << "255\n";

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        fout << image[j][i].r << " ";
        fout << image[j][i].g << " ";
        fout << image[j][i].b << " ";
        fout << endl;
      }
    }
  }
  return true;
}

int energy(Pixel** image, int x, int y, int width, int height) {
  int xr, xg, xb;
  int yr, yg, yb;
  int energy;
  // if left column
  if (x == 0) {
    // top corner
    if (y == 0) {
      xr = (image[1][0].r - image[width - 1][0].r);
      xg = (image[1][0].g - image[width - 1][0].g);
      xb = (image[1][0].b - image[width - 1][0].b);
      yr = (image[0][1].r - image[0][height - 1].r);
      yg = (image[0][1].g - image[0][height - 1].g);
      yb = (image[0][1].b - image[0][height - 1].b);
      energy = (xr * xr) + (xg * xg) + (xb * xb) + (yr * yr) + (yg * yg) + (yb * yb);
      return energy;
    }
    // bottom corner
    if (y == (height - 1)) {
      xr = (image[1][0].r - image[width - 1][0].r);
      xg = (image[1][0].g - image[width - 1][0].g);
      xb = (image[1][0].b - image[width - 1][0].b);
      yr = (image[0][y - 1].r - image[0][0].r);
      yg = (image[0][y - 1].g - image[0][0].g);
      yb = (image[0][y - 1].b - image[0][0].b);
      energy = (xr * xr) + (xg * xg) + (xb * xb) + (yr * yr) + (yg * yg) + (yb * yb);
      return energy;
    }
    // the rest
    xr = (image[1][y].r - image[width - 1][y].r);
    xg = (image[1][y].g - image[width - 1][y].g);
    xb = (image[1][y].b - image[width - 1][y].b);
    yr = (image[0][y-1].r - image[0][y+1].r);
    yg = (image[0][y-1].g - image[0][y+1].g);
    yb = (image[0][y-1].b - image[0][y+1].b);
    energy = (xr * xr) + (xg * xg) + (xb * xb) + (yr * yr) + (yg * yg) + (yb * yb);
    return energy;
  }
  // if top row
  if (y == 0) {
    // if right corner
    if (x == (width - 1)) {
      xr = (image[x - 1][0].r - image[0][0].r);
      xg = (image[x - 1][0].g - image[0][0].g);
      xb = (image[x - 1][0].b - image[0][0].b);
      yr = (image[x][y + 1].r - image[x][height - 1].r);
      yg = (image[x][y + 1].g - image[x][height - 1].g);
      yb = (image[x][y + 1].b - image[x][height - 1].b);
      energy = (xr * xr) + (xg * xg) + (xb * xb) + (yr * yr) + (yg * yg) + (yb * yb);
      return energy;
    }
    // the rest
    xr = (image[x + 1][0].r - image[x - 1][0].r);
    xg = (image[x + 1][0].g - image[x - 1][0].g);
    xb = (image[x + 1][0].b - image[x - 1][0].b);
    yr = (image[x][y + 1].r - image[x][height - 1].r);
    yg = (image[x][y + 1].g - image[x][height - 1].g);
    yb = (image[x][y + 1].b - image[x][height - 1].b);
    energy = (xr * xr) + (xg * xg) + (xb * xb) + (yr * yr) + (yg * yg) + (yb * yb);
    return energy;
  }
  // if right column
  if (x == (width - 1)) {
    // if bottom right corner
    if (y == (height - 1)) {
      xr = (image[x - 1][y].r - image[0][y].r);
      xg = (image[x - 1][y].g - image[0][y].g);
      xb = (image[x - 1][y].b - image[0][y].b);
      yr = (image[x][y - 1].r - image[x][0].r);
      yg = (image[x][y - 1].g - image[x][0].g);
      yb = (image[x][y - 1].b - image[x][0].b);
      energy = (xr * xr) + (xg * xg) + (xb * xb) + (yr * yr) + (yg * yg) + (yb * yb);
      return energy;
    }
    // the rest
    xr = (image[x - 1][y].r - image[0][y].r);
    xg = (image[x - 1][y].g - image[0][y].g);
    xb = (image[x - 1][y].b - image[0][y].b);
    yr = (image[x][y - 1].r - image[x][y + 1].r);
    yg = (image[x][y - 1].g - image[x][y + 1].g);
    yb = (image[x][y - 1].b - image[x][y + 1].b);
    energy = (xr * xr) + (xg * xg) + (xb * xb) + (yr * yr) + (yg * yg) + (yb * yb);
    return energy;
  }
  // bottom row
  if (y == (height - 1)) {
    xr = (image[x + 1][y].r - image[x - 1][y].r);
    xg = (image[x + 1][y].g - image[x - 1][y].g);
    xb = (image[x + 1][y].b - image[x - 1][y].b);
    yr = (image[x][y - 1].r - image[x][0].r);
    yg = (image[x][y - 1].g - image[x][0].g);
    yb = (image[x][y - 1].b - image[x][0].b);
    energy = (xr * xr) + (xg * xg) + (xb * xb) + (yr * yr) + (yg * yg) + (yb * yb);
    return energy;
  }
  // all non edge cases
  xr = (image[x - 1][y].r - image[x + 1][y].r);
  xg = (image[x - 1][y].g - image[x + 1][y].g);
  xb = (image[x - 1][y].b - image[x + 1][y].b);
  yr = (image[x][y - 1].r - image[x][y + 1].r);
  yg = (image[x][y - 1].g - image[x][y + 1].g);
  yb = (image[x][y - 1].b - image[x][y + 1].b);
  energy = (xr * xr) + (xg * xg) + (xb * xb) + (yr * yr) + (yg * yg) + (yb * yb);
  return energy;
}

// implement for part 2

// uncomment for part 2
/*

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  return 0;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  return 0;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  return nullptr;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  return nullptr;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
}
*/
