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

    void reset() {
      fill(a.begin(), a.end(), 0);
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
};

int main() {
  int numGems, numQueries, temp;
  scanf("%d %d\n", &numGems, &numQueries);
  FT tree(numGems);

  // intake 6 gems, order in gems
  int gems[7];
  for (int i=1; i <= 6; i++) {
    scanf("%d\n", &temp);
    gems[i] = temp;
  }

  int gemsOrder[numGems+1];
  vector<vector<int>> gemContains;
  gemContains.resize(7);
  string scanval;
  cin >> scanval;
  for (int i=0; i < numGems; i++) {
    gemsOrder[i+1] = scanval[i] - 48;
    gemContains[scanval[i] - 48].push_back(i+1);
    // cout << "val:" << scanval[i] << " conv:" << scanval[i] - 48 << " inc: " << gems[scanval[i] - 48] << endl;
    tree.incr(i+1, gems[scanval[i] - 48]);
  }

  int a, b, c;
  while (numQueries--) {
    scanf("%d %d %d\n", &a, &b, &c);
    // cout << a << " | " << b << " | " << c << endl;
    if (a == 1) {
      // cout << "here" << endl;
      int offset = gems[c] - gems[gemsOrder[b]];
      for (int i=0; i < gemContains[gemsOrder[b]].size(); i++) {
        if (gemContains[gemsOrder[b]][i] == b) {
          gemContains[gemsOrder[b]].erase(gemContains[gemsOrder[b]].begin() + i);
        }
      }
      gemContains[c].push_back(b);
      // cout << offset << endl;
      gemsOrder[b] = c;
      tree.incr(b, offset);
      // for (int i=0; i < gemContains[
    } else if (a == 2) {
      int offset = c - gems[b];
      gems[b] = c;
      for (int i=0; i < gemContains[b].size(); i++) {
        tree.incr(gemContains[b][i], offset);
      }
      // for (int i=1; i <= numGems; i++) {
      //   if (gemsOrder[i] == b) {
      //     tree.incr(i, offset);
      //   }
      // }
    } else {
      cout << tree.rsq(b, c) << "\n";
    }


    // for (int i=1; i <= numGems; i++) {
    //   cout << "i:" << i << " | " << tree.rsq(i, i) << endl;
    // }
    // for (int i=0; i < 6; i++) {
    //   cout << "gems[" << i+1 << "]:" << gems[i+1] << endl;
    // }
    // cout << endl;
  }


  return 0;
}
