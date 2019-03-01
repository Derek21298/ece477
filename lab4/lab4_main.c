/*
 *   ECE 477 Lab 4
 *   Authors: Alex Barnett, Derek Haas, Dustin Knight
 *   Date: 3/1/2019	
 */

/*
 *   File: lab4_main.c
 *   Functions:
 *		set_up_pins
 *		button_check
 */

/*	
 *   Function Descriptions:
 *
 *   	set_up_pins
 *   	   Initializes GPIO pins 25,27, and 28 as inputs and pull-down
 *
 *	button_check
 *	   Checks which button is pressed and changes the time_delay between LEDs and the direction
 *	   the LEDs rotate by writing to the command line. Outputs struct button_properties to save
 *	   time_delay and direction for the next input.
 */ 

/*
 *   Main function:
 *	In an infinite while loop, main reads the inputs from three buttons: GPIO25, GPIO27, 
 *	and GPIO28. These values are input to the button_check function to run lab4_rotate with
 *	the specified time_delay and direction as defined in the struct button_properties. 
 *	
 */


#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PRESSED 1
#define RELEASED 0

void set_up_pins(void);
struct button_properties button_check(int button_a, int button_b, struct button_properties);
int get_passcode(void);
int compare_arrays(int size, int a1[], int a2[]);

/* Holding the properties of button in struct to avoid global variable */
struct button_properties {
	int time_delay;
	int direction;
};	


int main(int argc, char** argv) {

	/* Initialize Variables */
	int button_a, button_b, i;
	struct button_properties s;
	s.time_delay = 1024;	   // Delay is initially 1024 ms
	s.direction = 1;	   // Direction is initially from GPIO0 to GPIO7
	int buffer[4];			// Buffer to keep the password	
	int passcode[4] = {1,2,2,1};	// The password (ABBA like the band) 
	int compare;		
	
	/* Initialize GPIO pins 25, 27, and 28 as pull-down input */
	set_up_pins();

	// Get the password
	while(1) {
		
		// Iterate through the 4 allowable inputs for the password
		for(i = 0; i < 4; i++) {
		
			// Ask for 4 inputs for the passcode and delay
			buffer[i] = get_passcode();
			delay(200);
		}
		// Compare the buffer array with the asctual password
		compare = compare_arrays(4, buffer, passcode);
		printf("COMPARE = %d\n", compare);
		// If the two match, move on into PART A
		if(compare) break;
	}		
		

	/* Close lab4_rotate if open and start rotating LEDs */
	system("pkill lab4_rotate");
	system("./lab4_rotate 1024 1&");
	

	/* Begin infinite loop to check */
	while(1){

		/* Button a decrements time_delay */
		button_a = digitalRead(25);	   // GPIO25

		/* Button b increments time_delay */
		button_b = digitalRead(27); 	   // GPIO27

		/* Print value of buttons (1 or 0) */
		printf("BUTTON A VALUE: %d\n", button_a);	
		printf("BUTTON B VALUE: %d\n", button_b);	

		/* Check buttons and save time_delay and direction to struct s */
		s = button_check(button_a, button_b, s);
	}

}

void set_up_pins(void) {

	/* Initialize Wiring Pi */
	wiringPiSetup();

	/* Initialize GPIO pins as input */
	pinMode(25, INPUT);
	pinMode(27, INPUT);

	/* Initializes GPIO pins as pull-down */
	pullUpDnControl(25, PUD_DOWN);
	pullUpDnControl(27, PUD_DOWN);
}

struct button_properties button_check(int button_a, int button_b, struct button_properties s) {

	char buffer[256];
	char sys_buffer[256];


	/* When only button a has been pressed */
	if((button_a == PRESSED) && (button_b == RELEASED)) {			
		/* Make sure the button has been pressed for at least 150 us */
		delay(150);
		button_a = digitalRead(25);
		/* Check if button is pressed */
		if(button_a == PRESSED) {

			printf("BUTTON A IS PRESSED\n");

			/* Change direction of LED flashing when time_delay is less than 32 */
			if((s.time_delay == 32) && (s.direction == 1)) {
				s.direction = 2;
			}
			else if((s.time_delay == 32) && (s.direction == 2)) {
				s.direction = 1;
			}
			/* Decrease time_delay if it is not yet 32 and button_a is pressed */
			if(s.time_delay > 32) {
				s.time_delay /= 2;
			}
		
			printf("Time delay is %d us\n", s.time_delay);
		
			/* Convert time_delay int to a string in buffer */
			snprintf(buffer, 10, "%d", s.time_delay);

			/* Write to the console to initiate lab4_rotate with new time_delay */
			strcpy(sys_buffer, "./lab4_rotate ");
			strcat(sys_buffer, buffer);
			strcat(sys_buffer," ");
			
			/* Convert direction int to a string in buffer */
			snprintf(buffer, 10, "%d", s.direction);

			/* Write to the console to initiate lab4_rotate with a new direction */
			strcat(sys_buffer, buffer);

			/* Run in the background with & */
			strcat(sys_buffer, "&");
			printf("I made it!\n");
		
			/* Kill the previous process */
			system("pkill lab4_rotate");

			/* Start the next process "./lab4_rotate time_delay direction" */
			system(sys_buffer);
		}
			
		/* Wait until the button is relased */
		printf("Direction is = %d\n", s.direction);
		
		/* Hold until button_a is released */
		while(button_a == PRESSED) {
			button_a = digitalRead(25);
			button_b = digitalRead(27);

			/* If button_a and button_b are pressed, kill the program */
			if(button_b == PRESSED) {
				system("pkill lab4_rotate -f");
				system("pkill lab4_main -f");
			}
		}
		printf("BUTTON A IS RELEASED\n");
	}

	/* When only button_b is pressed */
	if((button_b == PRESSED) && (button_a == RELEASED)) {
		
		/* Make sure the button has been pressed for 150 us and check if button is pressed */
		delay(150);
		button_b = digitalRead(25);
		if(button_b == PRESSED) {		
			
			
			/* Change direction of LED flashing when time_delay is less than 32 */
			if((s.time_delay == 1024) && (s.direction == 1)) {
				s.direction = 2;
			}
			else if((s.time_delay == 1024) && (s.direction == 2)) {
				s.direction = 1;
			}
			printf("BUTTON B IS PRESSED\n");
			
			/* Increase the time_delay if button_b is pressed and time_delay is not 1024 */
			if(s.time_delay < 1024) {
				s.time_delay *= 2;
			}
					
			printf("Time delay is %d us\n", s.time_delay);
		
			/* Convert time_delay int to a string in buffer */
			snprintf(buffer, 10, "%d", s.time_delay);

			/* Write to the console to initiate lab4_rotate with new time_delay */
			strcpy(sys_buffer, "./lab4_rotate ");
			strcat(sys_buffer, buffer);
			strcat(sys_buffer," ");
			
			/* Convert direction int to a string in buffer */
			snprintf(buffer, 10, "%d", s.direction);

			/* Write to the console to initiate lab4_rotate with a new direction */
			strcat(sys_buffer, buffer);

			/* Run in the background with & */
			strcat(sys_buffer, "&");
			printf("I made it!\n");
		
			/* Kill the previous process */
			system("pkill lab4_rotate");

			/* Start the next process "./lab4_rotate time_delay direction" */
			system(sys_buffer);
		}
			
		/* Wait until the button is relased */
		while(button_b == PRESSED) {
			button_b = digitalRead(27);
			button_a = digitalRead(25);

			/* If button_a is also pressed, kill the program */
			if(button_a == PRESSED) {
				system("pkill lab4_rotate -f");
				system("pkill lab4_main -f");
			}
		}
		printf("BUTTON B IS RELEASED\n");
	}
	return s;
}

// Function to get 1 input of the passcode
int get_passcode() {

	int button_a;	// Local variables for A and B
	int button_b;
	
	while(1) {
		// Read the GPIO pins
		button_a = digitalRead(25);	   // GPIO25
		button_b = digitalRead(27); 	   // GPIO27
		
		// If only A is pressed
		if((button_a == PRESSED) && (button_b == RELEASED)) {
		
			/* Make sure the button has been pressed for at least 150 us */
			delay(150);
			// Read the button again
			button_a = digitalRead(25);
			/* Check if button is pressed */
			if(button_a == PRESSED) {
				printf("BUTTON A IS PRESSED\n");
			}
			// Wait for the button to be released
			while(button_a == PRESSED) {
				button_a = digitalRead(25);
			}
			// Return a 1 for the password
			return 1;
		}

		// If only B is pressed
		if((button_b == PRESSED) && (button_a == RELEASED)) {
		
			/* Make sure the button has been pressed for at least 150 us */
			delay(150);
			// Read the button again
			button_b = digitalRead(27);
			/* Check if button is pressed */
			if(button_b == PRESSED) {
				printf("BUTTON B IS PRESSED\n");
			}
			// Wait for the button to be released
			while(button_b == PRESSED) {
				button_b = digitalRead(27);
			}
			// Return a 2 for the password
			return 2;
		}
	}
}

// Function to compare two arrays
int compare_arrays(int size, int a1[], int a2[]) {

	int i;
	
	// Iterate through the elements in the array
	for(i = 0; i < size; i++) {

		// If an element is not equal, the arrays are not equal
		if(a1[i] != a2[i]) {
			return 0;
		}
	}
	// Return 1 if true
	return 1;
}
		
