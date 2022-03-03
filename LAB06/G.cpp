#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <math.h>

using namespace std;

// G
struct cmp
{
    inline bool operator() (const string& s1, const string& s2)
    {
        // return (struct1.key < struct2.key);
        if (s1[0] <= s2[0] && s1[1] < s2[1]) {
            return true;
        } 
        else if (s1[0] < s2[0]) {
            return true;
        } 
        else {
            return false;
        }
    }
};

int main() {
    int loop;
    string temp;


    while (true) {
        cin >> loop;
        if (loop == 0){
            return 0;
        }
        vector<string> names;
        // std::priority_queue<string, std::vector<string>,  CustomCompare > q;
        while (loop--) {
            cin >> temp;
            names.push_back(temp);
            // q.push(temp);
        }
        stable_sort(names.begin(), names.end(), cmp());
        for (auto i : names) {
            cout << i << endl;
        }
        cout << endl;
    }
}
