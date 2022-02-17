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
    long long rsq(long long elem) {
      long long sum=0;
      while (elem > 0) {
        sum += a[elem];
        elem -= LSOne(elem);
      }
      return sum;
    }

    // range sum query - sums i to j
    long long rsq(long long i, long long j) {
      return rsq(j) - rsq(i-1);
    }
};

int main() {
  long long n, p, rain, year1, secondVal;
  // size sqrt billion
  FT tree(45000);
  int a, b;
  char c;

  scanf("%lld\n", &n);
  while (n != 0 && p != 0) {
    while (n--) {
      scanf("%lld %lld\n", &year1, &secondVal);
      tree.incr(year1, secondVal);
    }

    scanf("%lld\n", &p);
    while (p--) {
      scanf("%lld %lld\n", &year1, &secondVal);
      cout << year1 << " rsq:" << tree.rsq(year1) << endl;
      if (secondVal < tree.rsq(year1)) {
        cout << "false\n";
      } else {
        cout << "true\n";
      }
    }
    scanf("%lld\n", &n);
  }


  return 0;
}
