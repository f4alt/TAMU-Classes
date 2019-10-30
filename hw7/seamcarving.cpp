#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

int main() {
  string filename;
  int width = 0;
  int height = 0;
  int targetWidth = 0;
  int targetHeight = 0;

  // Add code to validate input (Do in part 1)
  cout << "Input filename: ";
  cin >> filename;
  cout << "Input width and height: ";
  cin >> width;
  // bad width input
  if(!cin.good()) {
  cout << "Error: width is a non-integer value" << endl;
  return -1;
  }
  cin >> height;
  // bad height input
  if (!cin.good()) {
    cout << "Error: height is a non-integer value" << endl;
    return -1;
  }
  cout << "Input target width and target height: ";
  cin >> targetWidth;
  // bad target width input
  if (!cin.good()) {
    cout << "Error: target width is a non-integer value" << endl;
    return -1;
  }
  // bad target height input
  cin >> targetHeight;
  if (!cin.good()) {
    cout << "Error: target height is a non-integer value" << endl;
    return -1;
  }

// error messages for sizes <= 0
  if (width <= 0) {
    cout << "Error: width must be greater than 0. You entered " << width << endl;
    return -1;
  }
  if (height <= 0) {
    cout << "Error: height must be greater than 0. You entered " << height << endl;
    return -1;
  }
  if (targetWidth <= 0) {
    cout << "Error: target width must be greater than 0. You entered " << targetWidth << endl;
    return -1;
  }
  if (targetHeight <= 0) {
    cout << "Error: target height must be greater than 0. You entered " << targetHeight << endl;
    return -1;
  }

// error messages for incompatible sizing
  if (targetWidth > width) {
    cout << "Error: target width must be less than width, " << targetWidth << " is greater than " << width << endl;
    return -1;
  }
  if (targetHeight > height) {
    cout << "Error: target height must be less than height, " << targetHeight << " is greater than " << height << endl;
    return -1;
  }




  int originalWidth = width; // need to delete image array at end of program
  // int width_difference = width - targetWidth;
  // int height_difference = height - targetHeight;
  // int total_difference = width_difference + height_difference;

  Pixel** image = createImage(width, height); // create array of size that we need
  if (image != nullptr) {
    if (loadImage(filename, image, width, height)) {
      cout << "Start carving..." << endl;

      // Add code to remove seams from image (Do in part 2)
      while (width > targetWidth || height > targetHeight) {
        if (width > targetWidth) {
          int* mvs = findMinVerticalSeam(image, width, height);
          removeVerticalSeam(image, width, height, mvs);
          width--;
          delete[] mvs;
        }
        if (height > targetHeight) {
          int* mhs = findMinHorizontalSeam(image, width, height);
          removeHorizontalSeam(image, width, height, mhs);
          height--;
          delete[] mhs;
        }
      }

      // set up output filename
      stringstream ss;
      ss << "carved" << width << "X" << height << "." << filename;
      outputImage(ss.str().c_str(), image, width, height);
    }

    // call last to remove the memory from the heap
    deleteImage(image, originalWidth);
  } else {
    cout << "Yeet" << endl;
  }

}
