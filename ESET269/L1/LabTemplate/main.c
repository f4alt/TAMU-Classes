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
		
		/* ***********
			  	CODE 1
		   *********** */
		printf("***** CODE 1 *****\n\n\r");
		
		/* **** VARIABLES **** */
		int test_int = 269;
		float test_float = 14.95;
		char test_string[] = "Launchpad";
		char test_char = '!';
		
  	// print info
		printf("Practice using printf()\n\r\tESET %d\n\n\rC coding. %.2f weeks to go\n\r%s\n\r\t%c", test_int,test_float,test_string,test_char);
		
		
		/* ***********
			  	CODE 2
		   *********** */
		
		printf("\n\n\r***** CODE 2 *****\n\n\r");
		/* **** VARIABLES **** */
		char first_i;
		char last_i;
		int fav_num;
		float dec_num;
		
    // prompt user input for first inital, last initial, favorite num, and a decimal num to 3 places
		printf("What is initial of first name?\n\r");
		scanf("%c",&first_i);
		printf("What is initial of last name?\n\r");
		scanf("%c",&last_i);
		printf("What is your favorite number?\n\r");
		scanf("%d",&fav_num);
		printf("Write a decimal number as x.xxx\n\r");
		scanf("%f",&dec_num);

		// print info
		printf("First initial %c, Last initial %c, fav. # %d, decimal # %.3f",first_i,last_i,fav_num,dec_num);

		/* ***********
			  	CODE 3
		   *********** */
		
		printf("\n\n\r***** CODE 3 *****\n\n\r");
		
		/* **** VARIABLES **** */
		char first_name[20];
		char last_name[20];
		int age;
		
		// Prompt user input for first name, last name and age
		printf("Enter first name:");
		scanf("%s",first_name);
		printf("\rEnter last name:");
		scanf("%s",last_name);
		printf("\rEnter age:");
		scanf("%d",&age);
		
		// print info
		printf("\rFirst name:%s Last name:%s Age:%d",first_name,last_name,age);
		
		// change variable data
		strcpy(first_name,"John");
		strcpy(last_name,"Doe");
		age=99;
		
		// print info
		printf("\n\n\rFirst name:%s Last name:%s Age:%d",first_name,last_name,age);
		
		
		
		/*Go in waiting state. Will modify in later labs*/
		while(1);
  }
