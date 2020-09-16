//To compile (win): gcc runner.c cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int main(int argc, char** argv) {
	//argc counts how may arguments are passed
	//argv[0] is a string with the name of the program
	//argv[1] is the first command line argument (input image)
	//argv[2] is the second command line argument (output image)

	//Checking that 2 arguments are passed
	if (argc != 3)
	{
	    fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
	    exit(1);
	}

	printf("Running program - a turtle made it to the water - V1.0\n");
	//Detect the cells and make file
	detectCells(argc, argv);
	
	return 0;
}