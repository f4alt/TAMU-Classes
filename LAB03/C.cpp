#include <bits/stdc++.h>

using namespace std;

int main() {
  int a, b, a_orig, b_orig, break_cond, astep, bstep;
  std::set<int>::iterator it;

  while (true) {
    set<int> seta, setb;

    cin >> a >> b;

    if (a == 0 && b == 0) {
      break;
    }

    a_orig = a;
    b_orig = b;
    astep = 0;
    bstep = 0;

    while (true) {
      seta.insert(a);
      setb.insert(b);

      astep++;
      bstep++;

      it = seta.find(b);
      if (it != seta.end()) {
        break_cond = b;
        bstep--;
        break;
      }
      it = setb.find(a);
      if (it != setb.end()) {
        break_cond = a;
        astep--;
        break;
      }

      if (a%2 == 0) {
        a = a/2;
      } else {
        a = 3*a + 1;
      }

      if (b%2 == 0) {
        b = b / 2;
      } else {
        b = 3*b+1;
      }
    }

    // cout << astep << " | " << bstep << endl;

    if (astep < bstep) {
      a = a_orig;
      astep = 0;
      while (a != break_cond) {
        if (a%2 == 0) {
          a = a/2;
        } else {
          a = 3*a + 1;
        }
        astep++;
      }
    } else {
      b = b_orig;
      bstep = 0;
      while (b != break_cond) {
        if (b%2 == 0) {
          b = b/2;
        } else {
          b = 3*b + 1;
        }
        bstep++;
      }
    }

    cout << a_orig << " needs " << astep << " steps, " << b_orig << " needs " << bstep << " steps, they meet at " << break_cond << endl;
  }




  return 0;
}
