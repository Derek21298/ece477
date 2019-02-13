#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	
	int input = atoi(argv[1]);
	int i;	
	int mask = 0b00000001;	

	if(argc < 2) {
		printf("Invalid use of program!\n");
		printf("Correct use: ./lab2 *integer*\n");
		return 0;
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

	
	printf("TURNING ON LEDS\n");

	//input = input & ~mask;

	for(i = 0; i < 8; i++) {
		digitalWrite(i, LOW);
	}

	printf("%x\n", input);

//	digitalWrite(0,HIGH);

	for(i = 0; i < 8; i++) {

		if((input & mask) == mask) {
			digitalWrite(i, HIGH);
		}
		
		mask =  mask << 1;		

	}

	return 0;

}


