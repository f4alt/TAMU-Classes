#include <bits/stdc++.h>

using namespace std;

int main() {
  long long N, t;
  long long sum=0;

  cin >> N >> t;

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
      cout << (inputs[0] + inputs[1] + inputs[2]) / (long long)3 << endl;
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
      while (1) {
        if (inputs[next_index] > N) {
          cout << "Out" << endl;
          break;
        } else if (inputs[next_index] == N-1) {
          cout << "Done" << endl;
          break;
        } else if (next_index == 0) {
          cout << "Cyclic" << endl;
          break;
        }
        next_index = inputs[next_index];
      }
      break;
  }


  return 0;
}
