#include <bits/stdc++.h>

using namespace std;

inline int LSOne(const int x) {
  return x & -x;
}

class FT {
  vector<long long> a;
  int n;

  public:
    FT(int x) {
      n = x;
      a.resize(x+1, 0);
    }

    // increment elem by val
    void incr(int elem, long long val) {
      while (elem <= n) {
        a[elem] += val;
        elem = elem + LSOne(elem);
      }
    }

    // range sum query - sums 1 to elem
    long long rsq(int elem) {
      long long sum=0;
      while (elem > 0) {
        sum += a[elem];
        elem -= LSOne(elem);
      }
      return sum;
    }

    // range sum query - sums i to j
    long long rsq(int i, int j) {
      return rsq(j) - rsq(i-1);
    }

    // flip elem
    void flip(int elem) {
      int add = 1;
      // cout << "flip:" << elem << " | " << rsq(elem) << " - " << rsq(elem-1) << " = " << rsq(elem, elem) << endl;
      if (rsq(elem, elem) == 1) {
        // cout << "here" << endl;
        add = -1;
      }
      while (elem <= n) {
        a[elem] += add;
        elem = elem + LSOne(elem);
      }
    }
};

int main() {
  int n, q;
  scanf("%d %d\n", &n, &q);
  FT tree(n);
  int a, b;
  char c;

  while (q--) {
    scanf("%c\n", &c);
    if (c == 'F') {
      scanf("%d\n", &a);
      tree.flip(a);
    } else {
      scanf("%d %d\n", &a, &b);
      cout << tree.rsq(a, b) << "\n";
    }
  }


  return 0;
}
