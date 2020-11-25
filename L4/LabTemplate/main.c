/* 
* Lab Partner Names:
* Lab #:
*/

/*Include files */
#include <stdio.h>
#include <stdlib.h>

/*Function Declarations*/
void OutputInit(void); 

int main(void)
	{
    /*Setup Launchpad for Printf & Scanf*/
		OutputInit(); 
		
		/* **************************
							TASK 1
			 ************************** */
		printf("TASK 1\n\r");
		
		int patient_data[3][6] = {{48,55,52,53,50,51},										// ESV
															{118,120,119,122,124,121},							// EDV
															{62,80,65,70,66,64}};										// HR
		char patient_letter = 'A';
															
		for(int i = 0; i < 6; i++) {
			int SV = patient_data[1][i] - patient_data[0][i];
			float CO = ((float)SV * patient_data[2][i]) / 1000;
			
			printf("Patient %c: SV %d mL. CO %.2f L/min\n\r",patient_letter,SV,CO);
			patient_letter++;
		}
		
		
		/* **************************
							TASK 2
			 ************************** */
		printf("\n\n\rTASK 2\n\r");
		
		// VARIABLES
		int grades[3][7] = {{80,75,99,78,100,55,69},
												{50,68,100,95,85,73,80},
												{65,50,88,100,86,76,99}};
		float section_total[3];
		int letter_grade_count[5];
		float class_total = 0;
		char letter_grade[] = {'A', 'B', 'C', 'D', 'F'};
		int sections[3] = {101, 102, 103};
										
		// SORT ARRAY INTO LETTER GRADES AND KEEP RUNNING TOTAL FOR SECTION AND CLASS
		for (int section = 0; section < 3; section++) {
			section_total[section] = 0;																			// reset section total
			for (int individual = 0; individual < 7; individual++) {
				section_total[section] += grades[section][individual];				// keep running total for section
				class_total += grades[section][individual];										// keep running total for entire class
				
				int curr = grades[section][individual] / 10;									// simplify grade into one digit value to sort letter grades
				switch (curr) {																								// sort letter grades into 10&9, 8, 7, 6, rest 
					case 10:
					case 9:
						letter_grade_count[0]++;
						break;
					case 8:
						letter_grade_count[1]++;
						break;
					case 7:
						letter_grade_count[2]++;
						break;
					case 6:
						letter_grade_count[3]++;
						break;
					default:
						letter_grade_count[4]++;
						break;
				}
			}
		}
		
		// PRINT OUT FINDINGS
		for (int i = 0; i < 5; i++) {																			// number of letter grades
			printf("The number of %cs:%d\n\r",letter_grade[i],
			letter_grade_count[i]);
		}
		printf("\n\r");
		for (int i = 0; i < 3; i++) {																			// section averages
			printf("Section %d average is %.2f\n\r",sections[i],
			(float)section_total[i]/7);
		}
		printf("The class average is %.2f",class_total / 21);							// class average
		
		/*Go in waiting state. Will modify in later labs*/
		while(1);
  }
