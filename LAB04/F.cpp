#include <bits/stdc++.h>

using namespace std;

int main() {
  int num_tests, num_phone;
  string smallest="999999999", temp;

  cin >> num_tests;

  for (int z=0; z< num_tests; z++) {
    vector<string> numbers;
    bool bad = false;

    cin >> num_phone;

    for (int x=0; x < num_phone; x++) {
      cin >> temp;

      if (smallest.size() > temp.size()) {
        smallest = temp;
      }
      numbers.push_back(temp);
    }

    for (int i=0; i < numbers.size(); i++) {
      if (numbers[i].find(smallest) != string::npos) {
        cout << "NO" << endl;
        bad = true;
        break;
      }
    }
    if (!bad) {
      cout << "YES" << endl;
      bad = false;
    }
  }
}
