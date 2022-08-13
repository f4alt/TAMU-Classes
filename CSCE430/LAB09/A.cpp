#include <bits/stdc++.h>

using namespace std;

int scores_table[30] = {100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

bool s_sort(vector<int> lhs, vector<int> rhs) {
    return (lhs[0] > rhs[0]);
}

bool p_sort(vector<int> lhs, vector<int> rhs) {
    return (lhs[1] < rhs[1]);
}

bool f_sort(vector<int> lhs, vector<int> rhs) {
    return (lhs[2] < rhs[2]);
}

int main() {
    int n, s, p, f, o, tie;

    cin >> n;

    vector<vector<int>> stats;

    for (int i = 0; i < n; i++) {
        vector<int> temp;
        tie = 0;

        cin >> s >> p >> f >> o;

        temp.push_back(s);
        temp.push_back(p);
        temp.push_back(f);
        temp.push_back(o);

        // check for tie
        for (int j = 0; j < stats.size(); j++) {
            if (stats[j][0] == s && stats[j][1] == p && stats[j][2] == f) {
                tie = 1;
                break;
            }
        }

        temp.push_back(tie);
        stats.push_back(temp);
    }

    vector<vector<int>> duplicate_stats = stats;

    stable_sort(stats.begin(), stats.end(), f_sort);
    stable_sort(stats.begin(), stats.end(), p_sort);
    stable_sort(stats.begin(), stats.end(), s_sort);


    // for (int i = 0; i < stats.size(); i++) {
    //     for (int j = 0; j < stats[i]size(); j++) {
    //         cout << stats[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    vector<int> new_order;
    for (int i = 0; i < duplicate_stats.size(); i++) {
        for (int j = 0; j < stats.size(); j++) {
            if (duplicate_stats[i][0] == stats[j][0] &&
                duplicate_stats[i][1] == stats[j][1] &&
                duplicate_stats[i][2] == stats[j][2] &&
                duplicate_stats[i][3] == stats[j][3]) {
                new_order.push_back(j);
                break;
            }
        }
    }

    // cout << "HERE" << endl;
    // cout << duplicate_stats.size() << " | " << stats.size() << endl;
    // for (int i = 0; i < new_order.size(); i++) {
    //     cout << new_order.at(i) << endl;
    // }
    // cout << "END" << endl;

    vector<int> scores;
    int tie_counter = 0;
    float tie_score = 0;

    for (int i = 0; i < n; i++) {
        if (stats[i][4] == 1) {
            if (tie_counter == 0) {
                tie_score += i <= 30 ? scores_table[i-1] : 0;
                for (int j = i; j < n; j++) {
                    if (stats[j][4] == 0) {
                        break;
                    }
                    tie_score += j+1 <=30 ? scores_table[j] : 0;
                    tie_counter++;
                }

                tie_score /= (tie_counter + 1);
                tie_score = ceil(tie_score);
                scores.back() = (tie_score+stats[i-1][3]);
                scores.push_back(tie_score+stats[i][3]);
            } else {
                scores.push_back(tie_score+stats[i][3]);
            }
        } else {
            tie_counter = 0;
            tie_score = 0;
            if (i+1 <= 30) {
              scores.push_back(scores_table[i]+stats[i][3]);
            } else {
              scores.push_back(stats[i][3]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << scores[new_order[i]] << endl;
    }


















    return 0;
}
