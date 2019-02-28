/*
*	ECE 477 Lab 4
*	Authors: Alex Barnett, Derek Haas, Dustin Knight
*	Date: 3/1/2019
*	File: lab4_rotate.c
*	Function: 	Iterate through 8 LEDs (GPIO0 through GPIO7) from left-to-right
*			or right-to-left
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

	if(argc < 2) {
		printf("Invalid Use Of Program!\n");
		return 0;
	}

	int time_delay = atoi(argv[1]);
	int direction = atoi(argv[2]);	
	int i;

	set_up_pins();

	// Turn all LEDs off
	for(i = 0; i < 8; i++) {
		digitalWrite(i,LOW);
	}

	while(1) {
		if(direction == 1) {
			moving_forward(time_delay);
		}
		if(direction == 2) {
			moving_backward(time_delay);
		}
	}

}
void set_up_pins(void) {
	int i;

	wiringPiSetup();
	
	for(i = 0; i < 8; i++) {	
		pinMode(i, OUTPUT);
	}
}


void moving_forward(int time_delay) {
	int i;
	
	digitalWrite(7,LOW);

	for(i = 0; i < 8; i++) {
			
		if(i==0) {
			digitalWrite(i,HIGH);
			continue;
		}
	
		delay(time_delay);

		digitalWrite(i-1, LOW);
		digitalWrite(i, HIGH);
	}
}

void moving_backward(int time_delay) {
	int i;

	digitalWrite(0,LOW);

	for(i = 7; i >= 0; i--) {
			
		if(i==7) {
			digitalWrite(i,HIGH);
			continue;
		}
	
		delay(time_delay);

		digitalWrite(i+1, LOW);
		digitalWrite(i, HIGH);
	}
}
