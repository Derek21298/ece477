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

/* this is the high_low server running on serial on an avr */
/* it sets up the serial communication for 4800 baud */
/* note that the random number generator will always generate the same sequence */
int main(void)
{ 
  init_serial();
  _delay_ms(2000);
  
  FILE *fp, *fpr;
  int guess,x;
  fp=stdout;
  fpr=stdin;

  fprintf(fp,"TESTING\r\n");

  while(1) 
  { 
     	x = fscanf(fpr,"%d",&guess);
	fprintf(fpr,"%d\r\n",x);
	while(x!=1){     
		fprintf(fp,"%d\r\n",guess);
	}
     //do_high_low();
  }   
  return 0;
}

/* Initializes AVR USART for 1200 baud (assuming 1MHz clock) */
/* 8MHz/(16*(212+1)) = 4800		                     */
void init_serial(void)
{
   UBRR0H=0b00000011;
   UBRR0L=0b01010000; // 4800 BAUD FOR 8MHZ SYSTEM CLOCK
   UCSR0A= 1<<U2X0;
   UCSR0C= (1<<USBS0)|(3<<UCSZ00) ;  // 8 BIT NO PARITY 2 STOP
   UCSR0B=(1<<RXEN0)|(1<<TXEN0)  ; //ENABLE TX AND RX ALSO 8 BIT
   stdin=&serial_stream;
   stdout=&serial_stream;

}   

/* This code is essentially identical to the high_low_server code that */
/* is one of the examples on the 477 page.  Essentially file I/O,      */
/* stdin/stdout, and serial I/O are all incredibly similar and almost  */
/* interchangable                                                      */
void do_high_low(void)
{
   FILE *fp, *fpr;
   int answer, guess;
 
   answer=rand()%10000;
   fp=stdout;
   fpr=stdin;
 
  fprintf(fp,"Welcome to the high-low guessing game!\r\n");
  fprintf(fp,"Please enter integer guesses between 0 and 10000: \r\n");
 

  guess=answer+1;
 
  while(guess!=answer){

	//fflush(stdout);

	// Hold program until a guess is written to stdin
   	while(fscanf(fpr,"%d",&guess)!=1){
//		 fprintf(fp,"%d\n",guess);
		 fscanf(fpr,"%*s");
 	}	
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

//simplest possible putchar, waits until UDR is empty and puts character
int serial_putchar(char val, FILE * fp)
{
  while((UCSR0A&(1<<UDRE0)) == 0); //wait until empty 
   UDR0 = val;
   return 0;
}

//simplest possible getchar, waits until a char is available and reads it
//note:1) it is a blocking read (will wait forever for a char)
//note:2) if multiple characters come in and are not read, they will be lost
int serial_getchar(FILE * fp)
{
   while((UCSR0A&(1<<RXC0)) == 0);  //WAIT FOR CHAR
   return UDR0;
}     


