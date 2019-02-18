#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	
	if(argc < 2) {
		printf("Invalid use of program!\n");
		printf("Correct use: ./lab2 *integer*\n");
		return 0;
	}
	
	int input = atoi(argv[1]);
	int i;	
	int mask = 0b00000001;	

	if(strcmp(argv[1],"cool")) { 

		if((input == 0)	&& (*argv[1] != '0')){

			printf("Invalid use of program!\n");
			printf("Character entered.  Enter integer between 0-255\n");
			return 0;
		}
	}

	if(input > 0xff) { 
		printf("Invalid use of program!\n");
		printf("Please enter number 0-255\n");
		return 0;
	}

	// Setup Wiring Pi and set pins as outputs
	wiringPiSetup();
	pinMode (0, OUTPUT);
	pinMode (1, OUTPUT);
	pinMode (2, OUTPUT);
	pinMode (3, OUTPUT);
	pinMode (4, OUTPUT);
	pinMode (5, OUTPUT);
	pinMode (6, OUTPUT);
	pinMode (7, OUTPUT);

	if(!strcmp(argv[1],"cool")) {	

		for(i = 0; i < 8; i++) {
			digitalWrite(i,LOW);
		}

		while(1) {

			for(i = 0; i < 8; i++) {
	
				if(i == 0) {
					digitalWrite(i, HIGH);
					continue;
				}
			
				delay(200);
				digitalWrite(i-1,LOW);
				digitalWrite(i,HIGH);
			}

			for(i = 7; i >= 0; i--) {

				if(i == 7) {
					digitalWrite(i, HIGH);
					continue;
				}	
			
				delay(200);	
				digitalWrite(i+1,LOW);
				digitalWrite(i,HIGH);

			}	
				
		}

	}

	if(input > 0) {	
	//	printf("Turning on LEDs\n\n");
	}
	else {
	//	printf("Turning off LEDs\n");
	}

	for(i = 0; i < 8; i++) {
		digitalWrite(i,LOW);
	}

	for(i = 0; i < 8; i++) {
	
		if((input & mask) == mask) {
			digitalWrite(i, HIGH);
			//printf("Turning on LED %d\n", i);
		}
		
		mask = mask << 1;
			
	}	
	

	return 0;

}


