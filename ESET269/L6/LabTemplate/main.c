/* 
* Lab Partner Names:
* Lab #:
*/

/*Include files */
#include <stdio.h>
#include <stdlib.h>
#include "lasers.h"

/*Function Declarations*/
void OutputInit(void); 

int main(void)
	{
    /*Setup Launchpad for Printf & Scanf*/
		OutputInit(); 
		
		/* Place application code here */
		// Create array of lasers and populate with default values
		struct laser default_table[4];
		populateLasers(default_table);
		
		// loop through lasers array and check replacement criteria
		for (int i = 0; i < 4; i++) {
			checkUpgrade(default_table[i]);
		}
		
		/*Go in waiting state. Will modify in later labs*/
		while(1);
  }
