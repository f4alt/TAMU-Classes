#include <bits/stdc++.h>

using namespace std;

struct coord {
    double x;
    double y;

    coord(double x, double y) : x(x), y(y) {}
    coord() {}
 };

double dist(coord a, coord b) {
    double x = a.x - b.x;
    double y = a.y - b.y;
    return sqrt(x*x + y*y);
}

int main() {
  int num_tests, inner_points, outer_points;
  double x, y;

  cin >> num_tests;
  while(num_tests--) {
    vector<coord> outer_poly;
    vector<coord> inner_poly;

    cin >> inner_points;

    for(int i = 0; i < inner_points; ++i) {
        cin >> x >> y;
        inner_poly.emplace_back(x,y);
    }

    cin >> outer_points;

    for(int i = 0; i < outer_points; ++i) {
        cin >> x >> y;
        outer_poly.emplace_back(x,y);
    }


    double minDistance = 1e9;
    for (int i = 0; i < outer_points; ++i) {
        coord outer1;
        outer1.x = outer_poly[i].x;
        outer1.y = outer_poly[i].y;
        coord outer2;
        if (i == outer_points-1) {
            outer2.x = outer_poly[0].x;
            outer2.y = outer_poly[0].y;
        } else {
            outer2.y = outer_poly[i+1].y;
            outer2.x = outer_poly[i+1].x;
        }

        for (int j = 0; j < inner_points; ++j) {
          coord p = inner_poly[j];
          coord a = outer1;
          coord b = outer2;
          double segment_size = dist(a,b);
          double u = ((p.x - a.x)*(b.x-a.x) + (p.y-a.y)*(b.y-a.y))/(segment_size*segment_size);

          double x = a.x + u*(b.x-a.x);
          double y = a.y + u*(b.y-a.y);
          coord projection;
          projection.x = x;
          projection.y = y;
          double line_projection_dist = dist(p, projection);
          if (line_projection_dist < 1e-8) {
              line_projection_dist = 1e9;
          }
          if (dist(projection,a) + dist(projection,b) - dist(a,b) > 1e-12) {
              line_projection_dist = 1e9;
          }

          double endpoint1_dist = dist(p, a);
          double endpoint2_dist = dist(p, b);

          double res = min(line_projection_dist,endpoint1_dist);
          res = min(res, endpoint2_dist);

          minDistance = min(minDistance, res);
        }
    }
    cout << setprecision(8) << minDistance*0.5 << endl;
  }



}
