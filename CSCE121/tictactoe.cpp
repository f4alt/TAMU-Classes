/* prints playable tictactoe game */
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::cin;
using std::setw;

void print_board(char A[][8], int width, int height) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      cout << A[i][j];
    }
    cout << endl;
  }
}

int main() {
  char board[][8] = {
    {"-------"},
    {"| | | |"},
    {"-------"},
    {"| | | |"},
    {"-------"},
    {"| | | |"},
    {"-------"},
  };

  cout << "Enter position as T/M/B L/M/R ie, topleft = TL" << endl;
  print_board(board, 7, 7);

  return 0;
}
