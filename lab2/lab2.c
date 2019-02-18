#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

	// Ensure user is entering proper command line argument
	if(argc < 2) {
		printf("Invalid use of program!\n");
		printf("Correct use: ./lab2 *integer*\n");
		return 0;
	}

	// Convert input from a string to integer
	// Initilialize variables
	int input = atoi(argv[1]);
	int i;
	int mask = 0b00000001;

	// If the input string arg[v] and "cool" are the same, skip loop (as strcmp() returns 0 for strings that are equal)
	if(strcmp(argv[1],"cool")) {

		// atoi() returns 0 for strings that are character letters AND for the character '0'
		// So, if input is a character and not the character '0', then a letter was input and an error is sent to the console
		if((input == 0)	&& (*argv[1] != '0')){

			printf("Invalid use of program!\n");
			printf("Character entered.  Enter integer between 0-255\n");
			return 0;
		}
	}

	// If the input exceeds 255
	if(input > 0xff) {
		printf("Invalid use of program!\n");
		printf("Please enter number 0-255\n");
		return 0;
	}

	// Setup Wiring Pi and set pins as outputs
	wiringPiSetup();
	// pinMode(GPIO_NUMBER,DIRECTION)
	// GPIO_NUMBER is the GPIO number that you are changing the direction of
	// DIRECTION can be either INPUT or OUTPUT
	pinMode (0, OUTPUT);
	pinMode (1, OUTPUT);
	pinMode (2, OUTPUT);
	pinMode (3, OUTPUT);
	pinMode (4, OUTPUT);
	pinMode (5, OUTPUT);
	pinMode (6, OUTPUT);
	pinMode (7, OUTPUT);

	// If input argument is "cool"
	if(!strcmp(argv[1],"cool")) {

		// Initialized all LEDs to be off
		for(i = 0; i < 8; i++) {
			// digitalWrite(GPIO_NUMBER,HIGH/LOW)
			// GPIO_NUMBER is the GPIO that is being written to
			// HIGH sets GPIO# to 3.3V
			// LOW sets GPIO# to 0V
			digitalWrite(i,LOW);

		}

		while(1) {

			// Blinking LEDs from GPIO0 to GPIO7
			for(i = 0; i < 8; i++) {

				// If at GPIO0 write high, but don't write previous LED low (as there is no previous LED)
				if(i == 0) {
					// set GPIO0 LED high
					digitalWrite(i, HIGH);
					// Go to next iteration of for-loop
					continue;
				}

				// Delay 200ms so LED switching is visible
				delay(200);

				// Turn previous LED off at the "same time"(as far as the human eye can see) as the next one is turned on
				digitalWrite(i-1,LOW);
				digitalWrite(i,HIGH);
			}

			// Blinking LEDs from GPIO7 to GPIO0
			for(i = 7; i >= 0; i--) {

				// If starting at GPIO7, don't write previous LED low
				if(i == 7) {
					digitalWrite(i, HIGH);
					continue;
				}

				delay(200);

				// Turn previous LED off at the "same time" as the next one is turned on
				digitalWrite(i+1,LOW);
				digitalWrite(i,HIGH);

			}

		}

	}

	// Indicate that LEDs are being turned on
	if(input > 0) {
		printf("Turning on LEDs\n\n");
	}
	// Indicate that LEDs are being turned off
	else {
		printf("Turning off LEDs\n");
	}

	// Turn off all LEDs to be off (to ensure that they are all off)
	for(i = 0; i < 8; i++) {
		digitalWrite(i,LOW);
	}

	// Iterate through GPIO0-GPIO7
	for(i = 0; i < 8; i++) {

		// Check if the 'ith' bit in input is a 1 or 0
		if((input & mask) == mask) {
			// Write GPIOi to 3.3V
			digitalWrite(i, HIGH);
			// Indicate LED is being turned on
			printf("Turning on LED %d\n", i);
		}

		// Shift mask
		mask = mask << 1;

	}


	return 0;

}


