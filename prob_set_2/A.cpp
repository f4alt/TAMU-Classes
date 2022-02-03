#include <bits/stdc++.h>

using namespace std;

// A

int main() {
  long long N, t, temp, qnty=1;
  long long sum=0;

  cin >> N >> t;

  vector<long long> inputs;
  inputs

  for (int i=0; i < N; i++) {
    cin >> temp;
    sum += temp;
    inputs.push_back(temp);
  }

  sort(inputs.begin(), inputs.end());

  // for (int i=0; i < inputs.size(); i++) {
  //   cout << inputs[i] << endl;
  // }

  switch (t) {
    case 1: {
      if (sum < 7777) {
        cout << "No" << endl;
        return 0;
      }
      if (!inputs.empty()) {
        for (int i=inputs.size()-1; i >= 0; i--) {
          // cout << inputs[i] << endl;
            for (int j=i -1; j > 0; j--) {
              // cout << inputs[i] << " + " << inputs[j] << endl;
              if (inputs[j] == inputs[i]) {
                continue;
              }
              if (inputs[j]+inputs[i] == 7777) {
                cout << "Yes" << endl;
                return 0;
              }
              if (inputs[j] + inputs[i] < 7777) {
                break;
              }
            }
          }
        }
        cout << "No" << endl;
        break;
      }
    case 2: {
      if (inputs.size() > 1) {
        for (int i=0; i < inputs.size()-1; i++) {
          if (inputs[i] == inputs[i+1]) {
            cout << "Contains duplicate" << endl;
            return 0;
          }
        }
      }
      cout << "Unique" << endl;
      break;
    }
    case 3: {
      for (int i=0; i < inputs.size()-1; i++) {
        if (inputs[i] == inputs[i+1]) {
          qnty++;
          // cout << "in[i]:" << inputs[i] << " | inc:" << qnty << endl;
        } else {
          qnty = 1;
        }
        if (qnty > N/2) {
          cout << inputs[i] << endl;
          return 0;
        }
      }
      cout << "-1" << endl;
    }
    case 4: {
      if (inputs.size() % 2 != 0) {
        cout << inputs[floor(inputs.size() / 2)] << endl;
      } else {
        cout << inputs[inputs.size() / 2 - 1] << " " << inputs[inputs.size()/2] << endl;
      }
    }
    case 5: {
      for (int i=0; i < inputs.size(); i++) {
        if (inputs[i] > 999) {
          return 0;
        }
        if (inputs[i] >= 100) {
          cout << inputs[i] << " ";
        }
      }
    }
  }

  return 0;
}
