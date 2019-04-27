#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void from_to(int f1,int f2);
void setup_stdin(void);

int init(void);

int main() { 
	
	int file;
   	setup_stdin();  // Initialize stdin for serial
   	file=init();	// Initialize the serial port

	// Error Check
	if(file < 0){
		printf("ERROR INITIALIZING SERIAL PORT!\n");
		return 0;
	}

	// Fork the from_to function
	// This makes it so that we can read from the serial and also write at the same time
   	if(fork()){ 
		from_to(file,1);
	}	
   	else{
		from_to(0,file);
	}

     	return 1;

}

// Initialize stdin for serial
void setup_stdin(void) { 

	// Create a struck termios	
	struct termios tc;

	// Get the attributes of the struct
   	tcgetattr(0, &tc);

	// Set the appropriate flags
   	tc.c_lflag &=~ICANON;	// Disable canonical
   	tc.c_lflag |=ECHO;	// Enable ECHO
	tc.c_cc[VMIN]=0;	// These were useful tips given by Professor Bruce Segee
	tc.c_cc[VTIME]=0;
	
	// Set the attributes of the struct
   	tcsetattr(0, TCSANOW, &tc);
}

// Function to read data from a file and write to another
void from_to(int f1, int f2) {  
	
	char c;
	
	// Infinite loop
   	while(1) {
		// If the file reads a character
		if(read(f1,&c,1)) {
			// Write to the other file that character
			 write(f2,&c,1);
		}
	}  
}

// Initialize serial communication
int  init() {
   
 	int file;
 	struct termios tc;	// Create a struct termios

	// Open the serial port ttyS0 to read and write 
    	file = open("/dev/ttyS0", O_RDWR|O_NOCTTY);

	if(file < 0){
		printf("Error opening serial port ttyS0\n");
		return -1;
	}

	// Get the attributes of the struct
    	tcgetattr(file, &tc);
	
	// Set the appropriate flags
    	tc.c_iflag = IGNPAR;
    	tc.c_oflag = 0;
    	tc.c_cflag = CS8 | CREAD | CLOCAL; // 8 bit chars enable receiver no modem status lines
    	tc.c_lflag =0 ;

    	// Setting baud rate to 1200
    	cfsetispeed(&tc, B1200);
    	cfsetospeed(&tc, B1200);

    	// Set the attributes for the struct
    	tcsetattr(file, TCSANOW, &tc);

  	return file;
}

