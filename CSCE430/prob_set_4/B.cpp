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

    // flip elem between 1, 0
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
};

int main() {
  int testCases, numMovies, numQueries, front, temp;
  // movieID, position
  map<int, int>::iterator it;

  scanf("%d\n", &testCases);

  while (testCases--) {
    map<int, int> moviePos;
    scanf("%d %d\n", &numMovies, &numQueries);

    FT tree(numMovies + numQueries);

    for (int i=1; i <= numMovies; i++) {
      tree.flip(i);
      moviePos.insert( {i, numMovies - i +1} );
    }
    front = numMovies;

    while (numQueries--) {
      cin >> temp;
      it = moviePos.find(temp);
      cout << tree.rsq(front) - tree.rsq(it->second) << " ";
      // update for move
      tree.flip(it->second);
      // update pos in map
      front++;
      it->second = front;
      tree.flip(front);


      // sanity prints
      // for (auto i : moviePos) {
      //   cout << i.first << " | " << i.second << endl;
      // }
      // cout << "front: position " << front << endl;
    }
    cout << "\n";
  }



  return 0;
}
