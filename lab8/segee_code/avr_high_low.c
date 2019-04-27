#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 1000000UL
#include <util/delay.h>

int serial_putchar(char, FILE *);
int serial_getchar(FILE *);
static FILE serial_stream = FDEV_SETUP_STREAM(serial_putchar, serial_getchar, _FDEV_SETUP_RW);

void init_serial(void);
void do_high_low(void);
int get_password(void);

int main(void) { 
	init_serial();
  	_delay_ms(2000);
  
  	FILE *fp, *fpr;
  	int guess,x;
  	fp=stdout;
	fpr=stdin;
	int password = 1234;
	int pass_guess;

	fprintf(fp, "Please enter 4-digit password to unlock High-Low Game:\r\n");	

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

  	while(1) { 
     		do_high_low();
  	}   
  	return 0;
}

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
   	UBRR0H=0b00000011;
   	UBRR0L=0b01010000; // 1200 BAUD FOR 8MHZ SYSTEM CLOCK
   	UCSR0A= 1<<U2X0;
   	UCSR0C= (1<<USBS0)|(3<<UCSZ00) ;  // 8 BIT NO PARITY 2 STOP
   	UCSR0B=(1<<RXEN0)|(1<<TXEN0)  ; //ENABLE TX AND RX ALSO 8 BIT
   	stdin=&serial_stream;
   	stdout=&serial_stream;
}   

void do_high_low(void) {
   	FILE *fp, *fpr;
   	int answer, guess;
 
   	answer=rand()%10000;
   	fp=stdout;
   	fpr=stdin;
 
 	fprintf(fp,"Welcome to the high-low guessing game!\r\n");
  	fprintf(fp,"Please enter integer guesses between 0 and 10000: \r\n");
 

  	guess=answer+1;
 
  	while(guess!=answer){

	// Hold program until a guess is written to stdin
   	while(fscanf(fpr,"%d",&guess)!=1){
		 fscanf(fpr,"%*s");
 	}

	fprintf(fp, "Guess: %d\r\n", guess);
	
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

int serial_putchar(char val, FILE * fp) {
  	while((UCSR0A&(1<<UDRE0)) == 0); //wait until empty 
   		UDR0 = val;
   	return 0;
}

//simplest possible getchar, waits until a char is available and reads it
//note:1) it is a blocking read (will wait forever for a char)
//note:2) if multiple characters come in and are not read, they will be lost
int serial_getchar(FILE * fp) {
   	while((UCSR0A&(1<<RXC0)) == 0);  //WAIT FOR CHAR
   	return UDR0;
}     


