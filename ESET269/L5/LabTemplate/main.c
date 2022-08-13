/* 
* Lab Partner Names:
* Lab #:
*/

/*Include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*Function Declarations*/
void OutputInit(void); 

// prints menu options and returns ascii int for whatever letter option is chosen
int Menu1() {
	char option;
	printf("\n\rSelect option.\n\ra.Capital all letters\n\rb.Count letters\n\rc.lowercase all\n\rd.replace string\n\r");
	scanf("%c",&option);
	return option;
}

// takes in option and string. option uses ascii aquivelent for a-d options and changes string accordingly
void modString(int opt, char string[]) {
	int numLetters = 0;
	
	switch(opt) {
		case 97: // 'a' - all uppercase
			for (int i = 0; i < strlen(string); i++) {
				string[i] = toupper(string[i]);
			}
			printf("Modified string is %s", string);
			break;
		case 98: // 'b' - count letters only
			for (int i = 0; i < strlen(string); i++) {
				if (isalpha(string[i])) {
					numLetters++;
				}
			}
			printf("Number of letters is %d", numLetters);
			break;
		case 99: // 'c' - all lower
			for (int i = 0; i < strlen(string); i++) {
				string[i] = tolower(string[i]);
			}
			printf("Modified string is %s", string);
			break;
		case 100: // 'd' - replace string
			printf("New String Value:");
			scanf("%s", string);
			printf("Replaced old string with %s", string);
			break;
		default:
			printf("invalid option");
			break;
	}
}

int Menu2() {
	int opt;
	printf("1. Area of circle\n\r2. Volume of sphere\n\r");
	scanf("%d", &opt);
	return opt;
}

float getRadius() {
	float r;
	printf("Enter a radius value:");
	scanf("%f", &r);
	return r;
}

float calVolume(int opt, float r) {
	float result;
	switch (opt) {
		case 1: // calculate vol of circle
			result = 3.141592652589 * pow(r, 2);
			printf("The area of a circle is %.2f", result);
			break;
		case 2:
			result = 1.333333333 * 3.141592652589 * pow(r, 3);
			printf("The volume of a sphere is %.2f", result);
			break;
		default:
			printf("invalid option");
			break;
	}
}

int main(void)
	{
    /*Setup Launchpad for Printf & Scanf*/
		OutputInit(); 
		
		/* ******************
						TASK 1
			 ****************** */
		// VARIABLES //
		char user_input[30];
		
		// prompt user for initial string
		printf("Enter a string:");
		scanf("%s", user_input);

		// call menu() to generate option and pass user string into modString
		modString(Menu1(), user_input);
		
		/* ******************
						TASK 2
			 ****************** */
		printf("\n\n\n\r"); // print space between task 1 and 2
		// VARIABLES //
		float r;
		
		// prompt user for radius
		printf("Enter a radius value:");
		scanf("%f", &r);
		
		// call menu() to generate option and pass r into calVolume funct
		calVolume(Menu2(), r);
		
		/*Go in waiting state. Will modify in later labs*/
		while(1);
  }
