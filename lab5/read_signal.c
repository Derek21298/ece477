


#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

#define HIGH 1
#define LOW 0

void set_up_input(void);

int main(void) {

	int input;
	unsigned int time_high = 0;
	unsigned int time_low = 0;
	double period;
	double frequency;
	unsigned int time1, time2;
	int count;
	int led_position = 1;
	
	set_up_input();

	// Turn the first LED on
	digitalWrite(0, HIGH);

	while(1) {

		input = digitalRead(25);
	
		if(input == HIGH){
			time1 = micros();
			count++;
			// If 5 periods have passed
			if((count % 5) == 0) {
				// rotate LED to next position
				// Position 0 case
				if(led_position == 0){
				
					digitalWrite(0,HIGH);
					digitalWrite(7, LOW);
					led_position++;
				}
				// Position 1-7 case
				else {

					digitalWrite(led_position,HIGH);
					digitalWrite(led_position - 1, LOW);
					led_position++;
				
					// Dont let led_position be above 8	
					if(led_position == 8) {
						led_position = 0;
					}
				}		
			}
	
			while(input == HIGH) {
				input = digitalRead(25);
			}
			time2 = micros();

			time_high = time2 - time1;
		}

		if(input == LOW){

			// Start timer
			time1 = micros();

			while(input == LOW) {
				input = digitalRead(25);
			}
			// stop timer
			time2 = micros();

			time_low = time2 - time1;

		}
		
		period = (time_high + time_low) * 1E-6;
		frequency = 1 / period;
		printf("Time High: %uus\tTime Low: %uus\tPeriod: %fus\tFrequency: %fHz\n", time_high, time_low, period * 1E6, frequency);	

	}

}

void set_up_input(void) {

	int i;

	// Initialize Wiring Pi
	wiringPiSetup();

	for(i = 0; i < 8; i++) {
		pinMode(i,OUTPUT);
		digitalWrite(i,LOW);
	}


	// Initialize GPIO 25 as an input
	pinMode(25, INPUT);

	// Set the pull down resistor on GPIO 25
	pullUpDnControl(25, PUD_DOWN);
	
}
