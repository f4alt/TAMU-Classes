#include <iostream>

using namespace std;

int cust(const void *p, const void *q) {
  int *a = (int *) p;
  int *b = (int *) q;
  return *a - *b;
}

int main() {
  long long N, T;
  long long a, b, c;

  long long ti[100000000];

  cin >> N >> T >> a >> b >> c >> ti[0];

  for (int i = 1; i < N; i++) {
    ti[i] = (a * ti[i-1] + b) % c + 1;
  }

  qsort(ti, N, sizeof(long long), cust);

  long long penalty, solve, temp;
  penalty = 0;
  solve = 0;
  temp = 0;
  for (int i = 0; i < N; i++) {
    if (temp + ti[i] <= T) {
      penalty = (penalty + ti[i] + temp) % 1000000007;
      temp += ti[i];
      solve++;
    } else {
      break;
    }
  }

  cout << solve << " " << penalty << endl;










  return 0;
}
