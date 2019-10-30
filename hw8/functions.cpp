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
			// looking for RT
			if (line_char == 'R') {
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

			line_char = line[i];
			i++;
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
				while (line_char != ' ') {
					found_hashtag += line_char;
					line_char = line[i];
					i++;
					j++;
				}
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
// use to lower
// compare with ordered hashtaglist hashlist.list[i].name
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
