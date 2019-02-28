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
 *	   
 *
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
struct button_properties button_check(int button_a, int button_b, int button_c, struct button_properties);

/* Holding the properties of button in struct to avoid global variable */
struct button_properties {
	int time_delay;
	int direction;
};	


int main(int argc, char** argv) {

	/* Initialize Variables */
	int button_a, button_b, button_c;
	struct button_properties s;
	s.time_delay = 1024;	   // Delay is initially 1024 ms
	s.direction = 1;	   // Direction is initially from GPIO0 to GPIO7
	

	/* Initialize GPIO pins 0 through 7 as output */
	set_up_pins();

	/* Close lab4_rotate if open and start rotating LEDs */
	 /********IS THIS RIGHT***********/
	system("pkill lab4_rotate");
	system("./lab4_rotate 1024 1&");
	

	/* Begin infinite loop to check */
	while(1){

		/* Button a decrements time_delay */
		button_a = digitalRead(25);	   // GPIO25

		/* Button b increments time_delay */
		button_b = digitalRead(27); 	   // GPIO27

		/* Button c resets program */
		button_c = digitalRead(28); 	   // GPIO28		

		/* Print value of buttons (1 or 0) */
		printf("BUTTON A VALUE: %d\n", button_a);	
		printf("BUTTON B VALUE: %d\n", button_b);	
		printf("BUTTON C VALUE: %d\n", button_c);

		/* Check buttons and save time_delay and direction to struct s */
		s = button_check(button_a, button_b, button_c, s);
	}

}

void set_up_pins(void) {

	/* Initialize Wiring Pi */
	wiringPiSetup();

	/* Initialize GPIO pins as input */
	pinMode(25, INPUT);
	pinMode(27, INPUT);
	pinMode(28, INPUT);

	/* Initializes GPIO pins as pull-down */
	pullUpDnControl(25, PUD_DOWN);
	pullUpDnControl(27, PUD_DOWN);
	pullUpDnControl(28, PUD_DOWN);
}

struct button_properties button_check(int button_a, int button_b, int button_c, struct button_properties s) {

	char buffer[256];
	char sys_buffer[256];

	if((button_a == PRESSED) && (button_b == RELEASED) && (button_c == RELEASED)) {			
		// Make sure the button has been pressed for 50 us
		delay(150);
		if(button_a == PRESSED) {
			printf("BUTTON A IS PRESSED\n");
			
			if((s.time_delay == 32) && (s.direction == 1)) {
				s.direction = 2;
			}
			else if((s.time_delay == 32) && (s.direction == 2)) {
				s.direction = 1;
			}
			// Dont let time-delay be less than 32
			if(s.time_delay > 32) {
				s.time_delay /= 2;
			}
		
			printf("Time delay is %d us\n", s.time_delay);
		
			snprintf(buffer, 10, "%d", s.time_delay);
			strcpy(sys_buffer, "./lab4_rotate ");
			strcat(sys_buffer, buffer);
			strcat(sys_buffer," ");
			snprintf(buffer, 10, "%d", s.direction);
			strcat(sys_buffer, buffer);
			strcat(sys_buffer, "&");
			printf("I made it!\n");
		
			// Kill the previous process and start a new one
			system("pkill lab4_rotate");
			system(sys_buffer);
		}
			
		// Wait until the button is relased
		printf("Direction is = %d\n", s.direction);
		while(button_a == PRESSED) {
			button_a = digitalRead(25);
			button_b = digitalRead(27);
			if(button_b == PRESSED) {
				system("pkill lab4_rotate -f");
				system("pkill lab4_main -f");
			}
		}
		printf("BUTTON A IS RELEASED\n");
	}

	if((button_b == PRESSED) && (button_a == RELEASED) && (button_c == RELEASED)) {
		
		// Make sure the button has been pressed for 50 us
		delay(150);
		if(button_b == PRESSED) {
			
			if((s.time_delay == 1024) && (s.direction == 1)) {
				s.direction = 2;
			}
			else if((s.time_delay == 1024) && (s.direction == 2)) {
				s.direction = 1;
			}
			printf("BUTTON B IS PRESSED\n");
			// Dont let time-delay be greater than 32
			if(s.time_delay < 1024) {
				s.time_delay *= 2;
			}
					
			printf("Time delay is %d us\n", s.time_delay);
			
			snprintf(buffer, 10, "%d", s.time_delay);
			strcpy(sys_buffer, "./lab4_rotate ");
			strcat(sys_buffer, buffer);
			strcat(sys_buffer," ");
			snprintf(buffer, 10, "%d", s.direction);
			strcat(sys_buffer, buffer);
			strcat(sys_buffer, "&");
			printf("I made it!\n");
		
			// Kill the previous process and start a new one
			system("pkill lab4_rotate -f");
			system(sys_buffer);
		}
			
		// Wait until the button is relased
		while(button_b == PRESSED) {
			button_b = digitalRead(27);
			button_a = digitalRead(25);
			if(button_a == PRESSED) {
				system("pkill lab4_rotate -f");
				system("pkill lab4_main -f");
			}
		}
		printf("BUTTON B IS RELEASED\n");
	}
		
	if((button_c == PRESSED) && (button_a == RELEASED) && (button_b == RELEASED)) {
					
		// Make sure the button has been pressed for 50 us
		delay(150);
		if(button_c == PRESSED) {
			s.time_delay = 1024;
			s.direction = 1;
					
			printf("Time delay is %d us\n", s.time_delay);
			
			snprintf(buffer, 10, "%d", s.time_delay);
			strcpy(sys_buffer, "./lab4_rotate ");
			strcat(sys_buffer, buffer);
			strcat(sys_buffer," ");
			snprintf(buffer, 10, "%d", s.direction);
			strcat(sys_buffer, buffer);
			strcat(sys_buffer, "&");
			printf("I made it!\n");
		
			// Kill the previous process and start a new one
			system("pkill lab4_rotate -f");
			system(sys_buffer);
		}

		// Wait until the button is relased
		while(button_c == PRESSED);
		printf("BUTTON C IS RELEASED\n");
	}
	return s;
}
