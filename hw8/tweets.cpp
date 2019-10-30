#include <iostream>
#include <fstream>
#include <string>
#include "functions.h"

using namespace std;

/* Starter code: used by function printMenu */
void printLine(string msg) {
    cout << msg << endl;
}

/* Starter code: function printMenu() is ready for you */
void printMenu() {
    cout << endl;
    printLine("Welcome to Aggieland Twitter Feeds Stats");
    printLine("The options are:");
    printLine("1. load tweet data file and update stats");
    printLine("2. show overall stats (number of tweets, retweets, and hashtags)");
    printLine("3. show most popular hashtags");
    printLine("9. quit");
    cout << "--------> Enter your option: ";
}

/* Starter code: function to read option from the user is ready for you */
int getOption() {
    int option;
    cin >> option;
    if (cin.fail()) {
	cin.clear();
	cin.ignore(256, '\n');
	return -1;
    } else {
	cin.ignore(256, '\n');
    }
    return option;
}

int main() {
  // print menu and get initial option
  printMenu();
  int chosen_option = getOption();
  bool goodFile;
  OrderedHashtagList orderedhl;

  // keep asking for options
    while(chosen_option != 9) {
      // option 1
      if (chosen_option == 1) {
        // get filename and validate file
        string filename;
        cout << "Enter filename: ";
        cin >> filename;
        goodFile = validFile(filename);

        // if valid file, open and start sorting tweets
        if (goodFile == true) {
          string line;
          ifstream fin;
        	fin.open(filename);

          while (!fin.eof()) {
            getline(fin, line);
            // reset input parameters
            bool isRetweet = false;
            int nb_hashtags = 0;
            string* p = nullptr;

            readTweet(line, isRetweet, nb_hashtags, p);
            if (nb_hashtags > 0) {
              string temp_string;
              for (int i = 0; i < nb_hashtags; i++) {
                temp_string = p[i];
                insertHashtag(temp_string, orderedhl);
              }
            }
          }
        }
      }
      // option 2
      else if (chosen_option == 2) {
          if (goodFile == true) {
            // display right stuff
            //fill the 0's later
          cout << "Tweets: " << "0" << ", Retweets: " << "0" << ", Hashtags: " << "0" << endl;
          } else {
            // bad file or none loaded
          cout << "Tweets: " << "0" << ", Retweets: " << "0" << ", Hashtags: " << "0" << endl;
        }
      }
      // option 3
      else if (chosen_option == 3) {
          if (goodFile == true) {
            // display right stuff ie popular hashtags
          } else {
            // bad file or none loaded
          cout << "No hashtags." << endl;
        }
      }
      else {
        cout << "Invalid option" << endl;
      }
      // re cycle through menu and options
      printMenu();
      chosen_option = getOption();
    }

// test with strings *******************************
    string test_str = "12345 hello world #yeet.\n"; // length 26
    string cp_test_str;
    cout << cp_test_str << endl;
    string* string_array = new string[2];

    char str_char = test_str[0];
    int i = 0;
    int j = 0;
    while (str_char != '\n') {
      cp_test_str += str_char;
      i++;
      j++;
      str_char = test_str[i];
    }
    cout << "cp test string: ";
    // for (int numchar = 0; numchar < 27; numchar++) {
    //   cout << cp_test_str[numchar];
    // }
    cout << cp_test_str << endl;
    cout << test_str << endl;
    // string_array[0] = cp_test_str;
    // cout << string_array[0] << endl;
    // cout << string_length(test_str) << endl;
// test with strings ******************************

    return 0;
}
