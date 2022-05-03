#include <bits/stdc++.h>

using namespace std;

struct line {
  double x1, y1, x2, y2;
};

pair<double,double> intersect(line l1, line l2) {
  double a1 = l1.y2 - l1.y1;
  double b1 = l1.x1 - l1.x2;
  double c1 = a1*(l1.x1) + b1*(l1.y1);

  double a2 = l2.y2 - l2.y1;
  double b2 = l2.x1 - l2.x2;
  double c2 = a2*(l2.x1) + b2*(l2.y1);

  double determinant = a1*b2 - a2*b1;

  double x = (b2*c1 - b1*c2)/determinant;
  double y = (a1*c2 - a2*c1)/determinant;

  return {x,y};
}

bool in(double v, double b1, double b2) {
  if (b1 > b2) {
    swap(b1, b2);
  }

  return v >= b1 && v <= b2;
}

bool canintersect(line l1, line l2) {
  double a1 = l1.y2 - l1.y1;
  double b1 = l1.x1 - l1.x2;
  double c1 = a1*(l1.x1) + b1*(l1.y1);

  double a2 = l2.y2 - l2.y1;
  double b2 = l2.x1 - l2.x2;
  double c2 = a2*(l2.x1) + b2*(l2.y1);

  double determinant = a1*b2 - a2*b1;

  double x = (b2*c1 - b1*c2)/determinant;
  double y = (a1*c2 - a2*c1)/determinant;

  if(!in(x, l1.x1, l1.x2) ||
     !in(x, l2.x1, l2.x2) ||
     !in(y, l1.y1, l1.y2) ||
     !in(y, l2.y1, l2.y2)) {
    return false;
  }

  return abs(determinant) > .0001;
}

bool diff(pair<double,double> p1, pair<double,double> p2) {
  return (abs(p1.first-p2.first) > .0001) || (abs(p1.second-p2.second) > .0001);
}

bool triangle(line l1, line l2, line l3) {
  pair<double,double> i1, i2, i3;

  if (!canintersect(l1,l2)) {
    return false;
  }
  if (!canintersect(l2,l3)) {
    return false;
  }
  if (!canintersect(l1,l3)) {
    return false;
  }

  i1 = intersect(l1,l2);
  i2 = intersect(l2,l3);
  i3 = intersect(l1,l3);

  if (diff(i1,i2) && diff(i2,i3) && diff(i3,i1)) {
    return true;
  }
  return false;
}

int main() {
  int n;
  while(cin >> n && n != 0) {
    vector<line> v(n);
    
    for (auto& i : v) {
      cin >> i.x1 >> i.y1 >> i.x2 >> i.y2;
    }

    int total = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            for(int k = j+1; k < n; k++) {
                bool works = triangle(v[i], v[j], v[k]);
                if(works) {
                    total++;
                }
            }
        }
    }

    cout << total << endl;
  }

}
