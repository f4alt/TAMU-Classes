#include <bits/stdc++.h>

using namespace std;

// D

int main() {
  int loop, len, d_count;
  bool reverse = false, error=false;
  string action, list_str;
  // int input*;

  std::ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> loop;

  for (int i=0; i < loop; i++) {
    cin >> action >> len >> list_str;

    // reset loop variables
    std::list<string> input;
    d_count=0;
    reverse = false;
    error = false;

    // get rid of first and last []
    list_str.erase(list_str.begin());
    list_str.erase(list_str.size()-1);

    // string stream input to comma deliminate
    stringstream s_stream(list_str);
    while (s_stream.good()) {
      string substr;
      getline(s_stream, substr, ',');
      if (substr != "") {
        input.push_back(substr);
      }
    }

    for (int i=0; i < action.size(); i++) {
      if (error) {
        break;
      }
      if (action[i] == 'R') {
        reverse = !reverse;
      } else if (action[i] == 'D') {
        d_count++;
        if (d_count > len) {
          cout << "error" << endl;
          error = true;
          break;
        }
        if (reverse) {
          input.pop_back();
        } else {
          input.pop_front();
        }
      }
    }

    string output = "[";

    if (reverse) {
      while (!input.empty()) {
        output.append(input.back());
        output.append(",");
        input.pop_back();
      }
    } else {
      while (!input.empty()) {
        output.append(input.front());
        output.append(",");
        input.pop_front();
      }
    }
    output.erase(output.size()-1);
    output.append("]\n");

    if (d_count == len) {
      cout << "[]\n";
    } else if (!error) {
      cout << output;
    }
  }



  return 0;
}
