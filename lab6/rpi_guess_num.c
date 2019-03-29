#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void from_to(int f1,int f2);
void setup_stdin(void);

int init(void);

int main() { 
	
	int fd1;
   	char buf[1000];
   	setup_stdin();
   	fd1=init();

	//todo make sure fd1 is ok
   	if(fork()){ 
		from_to(fd1,1);
	}	
   	else{
		from_to(0,fd1);
	}
   	//todo sure would be nice to have an exit condition
     	return 1;

}

void setup_stdin(void) { 
	
	struct termios tc;
   	tcgetattr(0, &tc);
   	tc.c_lflag &=~ICANON ;
   	tc.c_lflag &=~ECHO;
	tc.c_cc[VMIN]=0;
	tc.c_cc[VTIME]=0;
   	tcsetattr(0, TCSANOW, &tc);

}


void from_to(int f1, int f2) {  
	
	char c;
   	while(1) {
		if(read(f1,&c,1)) {
			 write(f2,&c,1);
		}
	}  
}

int  init() {
   
 	int fd1;
 	struct termios tc;                // terminal control structure

   	//todo serial port should not be hard coded
    	fd1 = open("/dev/ttyS0", O_RDWR|O_NOCTTY);  // really ought to check for error
    	tcgetattr(fd1, &tc);
    	tc.c_iflag = IGNPAR;
    	tc.c_oflag = 0;
    	tc.c_cflag = CS8 | CREAD | CLOCAL; //8 bit chars enable receiver no modem status lines
    	tc.c_lflag =0 ;

    	//todo baud rate should not be hard coded
    	cfsetispeed(&tc, B1200);
    	cfsetospeed(&tc, B1200);

    	//todo should have bits per character set
    	tcsetattr(fd1, TCSANOW, &tc);
  	return fd1;
}

