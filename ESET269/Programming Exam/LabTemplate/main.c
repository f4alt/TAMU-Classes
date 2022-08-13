/* 
* Lab Partner Names:
* Lab #:
*/

/*Include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Function Declarations*/
void OutputInit(void); 

/*Prints menu options and returns option*/
int printMenu() {
	printf("\tUser ID Program\n\r1. View User IDS\n\r2. View User Clearance\n\r3. Add New User \n\r4. Delete User\n\r5. Quit Program\n\r");
	int menu_option;
	scanf("%d", &menu_option);
	
	if (menu_option > 0 && menu_option < 6) {
		return menu_option;
	} else {
		printf("\n\rInvalid Option");
		printMenu();
	}
	return -1;
}

/* Prints user id's to console */
void view_ids(char user_ids[5][7]) {
	// blank line for output
	printf("\n\r");
	
	// iterates through ids displays when applicable
	for (int i = 0; i < 5; i++) {
		// dont display positions with nothing
		if (strcmp(user_ids[i], "") == 0) {
		} else {
			printf("%s\n\r", user_ids[i]);
		}
	}
	
	// blank line for output
	printf("\n\r");
}

/* Prints user clearance to console */
void view_clearance(char user_ids[5][7]) {
	char clearance;
	
	// blank line for output
	printf("\n\r");
	
	// iterates through ids displays when applicable
	for (int i = 0; i < 5; i++) {
		// dont display positions with nothing
		int result = strcmp(user_ids[i], "");
		if (result == 0) {
			
		} else {
			int clearance_total = 0;
			for (int j = 2; j < 6; j++) {
				clearance_total += user_ids[i][j] - 48;
			}
			if (clearance_total <= 10) {
				clearance = 'A';
			} else if (clearance_total > 10 && clearance_total <= 25) {
				clearance = 'B';
			} else if (clearance_total > 25) {
				clearance = 'C';
			}
			printf("User %s has clearance %c.\n\r", user_ids[i], clearance);
		}
	}
	
	// blank line for output
	printf("\n\r");
}

/* Adds user to ID to array */
void add_id(char user_ids[5][7]) {
	char new_id[15];
	int zero_count = 0;
	char* invalid_msg = "\rInvalid user ID!\n\n\r";
	
	// take in user_id to be added
	printf("Enter new User ID:");
	scanf("%s", new_id);
	
	// check first two capital letters
	for (int i = 0; i < 2; i++) {
		char temp = new_id[i];
		if (temp < 65 || temp > 90) {
			printf("%s", invalid_msg);
			return;
		}
	}
	
	// check for 4 numbers and not all 0
	for (int i = 2; i < 6; i++) {
		char temp = new_id[i];
		if (temp < 48 || temp > 57) {
			printf("%s", invalid_msg);
			return;
		}
		if (temp == 48) {
			zero_count++;
		}
	}
	if (zero_count == 4) {
		printf("%s", invalid_msg);
		return;
	}
	
	// make sure only 6 long
	if (strlen(new_id) > 6) {
		printf("%s", invalid_msg);
		return;
	}
	
	// check for available spot to fill
	for (int i = 0; i < 5; i++) {
		if (strcmp(user_ids[i], "") == 0) {
			strcpy(user_ids[i], new_id);
			printf("\rUser ID entered!\n\n\r");
			return;
		}
	}
	printf("\n\rToo many user_ids\n\n\r");
}

/* Removes user ID from array at index x */
void remove_id(char user_ids[5][7]) {
	int rmv_idx;
	printf("Select user to remove via number:");
	scanf("%d", &rmv_idx);
	
	// check for valid index
	if (strcmp(user_ids[rmv_idx-1], "") == 0 || rmv_idx < 1 || rmv_idx > 5) {
		printf("No user %d exists!\n\n\r",rmv_idx);
		return;
	}
	
	// replace index with ""
	strcpy(user_ids[rmv_idx-1], "");
	
	// cascade other indexes up to fill removal
	for (int i = 0; i < 4; i++) {
		if (strcmp(user_ids[i], "") == 0) {
			if (strcmp(user_ids[i+1], "") != 0) {
				strcpy(user_ids[i], user_ids[i+1]);
				strcpy(user_ids[i+1], "");
			}
		}
	}
	printf("User %d removed!\n\n\r", rmv_idx);
}

int main(void)
	{
    /*Setup Launchpad for Printf & Scanf*/
		OutputInit(); 
		
		/* Place application code here */
		char user_ids[5][7] = { "DK2346", "JM1102", "GW8990", "", "" };
		int menu_option = 0;
		
		while (menu_option != 5) {
			menu_option = printMenu();
			switch (menu_option) {
				case 1:
					view_ids(user_ids);
					break;
				case 2:
					view_clearance(user_ids);
					break;
				case 3:
					add_id(user_ids);
					break;
				case 4:
					remove_id(user_ids);
					break;
				case 5:
					printf("\nProgram Done");
					break;
				default:
					printf("\nInvalid option");
					break;
			}
		}
		
		/*Go in waiting state. Will modify in later labs*/
		while(1);
  }
