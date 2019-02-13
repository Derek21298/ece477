#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int i;		

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

	return 0;

}


