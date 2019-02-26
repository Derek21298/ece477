#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PRESSED 1
#define RELEASED 0

int main(int argc, char** argv) {

	int i;
	int button_a, button_b;
	int time_delay = 1024;
	char buffer[256];	
	char sys_buffer[256];

	pinMode(18, INPUT);
	pinMode(20, INPUT);

	pullUpDnControl(18, PUD_UP);
	pullUpDnControl(20, PUD_UP);

	system("./lab4_rotate 1024");

	while(1){

		button_a = digitalRead(18);
		button_b = digitalRead(20);

		if((button_a == PRESSED) && (button_b == RELEASED)) {
			
			// Make sure the button has been pressed for 50 us
			delay(50);
			if(button_a == PRESSED) {
				printf("BUTTON A IS PRESSED\n");
				
				// Dont let time-delay be less than 32
				if(time_delay > 32) {
					time_delay /= 2;
				}
			
				printf("Time delay is %d us\n", time_delay);
			
				// String Manipulation
				snprintf(buffer, 10, "%d", time_delay);
				strcpy(sys_buffer, "./lab4_rotate ");
				strcat(sys_buffer, buffer);
			
				// Kill the previous process and start a new one
				system("pkill lab4_rotate");
				system(sys_buffer);
			}
			
			// Wait until the button is relased
			while(button_a == RELEASED);
			printf("BUTTON A IS RELEASED\n");
		}

		if((button_b == PRESSED) && (button_a == RELEASED) ) {
			
			// Make sure the button has been pressed for 50 us
			delay(50);
			if(button_b == PRESSED) {
				
				printf("BUTTON B IS PRESSED\n");
				// Dont let time-delay be greater than 32
				if(time_delay < 1024) {
					time_delay *= 2;
				}
					
				printf("Time delay is %d us\n", time_delay);

				// String Manipulation
				snprintf(buffer, 10, "%d", time_delay);
				strcpy(sys_buffer, "./lab4_rotate ");
				strcat(sys_buffer, buffer);
			
				// Kill the previous process and start a new one
				system("pkill lab4_rotate");
				system(sys_buffer);
			}
			
			// Wait until the button is relased
			while(button_b == RELEASED);
			printf("BUTTON B IS RELEASED\n");
		}

				
		if((button_b == PRESSED) && (button_a == PRESSED) ) {
			
			// Make sure the button has been pressed for 50 us
			delay(50);
			if((button_b == PRESSED) && (button_a == PRESSED)) {
			
				// Kill the previous process
				system("pkill lab4_rotate");
				return 0;
			}	
		}
	}

}
