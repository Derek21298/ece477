/*
 *   ECE 477 Lab 4
 *   Authors: Alex Barnett, Derek Haas, Dustin Knight
 *   Date: 3/1/2019
 */

/*
 *   File: lab4_rotate.c
 *   Functions: 	
 *		set_up_pins
 *		moving_forward
 *		moving_backward
 */

/*
 *   Function Descriptions:
 *
 *   	set_up_pins
 *	   Initializes GPIO pins 0 through 7 using a for loop
 *
 *	moving_forward
 *   	   Flash LEDs from GPIO0 to GPIO7 with a time_delay delay between each iteration
 *
 *	moving_backward	
 *	   Flash LEDs from GPIO7 to GPIO0 with a time_delay delay between each iteration
 *
 */	

/*
 *   Main function:
 *      Inputs two arguments from the command line: time_delay and direction of blinking. The GPIO
 *      pins 0 through 7 are initialized as outputs and set low (just to be sure). Within a while loop
 *      the LEDs are either iterated from GPIO0-to-GPIO7 or GPIO7-to-GPIO0 depending on the direction 
 *      and switch at an interval determined by time_delay. This program runs parallel with the 
 *      lab4_main code.
 */


#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>


#define PRESSED 1
#define RELEASED 0


void set_up_pins(void);
void moving_forward(int time_delay);
void moving_backward(int time_delay);

int main(int argc, char** argv) {

	/* Ensure at least two there is at least two input arguments */
	if(argc < 2) {
		printf("Invalid Use Of Program!\n");
		return 0;
	}

	/* Initialize variables */
	int time_delay = atoi(argv[1]);  // Delay time between LED switches
	int direction = atoi(argv[2]);	 // Direction LEDs blink (left-to-right or right-to-left)
	int i;

	/* Initialize GPIO pins 0 through 7 as output */
	set_up_pins();

	/* Turn all LEDs off */
	for(i = 0; i < 8; i++) {
		digitalWrite(i,LOW);
	}

	/* Begin infinite while loop to rotate pins*/
	while(1) {

		/* Iterate LEDs from GPIO0 to GPIO7 */
		if(direction == 1) {
			moving_forward(time_delay);
		}
		
		/* Iterate LEDs from GPIO7 to GPIO0 */
		if(direction == 2) {
			moving_backward(time_delay);
		}
	}
	/* End while loop */

}
void set_up_pins(void) {
	int i;

	/* Initialize Wiring Pi */
	wiringPiSetup();
	
	/* Initialize GPIO pins 0 through 7 as OUTPUT */
	for(i = 0; i < 8; i++) {	
		pinMode(i, OUTPUT);
	}
}


void moving_forward(int time_delay) {
	int i;
	
	/* Ensure GPIO7 is pulled low */
	digitalWrite(7,LOW);


	/* Iterate from GPIO0 through to GPIO7 */
	for(i = 0; i < 8; i++) {
			
		/* No need to set previous GPIO pin low at start */
		if(i==0) {
			digitalWrite(i,HIGH);
			continue;
		}
	
		/* Delay for time_delay time */
		delay(time_delay);

		/* Turn previous LED off as the next one is turned on */
		digitalWrite(i-1, LOW);
		digitalWrite(i, HIGH);
	}
}

void moving_backward(int time_delay) {
	int i;

	/* Ensure GPIO0 is pulled low */
	digitalWrite(0,LOW);

	/* Iterate from GPIO7 through to GPIO0 */
	for(i = 7; i >= 0; i--) {
			
		/* No need to set previous GPIO pin low at start */
		if(i==7) {
			digitalWrite(i,HIGH);
			continue;
		}
	
		/* Delay for time_delay time */
		delay(time_delay);

		/* Turn previous LED off as the next one is turned on */
		digitalWrite(i+1, LOW);
		digitalWrite(i, HIGH);
	}
}
