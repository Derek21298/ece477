all:
	avr-gcc -mmcu=atmega88 avrcode.c
	avr-objcopy -j .text -j .data -O ihex a.out a.hex
	gcc -Wall -o read_signal read_signal.c -lwiringPi

fuse:
	sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88p -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m

flash:
	sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88p -U flash:w:a.hex:i

terminal:
	sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88pa -t

clean: 
	rm -rf a.hex a.out read_signal
