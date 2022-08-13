#include <iostream>
using namespace std;

int main() {
  // test array
  int A[][4] = {
    {2,16,13,3},
    {11,5,8,10},
    {7,9,12,6},
    {14,4,1,15}
  };



  int current_row_total;
  int row_total;
  int column_total;

  for (int i = 1; i < 4 * 4; i++) { //change dim back to 4
    for (int j = 0; j < 4; j++) { //same
      for (int k = 0; k < 4; k++) { //same
        if (A[j][k] == i) {
          k++;
          cout << A[j][k] << endl;
          return -1;
        }
      }
    }
  }

  /*for (int i = 0; i < dim; i++) {
    row_total += A[0][i];
    for (int j = 0; j < dim; j++) {
      current_row_total += A[i][j];
      if (current_row_total != row_total) {
        return false;
      }
    }
  }*/

  return 0;
}
