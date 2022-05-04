#include <math.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <cstring>
using namespace std;

// E

int parent[1000000];
int setSize[1000000];
vector<int> primes;

// initializes 0 to 'stop' in parent[] with itself
void initWithSelf(int start, int stop) {
    memset(parent, 0, stop);
    memset(setSize, 0, stop);
    for (int i = 0; i <= stop; i++) {
        parent[i] = i;
        setSize[i] = 1;
    }
}

int find(int x) {
    if (parent[x] == x) {
        return x;
    }
    return parent[x] = find(parent[x]);
}

void merge(int a, int b) {
    int tempA = find(a);
    int tempB = find(b);
    if (tempA != tempB) {
        parent[tempB] = tempA;
        setSize[tempA] += setSize[tempB];
    }
}

int getSetSize(int x, int n) {
    int output = 0;
    for (int i = 0; i <= n; i++) {
        if (find(i) == find(x)) output++;
    }
    return output;
}

// prints parent[] from 0 to stop position
void printParents(int start, int stop) {
    cout << "printing parent[] from 0 to " << stop << ":\n";
    for (int i = start; i <= stop; i++) {
        cout << parent[i] << " ";
    }
    cout << "\n\n";
}

bool isPrime(int n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= sqrt(n); i+=2) {
        if (n % i == 0) return false;
    }
    return true;
}

int findPrimeFactors(int n, int p) {
    int output = 0;
    int orig = n;

    while (n % 2 == 0) {
        output += 2;
        n = n / 2;
        if (p == 2) {
            merge(orig, 2);
        }
        // cout << "2 ";
    }

    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {
            output += i;
            n = n / i;
            if (n >= p) {
                merge(orig, n);
            }
            // cout << n << " ";
        }
    }

    if (n >= p) {
        merge(orig, p);
        output += n;
        // cout << n;
    }
    // cout << endl;

    return output;
};

int binary_search(int x) {
  int l = 0, r = primes.size() - 1;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (primes[m] == x) return m;
    if (primes[m] < x) l = m + 1;
    else r = m - 1;
  }
  return l;
}

int solve(int a, int b, int p) {
  int s = b-a+1;
  int top = s;
  for (int i = binary_search(p); i < primes.size(); i++) {
    int prime = primes[i];
    if (prime > top) break;

    int first_found = -1;
    for (int j = a; j <= b; j++) {
      if (j % prime == 0) {
        if (first_found < 0) {
            first_found = j;
        } else {
          int r_i = find(first_found);
          int r_j = find(j);
          if (r_i != r_j) {
            merge(r_i, r_j);
             s--;
          }
        }
      }
    }
  }
  return s;
}

int main() {
  int tc, a, b, p, prime_cnt = 0;

  // precompute primes
  vector<bool> prime(500, true);
  for (int i = 2; i < 500; i++) {
    if (prime[i]) {
      (prime_cnt)++;
      for (int j=i*i; j<500; j += i) prime[j] = false;
    }
  }
  primes.resize(prime_cnt);
  int next = 0;
  for (int i = 2; i < 500; i++) {
    if (prime[i]) primes[next++] = i;
  }

  cin >> tc;
  for (int i = 1; i <= tc; i++) {
    cin >> a >> b >> p;

    initWithSelf(0, 1001);

    cout << "Case #" << i << ": " << solve(a, b, p) << endl;
  }

    // int c, a, b, p;
    // cin >> c;
    // while (c--) {
    //     cin >> a >> b >> p;
    //     initWithSelf(0, b);
    //     // printParents(a, b);
    //
    //     for (int i = a; i <= b; i++) {
    //         // merge all prime factors
    //         findPrimeFactors(i, p);
    //     }
    //     printParents(a, b);
    //     for (int i=a; i <= b; i++) {
    //         cout << setSize[i] << " ";
    //     }
    //     cout << endl;
    // }
}
