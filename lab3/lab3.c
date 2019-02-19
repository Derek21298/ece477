/*
*	ECE 477 Lab 3
*	Authors: Derek Haas, Dustin Knight, Alex Barnett
*	Date: 2-18-19

*	Description:
*
*	Part A: Read the file /proc/loadavg and save the first value in the
*		file (minute average load on the CPU).  Based on the value
*		in the file, call lab2 code to turn on LEDs corresponding
*		to the load intensity on the CPU.
*
*	Part B: Read the file /proc/uptime and save the first value in the
*		file (amount of time in seconds the system has been up since
*		boot).  This value is converted to minutes and that binary 
*		representation is displayed on the LEDs. 
*
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {

	FILE *fff;			// Create a file pointer
	char value[256];		// Value from the file (string)
	float result;			// Where value from file is stored
	int cool_result;		// Integer value for something cool
	char string[256];
	char system_string[256];

	// If the only command line argument is the program itself
	if(argc == 1) {	

		// Infinite loop to check loadavg
		while(1) {

			// Open the loadavg using file pointers
			fff = fopen("/proc/loadavg", "r");

			// Error checking
			if(fff == 0) {
				printf("ERROR OPENING FILE!\n");	
				return 0;
			}
	
			// Read the first value in file
			fscanf(fff, "%s", value);
	
			// Convert the value from string to float
			result = atof(value);

			printf("Value is %f\n", result); 

			// For different values in loadavg,
			// turn on the corresponding LEDs
			if(result < 0.125) system("./lab2 1");
			if(result > 0.125) system("./lab2 3");
			if(result > 0.25) system("./lab2 7");
			if(result > 0.5) system("./lab2 15");
			if(result > 1.0) system("./lab2 31");
			if(result > 2.0) system("./lab2 63");
			if(result > 4.0) system("./lab2 127");
			if(result > 8.0) system("./lab2 255");

			// Wait 10 seconds and close since
			// loadavg is an avg minute reading
			sleep(10);
			fclose(fff);

		}

	}

	// Else there was more than 1 command line argument
	else {
		
		// Infinite loop to read uptime file
		while(1) {

			// Create file pointer to open uptime
			fff = fopen("/proc/uptime", "r");

			// Error checking
			if(fff == 0) {
				printf("ERROR OPENING FILE!\n");	
				return 0;
			}
	
			// Scan the file for the first value
			fscanf(fff, "%s", value);
	
			// Convert the value from a string to an int
			cool_result = atoi(value);
			// Convert the time from seconds to minutes
			cool_result = cool_result / 60;
			// Save the int result to a string value
			snprintf(string, 10, "%d", cool_result);
			
			// Copy a string to another stirng
			strcpy(system_string, "./lab2 ");
			// Append to the end of the string
			strcat(system_string, string);		
			printf("Time up is %s minutes\n", string);

			// Run the lab2 program with the string
			system(system_string);

			// Wait 60 seconds before updating the LEDs
			sleep(60);

			fclose(fff);
		}
	}
}


