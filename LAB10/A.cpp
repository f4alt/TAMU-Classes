#include <bits/stdc++.h>

using namespace std;

struct triplet {
	int first;
	int second;
	int third;
};

struct action {
	int timestamp;
	string person;
	char act;
	int value = 0;
	string name = "";

	bool operator<(const action& act) const {
		return timestamp < act.timestamp;
	}
};

int main() {
	int test_cases;
	cin >> test_cases;

	while (test_cases--) {
		int cars, actions;
		cin >> cars >> actions;

		unordered_map<string, triplet> stats;

		string car_name;
		while (cars--) {
			triplet t;
			cin >> car_name >> t.first >> t.second >> t.third;
			stats[car_name] = t;
		}

		unordered_map<string, string> owner;
		map<string, int> payment;

		vector<action> action_vec;

		while (actions--) {
			action a;
			cin >> a.timestamp >> a.person >> a.act;

			if (a.act == 'p') {
				cin >> a.name;
			} else {
				cin >> a.value;
			}

			action_vec.push_back(a);
		}

		sort(action_vec.begin(), action_vec.end());

		for (auto i : action_vec) {
			if (payment[i.person] == INT_MIN) {
				continue;
			}

			if ((i.act == 'p' && owner[i.person] != "") || (i.act != 'p' && owner[i.person] == "")) {
				payment[i.person] = INT_MIN;
				continue;
			}

			if (i.act == 'p') {
				owner[i.person] = i.name;
				payment[i.person] += stats[i.name].second;
			}

			if (i.act == 'a') {
				payment[i.person] += ceil((stats[owner[i.person]].first * i.value) / 100.00);
			}

			if (i.act == 'r') {
				payment[i.person] += stats[owner[i.person]].third * i.value;
				owner[i.person] = "";
			}
		}

		for (auto i : payment) {
			cout << i.first << " ";
			if (owner[i.first] != "" || i.second == INT_MIN) {
				cout << "INCONSISTENT" << endl;
			} else {
				cout << i.second << endl;
			}
		}

	}

	return 0;
}
