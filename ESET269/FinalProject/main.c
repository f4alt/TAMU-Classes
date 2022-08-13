#include "msp.h"
#include <stdio.h>
#include <string.h>

/* Delay in ms using SysTick
*/
void delay(int ms) {
	SysTick->LOAD = ((double)ms/1000.0 * 3000000) -1;		// convert ms to # of counts
	SysTick->CTRL |= 0x01;															// enable
	while((SysTick->CTRL & 0x10000) == 0) {
		// wait
	}
	SysTick->CTRL &= ~0x01;															// disable
}

/* prints string to console using UART transfer buffer
*/
void UPrint(char* string) {	
	int i = 0;
	while (i < strlen(string)) {
		EUSCI_A0->TXBUF = string[i];
		while ((EUSCI_A0->IFG & 0x02) == 0) {
			// wait for buffer
		}
		i++;
	}
}

/* UART string input returns user input character
done like this to only trigger on enter key and looking back
I realize I could've just checked the buffer for the enter key
but I'm too invested to turn back now */
char URecChar(void) {
	int i = 0;																					// index
	char x[2];																					// response
	while(1){
		if ((EUSCI_A0 ->IFG & 1) == 1) {
			x[i] = EUSCI_A0->RXBUF;													// assign input at position i to array to create string
			EUSCI_A0->TXBUF = x[i];													// echo typed character for user
			while ((EUSCI_A0->IFG & 0x02) == 0) {
				// wait for buffer
			}
			if(x[i] == '\r') {															// check for enter key and convert to string terminal char
				x[i] = '\0';
				break;
			} else {
				if (i == 9) {																	// check that input is not longer than allocated size - 1
					x[i] = '\0';																// fill last char with string terminal char
					break;
				} else {
					i++;
				}
			}
		}
		else {
			// wait for user input
		}
	}
	
	UPrint("\n\r");																			// formatting
		
	return x[0];
}

/* converts char 1-9 to int
not sure if we could use atoi so i built a dirty converter 
for int 0-9 */
int strToInt(char charInt) {
	switch(charInt) {
		case('0'):
			return 0;
		case('1'):
			return 1;
		case('2'):
			return 2;
		case('3'):
			return 3;
		case('4'):
			return 4;
		case('5'):
			return 5;
		case('6'):
			return 6;
		case('7'):
			return 7;
		case('8'):
			return 8;
		case('9'):
			return 9;
		default:
			UPrint("Invalid Int\n\r");
			return -1;
	}
}

/* initializes UART communication
*/
void UARTInit(void) {
	EUSCI_A0->CTLW0 |= 0x01;														// put in reset state
	EUSCI_A0->MCTLW = 0;																// % error on baud rate
	EUSCI_A0->CTLW0 |= 0x80;														// 1 stop bit, no parity, SMCLK, 8-bit data
	EUSCI_A0->BRW = 0x4E;															 	// baud rate
	P1->SEL0 |= 0x0C;
	P1->SEL1 &= ~0x0C;
	EUSCI_A0->CTLW0 &= ~0x01;														// take out of reset state
}

/* initialize ADC for temperature reading
*/
void ADCInit(void) {
	//Ref_A settings
	REF_A ->CTL0 &= ~0x8; 															//enable temp sensor
	REF_A ->CTL0 |= 0x30; 															//set ref voltage
	REF_A ->CTL0 &= ~0x01; 															//enable ref voltage
	
	//do ADC stuff
	ADC14 ->CTL0 |= 0x10; 															//turn on the ADC
	ADC14 ->CTL0 &= ~0x02; 															//disable ADC
	ADC14 ->CTL0 |=0x4180700; 													//no prescale, mclk, 192 SHT
	ADC14 ->CTL1 &= ~0x1F0000; 													//configure memory register 0
	ADC14 ->CTL1 |= 0x800000; 													//route temp sense
	ADC14 ->MCTL[0] |= 0x100; 													//vref pos int buffer
	ADC14 ->MCTL[0] |= 22; 															//channel 22
	ADC14 ->CTL0 |=0x02; 																//enable adc
	
	return;
}

/* initializes, LED, buttons, SysTick
*/
void hardwareInit() {
	/* setup
	   PORT1.0 is red LED, PORT1.1 is button S1, PORT1.4 is button S2
	   PORT2.0,1,2 is RGB LED (R,G,B) */
	
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
	
	//SysTick config
	SysTick->CTRL |= 0x04;															// system clk = 1, IE = 0, Enable = 0;
}

/* returns ADC temperature
*/
float tempRead(void) {
	float temp; //temperature variable
	uint32_t cal30 = TLV ->ADC14_REF2P5V_TS30C; //calibration constant
	uint32_t cal85 = TLV ->ADC14_REF2P5V_TS85C; //calibration constant
	float calDiff = cal85 - cal30; //calibration difference
	ADC14 ->CTL0 |= 0x01; //start conversion
	while((ADC14 ->IFGR0) ==0){
		//wait for conversion
	}
	temp = ADC14 ->MEM[0]; //assign ADC value
	temp = (temp - cal30) * 55; //math for temperature per manual
	temp = (temp/calDiff) + 30; //math for temperature per manual
	
	return temp; //return temperature in degrees C
}

/* handles menu option '1' for rgb color 
toggle time and blink amount */
void rgbControl(void) {
	UPrint("Enter Combination of RGB (1-7):");
	int rgbInt = strToInt(URecChar());
	// handle invalid input
	if (rgbInt == 0 || rgbInt > 7) {
		UPrint("Invalid option, try again\n\r");
		rgbControl();
		return;
	}
	
	UPrint("Enter Toggle Time:");
	int togTime = strToInt(URecChar());
	UPrint("Enter Number of Blinks:");
	int blinks = strToInt(URecChar());

	UPrint("Blinking LED...\n\r");
	P2->OUT &= ~0x07;																		// turn off rgb LED
	for (int i = 0; i < (blinks * 2); i++) {						// multiply by two to account for on / off xor cycle
		P2->OUT ^= rgbInt;		
		delay(togTime * 1000);
	}
	P2->OUT &= ~0x07;																		// turn off rgb LED
	
	UPrint("Done\n\r");
}

/* Displays how many buttons are currently pressed 
*/
void buttonCheck(void) {
	// check button states
	if ((P1->IN & 0x12) == 0) {											// if s1 + s2 pressed
		UPrint("Button 1 and 2 pressed.\n\r");	
	} else if ((P1->IN & 0x02) == 0) { 							// if S1 is pressed
		UPrint("Button 1 pressed.\n\r");																			
	} else if ((P1->IN & 0x10) == 0) { 							// if only s2 is pressed
		UPrint("Button 2 pressed.\n\r");	
	} else {
		UPrint("No Button pressed.\n\r");
	}
}

/* Handles menu option '3'
Takes 1-5 temperature readings */
void tempReading(void) {
	float degC;
	char readString[30];
	UPrint("Enter Number of Temperature Reading (1-5):");
	int readingAmt = strToInt(URecChar());
	
	// handle invalid input
	if (readingAmt == 0 || readingAmt > 5) {
		UPrint("Invalid Amount, try again\n\r");
		tempReading();
		return;
	}
	
	for (int i = 0; i < readingAmt; i++) {
		degC = tempRead();
		sprintf(readString, "Reading %d: %.2f C & %.2f F\n\r",i+1, degC, (degC * 9 / 5) + 32);
		UPrint(readString);
		delay(1000);
	}
}
	

/* prompts user menu and calls corrisponding function depending 
on input */
void userMenu(void) {
	UPrint("\n\r1. RGB Control\n\r2. Digital Input\n\r3. Temperature Reading\n\r");
	char userOpt = URecChar();
	switch(userOpt) {
		case('1'):
			rgbControl();
			break;
		case('2'):
			buttonCheck();
			break;
		case('3'):
			tempReading();
			break;
		default:
			UPrint("Unknown Option, try again\n\r");
	}
}

int main(void) {
	ADCInit();
	UARTInit();
	hardwareInit();

	// welcome message
	UPrint("MSP432 Menu\n\r");
	
	while(1) {
		// menu input and logic is handled within
		userMenu();
	}
}
