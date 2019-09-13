#include <iostream>

using namespace std;

int input = 1, check_input, list_length = 1;
bool decending_status = true, ascending_status = true, decending_final = true, ascending_final = true;

bool check_decending(int check) {
  if (check_input > check) {
    check_input = check;
    // cout << "New check_input is " << check_input << endl;
    return true;
  } else {
    return false;
  }
}

bool check_ascending(int check) {
  if (check_input <= check) {
    check_input = check;
    return true;
  } else {
    return false;
  }
}

int main() {
  cin >> check_input;
  while (input != 0) {
    cin >> input;
    if (input == 0) {
      break;
    }
    list_length++;
    ascending_status = check_ascending(input);
    decending_status = check_decending(input);
    if (decending_final == true) {
      check_decending(input);
      decending_final = true;
    }
    if (ascending_final == true) {
      check_ascending(input);
      ascending_final = true;
    }
    if (decending_status == false) {
      decending_final = false;
      // cout << "decending flagged false" << endl; //test line
    }
    if (ascending_status == false) {
      ascending_final = false;
      // cout << "ascending flagged false" << endl; //test line
    }
    // cout << ascending_final << decending_final << endl; //test line
  }
  if (decending_final == true || ascending_final == true) {
    cout << list_length << " sorted" << endl;
  } if (decending_final == false && ascending_final == false) {
    cout << list_length << " unsorted" << endl;
  }
  return 0;
}
