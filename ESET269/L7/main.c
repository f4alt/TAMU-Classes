#include "msp.h"

// delay in ms with 3MHz clock
void delayMs(int n) {
	int i, j;
	for (j = 0; j < n; j++) {
		for (i = 750; i > 0; i--) {
		}
	}
}

int main(void) {
	// setup
	// PORT1 is RED LED
	// PORT2 is RGB LED
	P1->SEL0 &= ~1;			// config P1 pin x as I/O
	P1->SEL1 &= ~1;
	P1->DIR |= 1;				// set direction as output
	P1->OUT &= 0;				// turn off
	
	P2->SEL0 &= ~7;			// config P1 pin xxx as I/O
	P2->SEL1 &= ~7;			
	P2->DIR |= 7;				// set direction as output
	
	// loop through color combinations twice for RGB LED
	for (int j = 0; j < 2; j++) {
		for (int i = 1; i <= 7; i++) {
				P2->OUT = i;		
				delayMs(300);
		}
	}
	
	P2->OUT = 4;				// set P2 LED to blue
	while(1) {
		// infinitely toggle red and blue
		P1->OUT ^= 1;
		P2->OUT ^= 4;
		delayMs(500);
	}
}
