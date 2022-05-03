#include <bits/stdc++.h>

using namespace std;

/*
 *function extended_gcd(a, b)
    s := 0;    old_s := 1
    r := b;    old_r := a

    while r ≠ 0 do
        quotient := old_r div r
        (old_r, r) := (r, old_r − quotient × r)
        (old_s, s) := (s, old_s − quotient × s)

    if b ≠ 0 then
        bezout_t := (old_r − old_s × a) div b
    else
        bezout_t := 0

    output "Bézout coefficients:", (old_s, bezout_t)
    output "greatest common divisor:", old_r
 */

void extended_gcd(long long a,
                  long long b,
                  long long& x,
                  long long& y,
                  long long& g) {
  x = 0, y = 1, g = b;
  long long m, n, q, r;
  for (long long u = 1, v = 0; a != 0; g = a, a = r) {
    q = g / a, r = g % a;
    m = x - u * q, n = y - v * q;
    x = u, y = v, u = m, v = n;
  }
}

// long long modInverse(long long a, long long m) {
//   for (long long x = 1; x < m; x++) {
//     if (((a%m) * (x%m)) % m == 1) {
//       return x;
//     }
//   }
//   return -1;
// }

long long modInverse(long long a, long long m) {
  long long x, y, gcd;
  extended_gcd(a, m, x, y, gcd);
  if (gcd != 1) {
    return 0;
  }
  return (x + m) % m;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    long long k, c;

    cin >> k >> c;

    if (k == 1) {
      if (c > 1) {
        cout << "1" << endl;
      } else {
        cout << "2" << endl;
      }
    } else if (c == 1) {
      cout << k + 1 << endl;
    } else {
      long long g = __gcd(k, c);
      if (g != 1) {
        cout << "IMPOSSIBLE" << endl;
      } else {
        cout << modInverse(c, k) << endl;
      }
    }
  }
  return 0;
}
