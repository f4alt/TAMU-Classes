/* 
* Lab Partner Names: Christopher McGregor
* Lab #: 3
*/

/*Include files */
#include <stdio.h>
#include <stdlib.h>

/*Function Declarations*/
void OutputInit(void); 

void printMenu() {
	printf("\n\n\rSelect option\n\r1.Withdraw\n\r2.Deposit\n\r3.Quit\n\n\r");
}

// Withdraw function passes balance by reference and prompts
// user for withdraw amount, if valid amount balance is updated
int Withdraw(float *balance) {
	float withdraw_amount;
	
	printf("How much to withdraw:");
	scanf("%f",&withdraw_amount);
	
	if (withdraw_amount <= *balance) {																				// check valid withdraw
		*balance -= withdraw_amount;																						// update balance if valid and return true
		printf("\rBalance remaining: $%.2f",*balance);
		return 1;
	} else {																																	// invalid withdraw - return 0
		printf("\rNot enough funds!");
		return 0;
	}
}

// Deposit function passes balance and deposit total by reference
// if deposit amount is within allotted deposit total, balance is updated
void Deposit(float *balance, float *deposit_total) {
	float deposit_amount;
	
	printf("Deposit how much:");
	scanf("%f",&deposit_amount);
	
	if (deposit_amount <= *deposit_total) {																		// check deposit amount is less than allotted deposit total
		*balance += deposit_amount;																							// update balance and deposit total if valid
		*deposit_total -= deposit_amount;
		printf("New Balance: $%.2f",*balance);
	} else {
		printf("Reached max deposit limit.");
	}
}
	

int main(void)
	{
    /*Setup Launchpad for Printf & Scanf*/
		OutputInit(); 
		
		/* Place application code here */
		
		// Variables
		int user_pin = 0;
		int correct_pin = 3344;
		int user_choice = 0;
		char incorrect_pin[] = "Entered Wrong PIN";
		float balance = 0;
		int withdraw_count = 0;
		float deposit_total = 10000;
		
		// Driver code
		do {
			printf("Enter PIN #:");																								// check for valid pin
			scanf("%d",&user_pin);
			if (user_pin == correct_pin) {
				while (user_choice != 3) {																					// pin accepted, prompt user menu
					printMenu();
					scanf("%d",&user_choice);
					switch (user_choice) {
						case 1:
							if (withdraw_count < 3) {																			// check withdraw count and attempt withdraw if < 3
								withdraw_count += (Withdraw(&balance) == 1) ? 1 : 0;
							} else {
								printf("Too many withdraws made.");
							}
							break;
						case 2:
							Deposit(&balance, &deposit_total);														// deposit
							break;
						case 3:																													// break condition
							printf("Transactions Done.");
							return 1;
						default:
							printf("Error, invalid option - try again");
							break;
					}
				}
			}
			printf("\r%s\n\r",incorrect_pin);
		} while (user_pin != correct_pin);
						
		
		/*Go in waiting state. Will modify in later labs*/
		while(1);
  }
