#include <bits/stdc++.h>

using namespace std;

int main() {
  int loop;
  string sequence;
  int total=0;

  cin >> loop;
  for (int i=0; i< loop; i++) {
    cin >> sequence;

    std::size_t found = sequence.find("CD");
    if (found!=std::string::npos) {
      continue;
    } else {
      total++;
    }
  }

  cout << total << endl;


  return 0;
}
