//
//	ECE 477 - Lab 1
//	Authors: Derek Haas, Alex Barnett, Dustin Knight
//	Description: Print "Hello World" the amount of times the size of an int
//	  	     Print "Hello World" the amount of times the size of a long
//	Something Cool: Color the "Hello World" in the console

#include <stdio.h>

void printColorizedHelloWorld(int size);

int main() {

	int size_int = sizeof(int);
	int size_long = sizeof(long);

	// Prints "Hello World" the amount of times that is the size of an int in bytes
	printf("Print \"Hello World\" the number of times corresponding to the size of an int in bytes.\n");
	printf("Printing \"Hello World\" %d times!\n", size_int);
	printColorizedHelloWorld(size_int);

	printf("\n");

	// Prints "Hello World" the amount of times that is the size of a long in bytes
	printf("Print \"Hello World\" the number of times corresponding to the size of a long in bytes.\n");
	printf("Printing \"Hello World\" %d times!\n", size_long);
	printColorizedHelloWorld(size_long);
}

void printColorizedHelloWorld(int size){
	#define RESET_COLOR "\x1b[0m"
	char string[12] = {'H','e','l','l','o',' ','W','o','r','l','d','!'};
	int i,j,k;

	// Loop size_int times
	for(i = 0,j = 31,k = 0; i < size;j++,k++){
		// Change color as j increments
		printf("%c[%dm",0x1B,j);
		// Print character in string
		printf("%c",string[k]);
		// Reset color to default
		printf(RESET_COLOR);
		// After 0x1B[37m in the ANSI escape code, background color changes
		if(j == 37){
			// 91 is start of 'bright' colors (added for variety)
			j = 91;
		}
		// After 0x1B[97m, background color changes
		if(j == 97){
			// Return to color sequence start
			j = 31;
		}
		// Once k reaches end of string, reset
		if(k == 10){
			// Set to -1 dur to for-loop incrementing
			k = -1;
			printf("\n");
			i++;
		}
	}
}
