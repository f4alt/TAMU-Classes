#include <bits/stdc++.h>

using namespace std;

// A

int main() {
  int left[1000], right[1000], temp_left, temp_right, loop, temp;
  bool stack_bool=true, queue_bool=true, pq_bool=true;

  while (!cin.eof()) {
    stack_bool=true, queue_bool=true, pq_bool=true;
    stack<int> stack;
    queue<int> queue;
    priority_queue<int> pq;
    // stack.clear();
    // queue.clear();
    // pq.clear();

    cin >> loop;
    if (cin.eof()) {
      break;
    }
    for (int i=0; i < loop; i++) {
      cin >> temp_left >> temp_right;

      left[i] = temp_left;
      right[i] = temp_right;
    }

    for (int i=0; i < loop; i++) {
      if (left[i] == 2) {
        if (stack.empty()) {
          // cout << "empty" << endl;
          stack_bool = false;
          break;
        }
        // if (!stack.empty()) {
          if (right[i] != stack.top()) {
            // cout << "mismatch" << endl;
            stack_bool = false;
            break;
          }
          stack.pop();
        // }
      } else {
        stack.push(right[i]);
      }
    }

    for (int i=0; i < loop; i++) {
      if (left[i] == 2) {
        if (queue.empty()) {
          queue_bool = false;
          break;
        }
        // if (!queue.empty()) {
          if (queue.front() != right[i]) {
            queue_bool = false;
            break;
          }
          queue.pop();
        // }
      } else {
        queue.push(right[i]);
      }
    }

    for (int i=0; i < loop; i++) {
      if (left[i] == 2) {
        if (pq.empty()) {
          pq_bool = false;
          break;
        }
        // if (!pq.empty()) {
          if (pq.top() != right[i]) {
            pq_bool = false;
            break;
          }
          pq.pop();
        // }
      } else {
          pq.push(right[i]);
        }
    }


    if (!stack_bool && !queue_bool && !pq_bool) {
      cout << "impossible" << endl;
    } else if (stack_bool && !queue_bool && ! pq_bool) {
      cout << "stack" << endl;
    } else if (!stack_bool && queue_bool && !pq_bool) {
      cout << "queue" << endl;
    } else if (!stack_bool && !queue_bool && pq_bool) {
      cout << "priority queue" << endl;
    } else {
      cout << "not sure" << endl;
    }
  }



  return 0;
}
