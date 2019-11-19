#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "functions.h"



/* readTweet
 * Parameters:
 *      line: string containing the tweet information received by the function
 *      isRetweet: reference to bool; function will update it with true if retweet
 *      nb_htags: reference to int; function will update with number of hashtags
 *                in the tweet.
 *      array_of_htags: reference to an array of strings; function will allocate
 *                      the array and store the hashtag in it
 * Return value:
 *      none
 * Functionality:
 *     Processes the string in order to find out hashtags and identify if it is Retweet
 */
void readTweet(string line, bool& isRetweet, int& nb_htags, string*& array_of_htags) {
		string found_hashtag;
		int i = 0;
		char line_char = line[0];

		// first pass:
		while (line_char != '\n') {

			line_char = line[i];
			i++;

			// looking for RT
			if (line[i] == 'R') {
				if (line[i+1] == 'T') {
					if (line[i+2] == ' ') {
						isRetweet = true;
					}
				}
			}
			// if hashtag symbol is found
			if (line_char == '#') {
				// first pass just updates number of hashtags and total amount
				nb_htags++;
			}
		}

		// grow array_of_htags if hashtags are found
		if (nb_htags > 0) {
			string* htags = new string[nb_htags];

		// second pass:
		line_char = line[0];
		i = 0;
		int k = 0;

		while (line_char != '\n') {
			if (line_char == '#') {
				int j = 0;
				found_hashtag.clear();
				while (line_char != ' ') {
					if (i == 0) {
						i++;
					}
					line_char = line[i];
					if (line_char == ' ') {
						break;
					}
					// cout << line_char << endl; //************
					// break if hashtag is at end of file
					if (line_char == '\n') {
						break;
					}
					// occasional . after hashtag need to also break
					if (line_char == '.') {
						break;
					}
					// cout << line_char; //**************
					i++;
					found_hashtag += line_char;
					// cout << found_hashtag; //******************
					j++;
				}
				// cout << found_hashtag << ": in function" << endl; //******************
				htags[k] = found_hashtag;
				k++;
			}
			line_char = line[i];
			i++;
		}

		array_of_htags = htags;
	}
}

/* insertHashtag
 * Parameters:
 *      ht: string
 *      hashlist: reference to OrderedHashtagList struct
 * Return value:
 *      true if insertion succeeds, false if memory allocation
 *      fails.
 * Functionality:
 *      See prompt for specification and examples.
 */

bool insertHashtag(string ht, OrderedHashtagList& hashlist) {
	string temp_hashtagname;
	string make_sure_string_is_clean;
	bool already_in_list = false;
	// use to lower to make string uniform
	for (int i = 0; i < ht.length(); i++) {
		if ((ht[i]) == '\n') {
			break;
		}
		if (ht[i] == ' ') {
			break;
		}
		if (ht[i] == '\0') {
			break;
		}
		make_sure_string_is_clean += tolower(ht[i]);
	}
	// cout << make_sure_string_is_clean << endl; //************

	// compare with ordered hashtaglist hashlist.list[i].name
	// check if this is the first hashtag to go into the list
	if (hashlist.size == 0) {
		hashlist.list[0].name = make_sure_string_is_clean;
		hashlist.list[0].counter = 0;
		hashlist.size = 1;
		// cout << hashlist.size << " " << hashlist.capacity << endl; //**********
	}
	// cout << "at beginning: " << hashlist.list[0].counter << endl; //*********

	// resize if at capacity
	if (hashlist.size == hashlist.capacity) {
		int old_capacity = hashlist.capacity;
		hashlist.size = old_capacity;

		// cout << "hashlist is at capacity - "; //testline *************
		// cout << "old capacity: " << old_capacity << " - "; //*******************

		// allocate new space
		Hashtag* newlist = new Hashtag[old_capacity * 2];

		// put old values into new array
		for (int i = 0; i < hashlist.capacity; i++) {
			newlist[i].name = hashlist.list[i].name;
			newlist[i].counter = hashlist.list[i].counter;
		}

		// update capacity
		hashlist.capacity = old_capacity * 2;

		// delete old list
		delete[] hashlist.list;
		// set new list to old list location
		hashlist.list = newlist;

		// test print block********************
		// cout << "capacity was updated: ";//*************
		// cout << "new capacity: " << hashlist.capacity << endl; //**************
		// cout << "updated size: " << hashlist.size << endl;//**********
	}

	// iterate through hashlist, if found update count and bool
	for (int i = 0; i < hashlist.size; i++) {
		temp_hashtagname = hashlist.list[i].name;
		// if hashtag is already in list, update count
		if (make_sure_string_is_clean == temp_hashtagname) {
			// cout << ht << " found" << endl; //********************
			hashlist.list[i].counter += 1;


			already_in_list = true;
		}
	}

		// sort
		for (int i = 1; i < hashlist.size; i++) {
			pushup(hashlist, i);
		}

	// if not found in list, add to end of array
	if (already_in_list == false) {
		// cout << "new hashtag: " << make_sure_string_is_clean << endl; //************
		int last_position = hashlist.size;
		// cout << "size: " << hashlist.size << " capacity: " << hashlist.capacity << endl; //********
		hashlist.list[last_position].name = make_sure_string_is_clean;
		hashlist.list[last_position].counter = 1;
		hashlist.size += 1;
	}
    return true;
}

/* showMostPopularHashtags
 * Parameters:
 *      hashlist: reference to OrderedHashtagList struct
 * Return value:
 *      none
 * Functionality:
 *      Prints the k most popular hashtags.
 *      See prompt for formatting details.
 */
void showMostPopularHashtags(OrderedHashtagList hashlist, int k) {
    cout << "To be implemented by the student" << endl;
}

bool validFile(string filename) {
	ifstream fin;
	fin.open(filename);

	if (!fin) {
		cout << "File can't be open." << endl;
		return false;
	}
	fin.close();
	return true;
}

int string_length(string string) {
	int length = 0;
	int i = 0;
	char letter = string[0];
	while (letter != '\0') {
		letter = string[i];
		length++;
		i++;
	}
	return length;
}

void pushup(OrderedHashtagList hashlist, int i) {
	if (hashlist.list[i].counter >= hashlist.list[i-1].counter) {
		Hashtag temp1 = hashlist.list[i];
		Hashtag temp2 = hashlist.list[i-1];
		hashlist.list[i-1] = temp1;
		hashlist.list[i] = temp2;
	}
}
