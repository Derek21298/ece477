all:
	avr-gcc -mmcu=atmega88 guess_num.c
	avr-objcopy -j .text -j .data -O ihex a.out a.hex
	gcc rpi_recv.c -o rpi_recv

fuse:
	sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88p -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m

flash:
	sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88p -U flash:w:a.hex:i

terminal:
	sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88p -t

clean: 
	rm -rf a.hex a.out rpi_recv
