#include <bits/stdc++.h>

using namespace std;

bool ishappy(int n) {
  if (n == 1) {
    return true;
  }
  if (n == 89) {
    return false;
  }

  int val = 0;
  while (n > 0) {
    val += pow(n%10,2);
    n /= 10;
  }

  return ishappy(val);
}

bool isprime(int n) {
  if (n < 2) {
    return false;
  }
  if (n == 2) {
    return true;
  }
  for (int i = 2; i <= sqrt(n); i++) {
    if (n%i==0) {
      return false;
    }
  }
  return true;
}

int main() {
  vector<bool> happy(10001, false);

  for (int i = 1; i <= 10000; i++) {
    happy[i] = ishappy(i);
  }

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int t1, t2;
    cin >> t1 >> t2;

    cout << t1 << " " << t2 << " ";
    if (happy[t2] && isprime(t2)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }

  return 0;
}
