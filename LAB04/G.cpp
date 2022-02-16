#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  int t=0, c=0, g=0;

  cin >> input;

  for (int i=0; i < input.size(); i++) {
    if (input[i] == 'T') {
      t++;
    }
    if (input[i] == 'C') {
      c++;
    }
    if (input[i] == 'G') {
      g++;
    }
  }

  cout << pow(t, 2) + pow(c, 2) + pow(g, 2) + min(min(t, c), g) * 7 << endl;


}
