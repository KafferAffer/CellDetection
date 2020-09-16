//To compile (win): gcc tester.c cbmp.c main.c -o test.exe -std=c99
//To run (win): test.exe 
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char work_image[BMP_WIDTH][BMP_HEIGTH];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

void printFailed(char * function, char * test);

int main(int argc, char** argv){
	read_bitmap("example.bmp", input_image);
	printf("tester testing!\n");

	



	write_bitmap(output_image, "BigBoyTest.bmp");
	return 0;
}

void printFailed(char * function, char * test){
	printf("%s failed test: %s!\n", function, test);
}

void testWorkToOutput(){
	//Drawing a 10 by 10 box
	for(int i = 0; i<10; i++){
		for(int j = 0; j<10; j++){
			work_image[i][j] = 1;
		}
	}
	
	//making an output image
	workToOutput(work_image,output_image);

	//checking if output image lives up to expectations
	for(int i = 0; i<10; i++){
		for(int j = 0; j<10; j++){
			if(
				output_image[i][j][0] != 255 ||
				output_image[i][j][0] != 255 ||
				output_image[i][j][0] != 255
			){
				printFailed("workToOutput","1");
			}
		}
	}
}