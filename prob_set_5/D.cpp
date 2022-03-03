#include <bits/stdc++.h>

using namespace std;

void printBoard(vector<vector<bool>> &board, vector<vector<int>>& amounts) {
  for (int row=0; row < board.size(); row++) {
    for (int col=0; col < board[0].size(); col++) {
      cout << board[row][col] << " ";
    }
    cout << "| " << amounts[0][row] << "\n";
  }
  cout << "---------\n";
  for (int i=0; i < amounts[1].size(); i++) {
    cout << amounts[1][i] << " ";
  }
  cout << "\n\n";
}

bool checkPos(vector<vector<bool>> &board, vector<vector<int>>& amounts, int r, int c) {
  if (board[r][c] == true) {
    return false;
  }
  if (amounts[0][r] > 0 && amounts[1][c] > 0) {
    return true;
  } else {
    return false;
  }
}

bool brute(vector<vector<bool>> &board,
          vector<vector<int>>& amounts,
          long long& pieces,
          int r,
          int c)
{
  if (pieces == 0) {
    return true;
  }
  // int col_start;
  // for (col_start=0; col_start < amounts[1].size(); col_start++) {
  //   if (amounts[1][col_start] != 0) {
  //     break;
  //   }
  // }
  bool valid = false;
  // for (int row=r; row < amounts[0].size(); row++) {
  //   for (int col=0; col < amounts[1].size(); col++) {
  for (int row=r; row < board.size(); row++) {
    for (int col=0; col < board[0].size(); col++) {
      if (amounts[0][row] == 0) {
        break;
      }

      if (checkPos(board, amounts, row, col)) {
        printBoard(board, amounts);

        amounts[0][row]--;
        amounts[1][col]--;
        pieces--;
        board[row][col] = true;
        valid = brute(board, amounts, pieces, row, col);
        if (valid) {
          return true;
        }
        amounts[0][row]++;
        amounts[1][col]++;
        pieces++;
        board[row][col] = false;
      }
    }
  }
  return valid;
}

int main() {
  int row_amt, col_amt, temp;
  long long row_pieces=0, col_pieces=0;

  cin >> row_amt >> col_amt;

  vector<vector<int>> amounts;
  vector<int> row_tot(row_amt);
  vector<int> col_tot(col_amt);
  vector<vector<bool>> board;
  vector<bool> row_false(col_amt, false);
  vector<bool> row_true(col_amt, true);


  int full_rows=0;
  for (int i=0; i < row_amt; i++) {
    cin >> temp;
    row_tot[i] = temp;
    if (temp == col_amt) {
      // board.push_back(row_true);
      row_tot[i] = 0;
      full_rows++;
    } else {
      board.push_back(row_false);
      row_pieces += temp;
    }
  }
  for (int i=0; i < col_amt; i++) {
    cin >> temp;
    col_tot[i] = temp - full_rows;
    if (temp == row_amt) {
      for (int j=0; j < row_amt; j++) {
        row_tot[j]--;
        board[j].erase(board[j].begin() + i);
        // board[j][i] = true;
      }
      col_tot[i] = 0;
      row_pieces -= row_amt - full_rows;
    } else {
      col_pieces += temp - full_rows;
    }
  }

  // if (row_pieces != col_pieces) {
  //   cout << "No\n";
  //   return 0;
  // }

  sort(row_tot.begin(), row_tot.end(), greater<int>());
  sort(col_tot.begin(), col_tot.end(), greater<int>());
  // amounts[0] = row totals
  // amounts[1] = col totals
  amounts.push_back(row_tot);
  amounts.push_back(col_tot);

  // cout << "board: " << board.size() << " | " << board[0].size() << endl;
  // cout << "amounts: " << amounts[0].size() << " | " << amounts[1].size() << endl;
  // cout << "pieces needed: " << row_pieces << " | " << col_pieces << endl;
  // printBoard(board, amounts);

  // cout << brute(board, amounts, total_amts, 0, 0) << endl;
  if (brute(board, amounts, row_pieces, 0, 0)) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }



  return 0;
}
