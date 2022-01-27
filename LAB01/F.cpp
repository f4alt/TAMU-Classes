#include <bits/stdc++.h>

using namespace std;

int main() {
  int qnty = 0;
  string msg = "";
  int square_base = 0;
  vector<string> answer_return;
  string return_msg = "";

  cin >> qnty;

  for (int i=0; i < qnty; i++) {
    cin >> msg;
    square_base = ceil(sqrt(msg.size()));
    // char msg_matrix[square_base][square_base] = {'*'};

    // cout << msg.size() << endl;
    // cout << "HUH:" << msg[13] << endl;
    // for (int j=0; j < square_base; j++) {
    //   for (int k=0; k < square_base; k++) {
    //     // cout << "counter:" << j*square_base+k << endl;
    //     if ((j*square_base+k) >= msg.size()) {
    //       // cout << "fill:" << j*square_base+k << endl;
    //       msg_matrix[j][k] = '*';
    //     } else {
    //       msg_matrix[j][k] = msg[j*square_base+k];
    //     }
    //   }
    // }

    for (int j=0; j < square_base; j++) {
      for (int k=square_base; k > 0; k--) {
        // cout << square_base*(k-1) + j << " ";
        if (square_base*(k-1) + j > msg.size()) {
          continue;
        } else {
          cout << msg[square_base*(k-1) + j];
          // return_msg += msg[square_base*(k-1) + j];
        }
      }
    }
    cout << endl;
    // answer_return.push_back(return_msg);
    // return_msg = "";


    // sanity check
    // for (int y = 0; y < square_base; y++)
    // {
    //    for (int z = 0; z < square_base; z++)
    //    {
    //       cout << msg_matrix[y][z] << " ";
    //    }
    //    // Newline for new row
    //    cout << endl;
    // }
  }
  // for (int i=0; i < answer_return.size(); i++) {
  //   cout << answer_return[i] << endl;
  // }




  // return 0;
}
