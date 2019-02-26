#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>


#define PRESSED 1
#define RELEASED 0

int main(int argc, char** argv) {

	int i;

	if(argc < 2) {
		printf("Invalid Use Of Program!\n");
		return 0;
	}

	int time_delay = atoi(argv[1]);

	wiringPiSetup();

	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);

	pinMode(15, INPUT);
	pinMode(16, INPUT);

	pullUpDnControl(15, PUD_UP);
	pullUpDnControl(16, PUD_UP);


	// Turn all LEDs off
	for(i = 0; i < 8; i++) {
		digitalWrite(i,LOW);
	}


	while(1) {
	
		for(i = 0; i < 8; i++) {
			
			if(i==0) {
				digitalWrite(i,HIGH);
				continue;
			}
	
			delay(time_delay);

			digitalWrite(i-1, LOW);
			digitalWrite(i, HIGH);
		}

		
		for(i = 7; i >= 0; i--) {
			
			if(i==0) {
				digitalWrite(i,HIGH);
				continue;
			}
	
			delay(time_delay);

			digitalWrite(i+1, LOW);
			digitalWrite(i, HIGH);
		}
	}

}
