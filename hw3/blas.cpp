/*
BLAS Level 1 function definitions
*/
#include <iostream>
#include <cmath>
#include "blas.h"

using std::cout;
using std::endl;

int amax(const double* x, const unsigned int len) {
  double max_val = *x;
  double check_val;
  unsigned int max_index = 0;
  if (len == 0) {
    return -1;
  } else {
  for (unsigned int i = 0; i < len; i++) {
    check_val = *(x + i);
    if (check_val < 0) {
      check_val *= -1;
    }
    if (check_val > max_val) {
      max_val = check_val;
      max_index = i;
    }
  }
}
  return max_index;
}

double asum(const double* x, const unsigned int len) {
  double total = 0;
  double add_val;
  if (len == 0) {
    return 0;
  }
  for (unsigned int i = 0; i < len; i++) {
    add_val = *(x + i);
    if (add_val < 0) {
      add_val *= -1;
    }
    total += add_val;
  }
    return total;
}

void axpy(const double a, const double* x, double* y, const unsigned int len) {
  double x_val;
  double x_times_const;
  for (unsigned int i = 0; i < len; i++) {
    x_val = *(x + i);
    x_times_const = x_val * a;
    *(y + i) += x_times_const;
    }
}

void copy(const double* src, double* dest, const unsigned int len) {
  for (unsigned int i = 0; i < len; i++) {
    *(dest + i) = *(src + i);
  }
}

double dot(const double* x, const double* y, const unsigned int len) {
  double x_val;
  double y_val;
  double total;
  if (len == 0) {
    return 0;
  }
  for (unsigned int i = 0; i < len; i++) {
    x_val = *(x + i);
    y_val = *(y + i);
    total = total +  x_val * y_val;
  }
    return total;
}

double norm2(const double* x, const unsigned int len) {
  double x_val_to_square;
  double total;
  if (len == 0) {
    return 0;
  }
  for (unsigned int i = 0; i < len; i++) {
    x_val_to_square = *(x + i);
    if (x_val_to_square < 0) {
      x_val_to_square *= -1;
    }
    total += x_val_to_square * x_val_to_square;
  }
  total = sqrt(total);
  return total;
}

void scale(const double a, double* x, const unsigned int len) {
  double x_val;
  for (unsigned int i = 0; i < len; i++) {
    x_val = *(x + i);
    x_val = x_val * a;
    *(x + i) = x_val;
  }
}

void swap(double* x, double* y, const unsigned int len) {
  double x_val;
  double y_val;
  for (unsigned int i = 0; i < len; i++) {
    x_val = *(x + i);
    y_val = *(y + i);
    *(x + i) = y_val;
    *(y + i) = x_val;
  }
}
