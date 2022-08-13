#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// F

int main() {
    int players, queries, player1, player2;
    string move1, move2;

    while (true) {
        cin >> players;
        int wins[players] = {0};
        int losses[players] = {0};
        if (players == 0) {
            return 0;
        }
        cin >> queries;
        queries = queries * players * (players-1) / 2;
        while (queries--) {
            // scanf("%d %s %d %s\n", &player1, &move1, &player2, &move2);
            cin >> player1 >> move1 >> player2 >> move2;
            // cout << player1 << " | " << move1 << endl;
            if (move1 == "rock") {
                if (move2 == "paper") {
                    // cout << "p2 win" << endl;
                    wins[player2-1]++;
                    losses[player1-1]++;
                } else if (move2 == "scissors") {
                    // cout << "p1 win" << endl;
                    wins[player1-1]++;
                    losses[player2-1]++;
                }
            }
            if (move1 == "paper") {
                if (move2 == "scissors") {
                    // cout << "p2 win" << endl;
                    wins[player2-1]++;
                    losses[player1-1]++;
                } else if (move2 == "rock") {
                    // cout << "p1 win" << endl;
                    wins[player1-1]++;
                    losses[player2-1]++;
                }
            }
            if (move1 == "scissors") {
                if (move2 == "rock") {
                    // cout << "p2 win" << endl;
                    wins[player2-1]++;
                    losses[player1-1]++;
                } else if (move2 == "paper") {
                    // cout << "p1 win" << endl;
                    wins[player1-1]++;
                    losses[player2-1]++;
                }
            }
        }
        for (int i=0; i < players; i++) {
            if (wins[i] == 0 && losses[i] == 0) {
                cout << "-" << endl;
            } else {
                printf("%.3f\n", (float)wins[i] / ((float)losses[i] + (float)wins[i]));
            }
            // cout << (float)wins[i] / ((float)losses[i] + (float)wins[i]) << endl;
        }
        cout << endl;
    }
}
