#include <bits/stdc++.h>

using namespace std;

// A

int main() {
  long long N, t, temp, qnty=1;
  long long sum=0;
  map<long long, int> freq;
  bool unique = true;
  map<long long, int>::iterator it;

  cin >> N >> t;

  long long max_num=-1;
  int max_idx=0;
  vector<long long> inputs;
  priority_queue<long long> inputs_pq;
  priority_queue<long long> inputs_pq_asc;
  int possiblities[7777] = {-1};
  // vector<long long> possiblities (4294967295, 0);
  // possiblities.resize(4294967296)
  // inputs

  for (int i=0; i < N; i++) {
    cin >> temp;
    sum += temp;
    inputs_pq.push(temp);
    inputs_pq_asc.push(-temp);
    inputs.push_back(temp);
    it = freq.find(temp);
    if (it != freq.end()) {
      unique = false;
      it->second++;
      if (it->second > max_idx) {
        max_idx = it->second;
        max_num = it->first;
      }
    } else {
      freq.insert(make_pair(temp, 1));
    }
    if (temp < 7778) {
      possiblities[temp]++;
    }
  }

  sort(inputs.begin(), inputs.end());

  // for (int i=0; i < inputs.size(); i++) {
  //   cout << inputs[i] << endl;
  // }

  switch (t) {
    case 1: {
        while (!inputs_pq.empty()) {
          // cout << inputs_pq.top() << " | " << possiblities[inputs_pq.top()] << endl;
          if (inputs_pq.top() < 7778) {
            if (possiblities[7777 - inputs_pq.top()] > 0) {
              cout << "Yes" << endl;
              return 0;
            }
          }
          inputs_pq.pop();
        }
        cout << "No" << endl;
        break;
      }
    case 2: {
      if (unique) {
        cout << "Unique" << endl;
      } else {
        cout << "Contains duplicate" << endl;
      }
      break;
    }
    case 3: {
      if (max_idx > (N/2)) {
        cout << max_num << endl;
      } else {
        cout << "-1" << endl;
      }
      break;
    }
    case 4: {
      if (N % 2 != 0) {
        for (int i=0; i < floor(N / 2); i++) {
          inputs_pq_asc.pop();
        }
        cout << -inputs_pq_asc.top() << endl;
      } else {
        for (int i=0; i < (N/2)-1; i++) {
          inputs_pq_asc.pop();
        }
        cout << -inputs_pq_asc.top() << " ";
        inputs_pq_asc.pop();
        cout << -inputs_pq_asc.top() << endl;
      }
    }
    case 5: {
      while (!inputs_pq_asc.empty()) {
        if (-inputs_pq_asc.top() > 999) {
          break;
        }
        if (-inputs_pq_asc.top() >= 100) {
          cout << -inputs_pq_asc.top() << " ";
        }
        inputs_pq_asc.pop();
      }
    }
  }

  return 0;
}
