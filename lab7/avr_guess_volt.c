#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define F_CPU 1000000UL
#include <util/delay.h>

// Variable declarations
int serial_putchar(char, FILE *);
int serial_getchar(FILE *);
static FILE serial_stream = FDEV_SETUP_STREAM(serial_putchar, serial_getchar, _FDEV_SETUP_RW);

void init_serial(void);
void do_high_low(void);
int read_integer(void);
int read_ADC(void);
void init_ADC(void);
void part_b(void);

int main(void) { 

	// Initialize UART for the AVR
	init_serial();

	// 2 second delay
  	_delay_ms(2000);
  
  	FILE *fp, *fpr;
  	fp=stdout;
	fpr=stdin;
	int input, ADC_output;
	float vref;

	// Initialize the ADC
	init_ADC();

	// Make all port b pins outputs (data direction register)
	DDRB = 0b11111111; 
	
	while(1) {

		// Reset the ADC output just incase...
		ADC_output = 0;
	
		input = read_integer();


		// Tell the user if LEDs are turning on or off
		if(input > 0) {
			fprintf(fp, "Turning on LEDs!\n");
		}
		else {
			fprintf(fp, "Turning off LEDs!\n");
		}

		
		PORTB = input; 	// Make output high source 

		// Read ADC from channel 0
		ADC_output = read_ADC();

		fprintf(fp, "ADC VALUE IS: %d\n", ADC_output);

		vref = (1.1 * 1024.0) / (float)ADC_output;

		fprintf(fp, "Power Supply: %f\n", vref);

		if(ADC_output < 330) {
	
			printf("ERROR POWER SUPPLY VOLATGE TOO HIGH!\n");

			part_b();
		}
		
	}

  	return 0;
}


void init_serial(void) {

	// Finding baud rate divider
	// f_clock/(16*(divider+1)) = baud rate
	// f_clock = 8 MHz
	// baud rate = 1200 bits per second
	// divider = 848 -> 0b0000001101010000;

	// Set baud rate to 1200 bits per second
   	UBRR0H=0b00000011; 
   	UBRR0L=0b01010000;

	// Enable U2X0 to double transmission speed
   	UCSR0A= 1<<U2X0;

	// Set parity mode to 8-bit "Enabled, Odd Parity"
	// Set stop bit to 2 bits
   	UCSR0C= (1<<USBS0)|(3<<UCSZ00);

	// Enable TX and RX
   	UCSR0B=(1<<RXEN0)|(1<<TXEN0);

	// Initialize stdin and stdout
   	stdin=&serial_stream;
   	stdout=&serial_stream;
}

void init_ADC(void) {

	// Set ADMUX register to use an external reference voltage for ADC source
	ADMUX = 0;
	ADMUX |= (1 << REFS0);
	
	// Sets the Single Ended Input channel to 1.1V (V_BG)
	ADMUX |= (1 << MUX3) | (1 << MUX2) | (1 << MUX1);
	
	// Enable ADC and set division factor as 64
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

int read_ADC(void) {
		
	// Start single conversion
	ADCSRA |= (1 << ADSC);

	// Wait for conversion to be complete
	while(!(ADCSRA & (1 << ADIF)));

	// Clear ADIF
	ADCSRA |= (1 << ADIF);

	fprintf(stdout, "ADCH %d \t ADCL %d\n", ADCH, ADCL);

	return ADC;
}	  

int read_integer(void) {

	FILE *fp, *fpr;
	int input;

	fp = stdout;
	fpr = stdin;

	
	// Receive a valid input
	while(1) {

		fprintf(fp, "Please enter an integer between 0 and 255: ");
		
		while(fscanf(fpr, "%d", &input) != 1) {
				fscanf(fpr, "%*s");
		}			

		fprintf(fp,"\nInput is: %d\n",input);

		if(input > 255) {
			fprintf(fp, "Entered value greater than 255!\n" );
		}
		else if(input < 0) {
			fprintf(fp, "Entered value less than 0!\n" );	
		}
		else {
			return input;
		}
	}	



	return input;
}

// Open the stream to write
int serial_putchar(char val, FILE * fp) {

	// Wait until empty, then write value
  	while((UCSR0A&(1<<UDRE0)) == 0);
   	UDR0 = val;
   	return 0;
}

// Wait until a character is available, then read it
int serial_getchar(FILE * fp) {
	// Wait for a character
   	while((UCSR0A&(1<<RXC0)) == 0);
   	return UDR0;
}     

void part_b(void) {

	int i,j;
	int mask = 0x01;

	for(i = 0; i < 10; i++) {

		PORTB = 0;
	
		for(j = 0; j < 8; j++) {

			_delay_ms(100);
			PORTB = mask << j;
					
		}
	}
}

