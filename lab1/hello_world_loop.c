//
//	ECE 477 - Lab 1
//	Authors: Derek Haas, Alex Barnett, Dustin Knight
//	Description: Print "Hello World" the amount of times the size of an int
//	  	     Print "Hello World" the amount of times the size of a long
//

#include <stdio.h>

int main() {

	int size_int = sizeof(int);
	int size_long = sizeof(long);
	int i = 0;

	// Prints "Hello World" the amount of times that is the size of an int in bytes
	printf("Print \"Hello World\" the number of times corresponding to the size of an int in bytes.\n");
	printf("Printing \"Hello World\" %d times\n", size_int);
	for(i = 0; i < size_int; i++) printf("Hello World!\n");
	printf("\n");	

	// Prints "Hello World" the amount of times that is the size of a long in bytes
	printf("Print \"Hello World\" the number of times corresponding to the size of a long in bytes.\n");
	printf("Printing \"Hello World\" %d times\n", size_long);
	for(i = 0; i < size_long; i++) printf("Hello World!\n");

}
