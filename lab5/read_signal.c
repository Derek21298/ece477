


#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

#define HIGH 1
#define LOW 0

void set_up_pins(void);

int main(void) {

	int input;
	unsigned int time_high = 0;
	unsigned int time_low = 0;
	double period;
	double frequency;
	unsigned int time1, time2;
	int count;
	int led_position = 1;
	
	// Initialize the GPIO pins
	set_up_pins();

	// Turn the first LED on
	digitalWrite(0, HIGH);

	while(1) {
		
		// Read the input at GPIO 25
		input = digitalRead(25);
	
		// If the line is high, the PWM signal is high
		if(input == HIGH){
			// Record the time of the rising edge
			time1 = micros();
			// Increment the count
			count++;
			// If 5 rising edges have passed
			if((count % 5) == 0) {
				// rotate LED to next position
				// Position 0 case
				if(led_position == 0){
					
					// For the LED0, turn on 0 and turn off 7
					digitalWrite(0,HIGH);
					digitalWrite(7, LOW);
					// Increment the position
					led_position++;
				}
				
				// Position 1-7 case
				else {

					// Turn on the current led position
					digitalWrite(led_position,HIGH);
					// Turn off the position before it
					digitalWrite(led_position - 1, LOW);
					// Move the position forward
					led_position++;
				
					// Dont let led_position be above 8	
					if(led_position == 8) {
						led_position = 0;
					}
				}		
			}
	
			// Wait until the PWM signal goes low
			while(input == HIGH) {
				input = digitalRead(25);
			}
			// Record the time of the falling edge
			time2 = micros();

			// Time high is from rising edge to falling edge
			time_high = time2 - time1;
		}

		// If the PWM signal is low
		if(input == LOW){

			// Get the time of the falling edge
			time1 = micros();

			// Wait until the PWM signal goes high
			while(input == LOW) {
				input = digitalRead(25);
			}
			
			// Record the time of the rising edge
			time2 = micros();
			// Time low is from falling edge to rising edge
			time_low = time2 - time1;

		}
		// The total period is time high + time low
		period = (time_high + time_low) * 1E-6;
		frequency = 1 / period;
		printf("Time High: %uus\tTime Low: %uus\tPeriod: %fus\tFrequency: %fHz\n", time_high, time_low, period * 1E6, frequency);	

	}

}

void set_up_pins(void) {

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
