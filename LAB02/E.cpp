#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  string output;
  int depth = 0;
  bool special_char = false;
  bool need_space = false;

  cin >> input;


  for (int i=0; i < input.size(); i++) {
    for (int j=0; j < depth; j++) {
      cout << "*";
    }

    if (input[i] == '{') {
      depth += 2;
      // cout << "depth:" << depth;
      cout << "{";
      special_char = true;
    }
    if (input [i] == '}') {
      depth -= 2;
      cout << "}";
      special_char = true;
    }

    cout << "\n";
  }

  // cout << "{" << endl;
//   for(int i=0; i < input.size(); i++) {
//     // cout << "i:" << i;
//     if (input[i] == '{') {
//       // cout << "\n";
//       cout << "{";
//       cout << "\n";
//       depth += 2;
//       special_char = true;
//       if (input[i+1] == '}') {
//         // cout << "\n";
//         depth-=2;
//         for (int j=0; j < depth; j++) {
//           cout << " ";
//         }
//         cout << "}";
//         i++;
//         // continue;
//       }
//     } else if (input[i] == '}') {
//       // if (i != input.size()-1) {
//       //   cout << "\n";
//       // }
//       cout << "\n";
//       depth -= 2;
//       for (int j=0; j < depth; j++) {
//         cout << " ";
//       }
//       cout << "}";
//       if (i+1 < input.size()) {
//         if (input[i+1] == ',') {
//           // cout << "HERE";
//           cout << ",\n";
//           // skip_com = true;
//           i++;
//           // continue;
//         }
//       }
//       special_char = true;
//     } else if (input[i] == ',') {
//       if (input[i-1] == '}') {
//         cout << "\n";
//         // continue;
//       } else {
//         cout << ",\n";
//         special_char = true;
//         skip_com = false;
//       }
//     }
//
//     if (!special_char) {
//       cout << input[i];
//     } else {
//       for (int j=0; j < depth; j++) {
//         cout << " ";
//       }
//       special_char = false;
//     }
//   }
//   // cout << "}" << endl;
//   cout << endl;
//
}
