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

    // flip elem either 1 or 0
    void flip(int elem) {
      int add = 1;
      if (rsq(elem, elem) == 1) {
        add = -1;
      }
      while (elem <= n) {
        a[elem] += add;
        elem = elem + LSOne(elem);
      }
    }

    // prints values in tree
    void print() {
        for (int i = 1; i <= 19; i++) {
            cout << rsq(i,i) << " ";
        }
        cout << endl;
    }
};

int main() {
  FT tree(300000);

  int n, q;
  map<int, set<string> > prob;
  map<string, int> people;

  cin >> n;
  while (n--) {
    string name;
    int pos;
    cin >> name >> pos;
    people.insert(make_pair(name, pos));
    tree.incr(pos+1, 1);
  }

  // tree.print();

  cin >> q;

  while (q--) {
    string one, two;
    int onei, twoi;

    cin >> one >> two;

    onei = people[one];
    twoi = people[two];

    // cout << "onei: " << onei << " | twoi: " << twoi << endl;
    if (onei < twoi) {
      // cout << "below" << endl;
      int lower = tree.rsq(onei+1, twoi);
      int upper = tree.rsq(onei+2, twoi+1);

      cout << one << " is ";
      if (lower < upper) {
        cout << lower << "-" << upper;
      } else {
        cout << upper << "-" << lower;
      }
      cout << " rank(s) below " << two << "!" << endl;

    } else if (onei > twoi) {
      // cout << "above" << endl;
      int lower = tree.rsq(twoi+1, onei);
      int upper = tree.rsq(twoi+2, onei+1);

      int offset1 = tree.rsq(onei+1, onei+1);
      int offset2 = tree.rsq(twoi+1, twoi+1);

      cout << one << " is ";
      if (lower < upper) {
        cout << lower - offset2+1 << "-" << upper + offset2-1;
      } else {
        cout << upper - offset1+1 << "-" << lower + offset1-1;
      }
      cout << " rank(s) above " << two << "!" << endl;
    } else {
      cout << one << " is tied with " << two << "!" << endl;
    }
    // cout << tree.rsq(twoi+1, twoi+1) - 1 << endl;
  }


  return 0;
}
