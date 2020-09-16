//To compile (win): gcc tester.c cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp

#include "main.h"

int main(int argc, char** argv){
	detectCells(argc, argv);
	return 0;
}