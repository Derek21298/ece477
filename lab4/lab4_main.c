#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PRESSED 1
#define RELEASED 0

void set_up_pins(void);
struct button_properties button_check(int button_a, int button_b, int button_c, struct button_properties);

// Holding the properties of button in struct to avoid global variable
struct button_properties {
	int time_delay;
	int direction;
};	


int main(int argc, char** argv) {

	int button_a, button_b, button_c;
	struct button_properties s;
	s.time_delay = 1024;
	s.direction = 1;
	
	set_up_pins();

	system("pkill lab4_rotate");
	system("./lab4_rotate 1024&");

	while(1){

		button_a = digitalRead(25);
		button_b = digitalRead(27);
		button_c = digitalRead(28);		

		printf("BUTTON A VALUE: %d\n", button_a);	
		printf("BUTTON B VALUE: %d\n", button_b);	
		
		s = button_check(button_a, button_b, button_c, s);
		
	}

}

void set_up_pins(void) {

	wiringPiSetup();
	pinMode(25, INPUT);
	pinMode(27, INPUT);

	pullUpDnControl(25, PUD_DOWN);
	pullUpDnControl(27, PUD_DOWN);
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
