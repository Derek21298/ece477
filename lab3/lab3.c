/*
*	ECE 477 Lab 3
*	Authors: Derek Haas, Dustin Knight, Alex Barnett
*	Date: 2-18-19
*	Description:
*
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define LED1 1
#define LED2 3
#define LED3 7
#define LED4 15
#define LED5 31
#define LED6 63
#define LED7 127
#define LED8 255

int main(int argc, char **argv) {

	FILE *fff;
	char value[256];
	float result;
	int cool_result;
	char string[256];
	char system_string[256];

	if(argc == 1) {	

		while(1) {

			fff = fopen("/proc/loadavg", "r");

			if(fff == 0) {
				printf("ERROR OPENING FILE!\n");	
				return 0;
			}
	
			fscanf(fff, "%s", value);
	
			result = atof(value);

			printf("Value is %f\n", result); 

			if(result < 0.125) system("./lab2 1");
			if(result > 0.125) system("./lab2 3");
			if(result > 0.25) system("./lab2 7");
			if(result > 0.5) system("./lab2 15");
			if(result > 1.0) system("./lab2 31");
			if(result > 2.0) system("./lab2 63");
			if(result > 4.0) system("./lab2 127");
			if(result > 8.0) system("./lab2 255");

			sleep(10);

			fclose(fff);

		}

	}
	else {
		
		while(1) {

			fff = fopen("/proc/uptime", "r");

			if(fff == 0) {
				printf("ERROR OPENING FILE!\n");	
				return 0;
			}
	
			fscanf(fff, "%s", value);
	
			cool_result = atoi(value);
			cool_result = cool_result / 60;
			snprintf(string, 10, "%d", cool_result);
			
			strcpy(system_string, "./lab2 ");
			strcat(system_string, string);		
			printf("Time up is %s minutes\n", string);

			system(system_string);

			sleep(60);

			fclose(fff);


		}
	}
}


