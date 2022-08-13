/* 
* Lab Partner Names: Christopher McGregor
* Lab #: 1
*/

/*Include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Function Declarations*/
void OutputInit(void); 

int main(void)
	{
    /*Setup Launchpad for Printf & Scanf*/
		OutputInit(); 
		
		/* Place application code here */
		/* ****************
						CODE 1
			 **************** */  		
		printf("***** CODE 1 *****\n\n\r");
		
		/* ***** VARIABLES ***** */
		char input_user_name[20];
		char input_password[20];
		char valid_user_name[] = "Admin";
		char valid_password[] = "PASS";
		char wrong_user_name[] = "Wrong login name";
		char wrong_password[] = "Wrong password";
		char wrong_both[] = "Wrong login name and password";
		char success[] = "Correct Login";
		int error = 1;
		
		while (error != 0) {
			error = 0;	// reset error
			
			// prompt for username and pass
			printf("Enter user name:");
			scanf("%s",input_user_name);
			printf("\rEnter password:");
			scanf("%s",input_password);
			
			// compare input to see if valid user + pass
			if (strcmp(input_user_name,valid_user_name) != 0) {
				error += 1;
			} 
			if (strcmp(input_password,valid_password) != 0) {
				error += 2;
			}
			
			// print correct message
			if (error == 0) {
				printf("%s",success);
			} else if (error == 1) {
				printf("%s\n\n\r",wrong_user_name);
			} else if (error == 2) {
				printf("%s\n\n\r",wrong_password);
			} else {
				printf("%s\n\n\r",wrong_both);
			}
		}
		
		/* ****************
						CODE 2
			 **************** */
		
		printf("\n\n\r***** CODE 2 *****\n\n\r");
		
		/* ***** VARIABLES ***** */
		int SBP, DBP, PP;
		float MAP;
		
		// Prompt user for SBP and MPB
		printf("Enter SBP:");
		scanf("%d",&SBP);
		printf("Enter MPB:");
		scanf("%d",&DBP);
		
		// find PP and MAP
		PP = SBP - DBP;
		MAP = (2 * ((float)DBP + (float)SBP)) / 3;
		
		// print PP and MAP
		printf("Pulse Pressure:%d\n\r",PP);
		printf("MAP:%.2f\n\r",MAP);
		
		// determine Blood pressure category and print
		if (SBP < 120 && DBP < 80) {
			printf("NORMAL");
		} else if (SBP < 130 && DBP < 80) {
			printf("ELEVATED");
		} else if (SBP < 140 && DBP < 90) {
			printf("HYPERTENSION Stage 1");
		} else {
			printf("HYPERTENSION Stage 2");
		}

		/*Go in waiting state. Will modify in later labs*/
		while(1);
  }
