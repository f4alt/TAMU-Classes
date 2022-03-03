#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// C

int main() {
    string input = "";
    cin >> input;

    int winStreak = 0;
    int stars = 0;
    int rank = 25;
    for (int i = 0; i < input.length(); i++) {
        if (rank == 0) {
          break;
        }
        if (input[i] == 'W') {
            // win

            // handle winStreak
            winStreak++;
            if (rank >=6 && winStreak >= 3) {
              // bonus star
              stars += 2;
            } else {
              // one star
              stars += 1;
            }

            // handle promotions
            if (rank >= 21 && rank <= 25 && stars > 2) {
              rank--;
              stars-=2;
            } else if (rank >= 16 && rank <= 20 && stars > 3) {
              rank --;
              stars -= 3;
            } else if (rank >= 11 && rank <= 15 && stars > 4) {
              rank --;
              stars -=4;
            } else if (rank >= 1 && rank <= 10 && stars > 5) {
              rank--;
              stars -=5;
            }
        } else {
            // loss
            winStreak = 0;
            if (rank > 20) {
              // do nothing
              continue;
            }
            if (stars > 0) {
              stars--;
              continue;
            }
            if (rank < 20) {
              rank++;
              if (rank >= 16 && rank <= 20) {
                stars = 2;
              } else if (rank >= 11 && rank <= 15) {
                stars = 3;
              } else if (rank >= 1 && rank <= 10) {
                stars = 4;
              }
            }
        }
    }

    if (rank == 0) {
        cout << "Legend" << endl;
    } else {
        cout << rank << endl;
    }
}
