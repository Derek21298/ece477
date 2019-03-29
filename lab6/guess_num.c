#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

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
void update_clock_speed(void);

int main(void) {

	update_clock_speed();
	init_serial();
	_delay_ms(2000);
	while(1){
		
		do_high_low();

	} //end of while loop
	return 0;
}

void init_serial(void) {

	UBRR0H = 0;
	UBRR0L = 212;
	UCSR0A = 1 << U2X0;
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	stdin = &serial_stream;
	stdout = &serial_stream;
}

void update_clock_speed(void)
{
  char temp;
  temp=eeprom_read_byte((void *)1); //read oscillator offset sign 
                                    //0 is positive 1 is  negative
                                    //erased reads as ff (so avoid that)
  if(temp==0||temp==1)      //if sign is invalid, don't change oscillator
  {
      if(temp==0)
	  {
	     temp=eeprom_read_byte((void *)0);
		 if(temp != 0xff) OSCCAL+=temp;
	  }
	  else
	  {
	     temp=eeprom_read_byte((void *)0);
		 if(temp!=0xff) OSCCAL -=temp;
	  }
  }
}

void do_high_low(void){

	FILE *fp, *fpr;
	int answer, guess;
	answer = rand()%10;
	fp = stdout;
	fpr = stdin;

	fprintf(fp, "Welcome to the High-Low guessing game \r\n");
	fprintf(fp, "Please enter integer guesses between 0 and 10k\r\n");

	guess = answer + 1;

	fprintf(fp, "The answer is %d\n", answer);

	while(guess != answer){

		fprintf(fp,"Getting guess...\n");
		fscanf(fpr, "%d", &guess);
		fprintf(fp, "Your guess is %d\n", guess);		



		while(fscanf(fpr, "%d", &guess)!=1){ 
			fprintf(fp, "ENTER THE NUMBER MASON\n");
			_delay_ms(2000);
			fscanf(fpr,"%*s");

		}

		fprintf(fp, "Your guess is %d\n", guess);		

		if(guess<answer) 
			fprintf(fp, "Tow low, try again \r\n");

		else if(guess>answer) 
			fprintf(fp,"Too high, try again \r\n");

		else 
			fprintf(fp, "Congratulations you got it right \r\n");

	}

}

int serial_putchar(char val, FILE *fp){

	while((UCSR0A & (1 << UDRE0)) == 0);
	UDR0 = val;
	return 0;

}

int serial_getchar(FILE *fp){

	while((UCSR0A & (1 << RXC0)) == 0);
	return UDR0;

}
