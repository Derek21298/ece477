#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <util/delay.h>

#define F_CPU 1000000UL

void init_serial(void);


int main(void) {

}

void init_serial(void) {

	UBRR0H = 0;
	UBRR0L = 12;
	UCSR0A = 1 << U2X0;
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	stdin = &serial_stream;
	stdout = &serial_stream;
}
