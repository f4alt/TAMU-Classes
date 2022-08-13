#include <bits/stdc++.h>

using namespace std;

// A
struct boxes_info {
  long long curr_division;
  long long boxes_alloc;
  long long orig_pop;

  boxes_info(long long a, long long b, long long c) : curr_division(a), boxes_alloc(b), orig_pop(c) {}

  bool operator<(const struct boxes_info& other) const {
    return curr_division < other.curr_division;
  }
};

int main() {
  long long num_cities=0, max_boxes=0, temp;

  cin >> num_cities >> max_boxes;

  while (max_boxes != -1 && num_cities != -1) {
    // reset pq
    priority_queue<boxes_info> pq;
    // take in all cities populations and assign one box per
    for (long long i=0; i < num_cities; i++) {
      cin >> temp;

      pq.push(boxes_info(temp, 1, temp));
    }

    // dec boxes by how many cities there are since every city must get atleast one box
    max_boxes -= num_cities;

    // hand out boxes via greedy algorithm
    while (max_boxes > 0) {
      boxes_info temp = pq.top();
      temp.boxes_alloc++;
      // BE SURE TO ceil since you cant have part of a person
      temp.curr_division = ceil((float)temp.orig_pop / (float)temp.boxes_alloc);
      pq.pop();
      pq.push(temp);
      max_boxes--;
    }

    // print top of pq since it has the max division
    cout << pq.top().curr_division << endl;

    // intake next test case
    cin >> num_cities >> max_boxes;
  }



  return 0;
}
