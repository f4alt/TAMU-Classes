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
  int numGems, numQueries;
  long long temp, sum;
  scanf("%d %d\n", &numGems, &numQueries);

  vector<int> gemOrder;
  gemOrder.resize(numGems+1, 0);
  vector<FT> trees;
  trees.resize(7, 0);

  // intake 6 gems, order in gems array
  // also create one tree per gem
  int gems[7];
  for (int i=1; i <= 6; i++) {
    scanf("%lld\n", &temp);
    gems[i] = temp;
    FT tree(numGems);
    trees[i] = tree;
  }

  // traverse gem value string
  // update gemOrder vector and tree value to indicate
  string scanval;
  cin >> scanval;
  for (int i=0; i < numGems; i++) {
    trees[scanval[i]-48].flip(i+1);
    gemOrder[i+1] = scanval[i]-48;
  }

  int a, b, c;
  while (numQueries--) {
    scanf("%d %d %d\n", &a, &b, &c);
    if (a == 1) {
      // flip to indicate gem of certain type
      trees[c].flip(b);
      // undo other flip
      trees[gemOrder[b]].flip(b);
      gemOrder[b] = c;
    } else if (a == 2) {
      gems[b] = c;
    } else {
      sum=0;
      for (int i=1; i <= 6; i++) {
        sum += gems[i] * trees[i].rsq(b, c);
      }
      cout << sum << "\n";
    }

    // debug printing
    // for (int i=1; i <= 6; i++) {
    //   cout << "trees[" << i << "] has " << trees[i].rsq(numGems) << " gems in it" << endl;
    // }
    // for (int i=0; i < 6; i++) {
    //   cout << "gems[" << i+1 << "]:" << gems[i+1] << endl;
    // }
    // for (int i=1; i <= numGems; i++) {
    //   cout << "gemOrder[" << i << "]:" << gemOrder[i] << endl;
    // }
    // cout << endl;
  }


  return 0;
}
