#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 1000000UL
#include <util/delay.h>

// Variable declarations
int serial_putchar(char, FILE *);
int serial_getchar(FILE *);
static FILE serial_stream = FDEV_SETUP_STREAM(serial_putchar, serial_getchar, _FDEV_SETUP_RW);

void init_serial(void);
void do_high_low(void);
int get_password(void);

int main(void) { 
	// Initialize UART for the AVR
	init_serial();
	// 2 second delay
  	_delay_ms(2000);
  
  	FILE *fp, *fpr;
  	int guess,x;
  	fp=stdout;
	fpr=stdin;
	int password = 1234;
	int pass_guess;

	fprintf(fp, "Please enter 4-digit password to unlock High-Low Game:\r\n");	


	// PART B CODE
	// Hold program until password is correctly input
	while(1) {
		
		pass_guess = get_password();
		
		if(pass_guess == password) {
			fprintf(fp, "Correct Password!\r\n");
			_delay_ms(2000);
			break;
		}
		else  {
			fprintf(fp, "INCORRECT PASSWORD!\r\n");
		}
	}

	// PART A CODE
	// Run "High/Low" game
  	while(1) { 
     		do_high_low();
  	}

  	return 0;
}
// Password function for Part B
int get_password(void) {

   	FILE *fp, *fpr;
   	int guess;
 
   	fp=stdout;
   	fpr=stdin;
  
	// Hold program until a guess is written to stdin
   	while(fscanf(fpr,"%d",&guess)!=1){
		fscanf(fpr,"%*s");
 	}
	fprintf(fp, "Entered Password: %d\r\n", guess);	
	
	return guess;
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

void do_high_low(void) {
   	FILE *fp, *fpr;
   	int answer, guess;
 
	// Create a random answer from 0 to 10000
   	answer=rand()%10000;
 
  	fp=stdout;
   	fpr=stdin;
 
	// /r is a carriage return or "new line" for the AVR
 	fprintf(fp,"Welcome to the high-low guessing game!\r\n");
  	fprintf(fp,"Please enter integer guesses between 0 and 10000: \r\n");
 
	// Initialize guess to be different than answer
  	guess=answer+1;
 
  	while(guess!=answer){

		// Hold program until a guess is written to stdin
	   	while(fscanf(fpr,"%d",&guess)!=1){
			// Ignore any strings
			fscanf(fpr,"%*s");
	 	}
	
		// Check if answer is guess
		if(guess<answer){
			 fprintf(fp,"Too low, try again\r\n");
	    	}

		else if (guess>answer){
			 fprintf(fp,"Too High, try again\r\n");
		}
		else{
			 fprintf(fp,"Congratulations! You got it right!\r\n");
		}
  	}
}

// Open the stream to write
int serial_putchar(char val, FILE * fp) {

	// Wait until empty, then write value
  	while((UCSR0A&(1<<UDRE0)) == 0){
   		UDR0 = val;
	}
   	return 0;
}

// Wait until a character is available, then read it
int serial_getchar(FILE * fp) {
	// Wait for a character
   	while((UCSR0A&(1<<RXC0)) == 0);
   	return UDR0;
}     


