#include "msp.h"

int main(void) {
	/* setup
	   PORT1.0 is red LED, PORT1.1 is button S1, PORT1.4 is button S2
	   PORT2.012 is RGB LED (R,G,B) */
	
	P1->SEL0 &= ~0x13;																	// config P1 pin 0,1,4 as I/O => xxx0xx00
	P1->SEL1 &= ~0x13;
	P1->DIR |= 0x01;																		// set direction for red LED as output => xxxxxxx1
	P1->DIR &= ~0x12;																		// set direction for S1, S2 as input => xxx0xx0x
	P1->REN |= 0x12;																		// enable P1 pin 1,4 internal resistor => xxx1xx1x
	P1->OUT |= 0x12;																		// config P1 pin 1,4 as pull up resistor => xxx1xx1x
	P1->OUT &= ~0x01;																		// turn off red LED
	
	P2->SEL0 &= ~7;																			// config P2 pin 0,1,2 as I/O => xxxxx000
	P2->SEL1 &= ~7;			
	P2->DIR |= 7;																				// set direction as output for rgb LED
	P2->OUT &= ~0x07;																		// turn off rgb LED

	while(1) {
		// check button states
		if ((P1->IN & 0x02) == 0) { 											// if S1 is pressed
			P1->OUT |= 0x01;																			
		} if ((P1->IN & 0x12) == 0) {											// if s1 + s2 pressed
			P2->OUT |= 0x05;
		} else if ((P1->IN & 0x10) == 0) { 								// if only s2 is pressed
			P2->OUT |= 0x02;
		} 
		
		P1->OUT &= ~0x01;
		P2->OUT &= ~0x07;
	}
}
