#include <bits/stdc++.h>

using namespace std;

int main() {
  long long N, t;
  long long sum=0;
  vector<long long> median_check;

  cin >> N >> t;

  long long visited[N];

  long long inputs[N];
  long long temp;

  for (int i=0; i<N; i++) {
    cin >> temp;
    inputs[i] = temp;
  }

  long long next_index =inputs[0];
  switch (t) {
    case 1:
      cout << "7" << endl;
      break;
    case 2:
      if (inputs[0] > inputs[1]) {
        cout << "Bigger" << endl;
      } else if (inputs[0] == inputs[1]) {
        cout << "Equal" << endl;
      } else {
        cout << "Smaller" << endl;
      }
      break;
    case 3:
      median_check.push_back(inputs[0]);
      median_check.push_back(inputs[1]);
      median_check.push_back(inputs[2]);
      sort(median_check.begin(), median_check.end());
      cout << median_check[1] << endl;
      // cout << (inputs[0] + inputs[1] + inputs[2]) / (long long)3 << endl;
      // if (inputs[0] >= inputs[1] && inputs[0] <= inputs[2]) {
      //   cout << inputs[0] << endl;
      // } else if (inputs[1] >= inputs[0] && inputs[1] <= inputs[2]) {
      //   cout << inputs[1] << endl;
      // } else {
      //   cout << inputs[2] << endl;
      // }
      break;
    case 4:
      sum=0;
      for (int i=0; i < N; i++) {
        sum += inputs[i];
      }
      cout << sum << endl;
      break;
    case 5:
      sum=0;
      for (int i=0; i < N; i++) {
        if (inputs[i] % 2 == 0) {
          sum += inputs[i];
        }
      }
      cout << sum << endl;
      break;
    case 6:
      for (int i=0; i < N; i++) {
        cout << (char)('a' + inputs[i]%26);
      }
      cout << endl;
      break;
    case 7:
      // cout << "Cyclic" << endl;
      // while (1) {
        for (int i=0; i < N; i++) {
          if (inputs[next_index] >= N || inputs[next_index] < 0) {
            cout << "Out" << endl;
            return 0;
          } else if (inputs[next_index] == N-1) {
            cout << "Done" << endl;
            return 0;
          }
          next_index = inputs[next_index];
        }
        cout << "Cyclic" << endl;
        // else if (visited[next_index] == 1) {
        //   cout << "Cyclic" << endl;
        //   break;
        // }
        // visited[next_index] = 1;
        // next_index = inputs[next_index];
        // it = visited.find(next_index);
        // if (it != visited.end()) {
        //   cout << "Cyclic" << endl;
        // } else {
        //   visited.insert(pair<int, int>(next_index, 1));
        // }
        //  else if (visited.find(next_index)) {
        //   cout << "Cyclic" << endl;
        //   break;
        // }
        // visited.insert(pair<int, int>(next_index, 1));
        // next_index = inputs[next_index];
      // }
      break;
  }


  return 0;
}
