#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void set_interface_attribs(void);
void from_to(int file1, int file2);
int init_serial(void);

int main(void) {

	int file;
	int guess;
	int input = stdin;
	int output = stdout;

	set_interface_attribs();
	file = init_serial();
	
	printf("About to talk with AVR\n");
	
	while(1) {
	
		fprintf(stdout, "Enter Guess: ");
		fscanf(stdin, "%d", &guess);
		fprintf(stdout ,"\n");
			
		if(fork()) {
			from_to(file, input);
		}
		else {
			from_to(output, file);
		}
	}

	return 0;
}

void set_interface_attribs(void) {

	struct termios tty;
	
	tcgetattr(0, &tty);
	
	tty.c_lflag &= ~ICANON;
	tty.c_lflag &= ~ECHO;

	tcsetattr(0, TCSANOW, &tty);
}

void from_to(int file1, int file2) {

	char c;

	while(1) {
		if(read(file1,&c,1)){
			write(file2,&c,1);
		}
	}
}

int init_serial(void) {

	int file;

	struct termios tty;


	file = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
	
	if(file == NULL) {
		printf("ERROR OPENING ttyS0!\n");
		return 0;
	}
	
	tcgetattr(file, &tty);

	tty.c_iflag = IGNPAR;
	tty.c_oflag = 0;
	tty.c_cflag = CS8 | CREAD | CLOCAL;
	tty.c_lflag = 0;

	cfsetispeed(&tty, B4800);
	cfsetospeed(&tty, B4800);

	tcsetattr(file, TCSANOW, &tty);

	return file;
	
}









	
