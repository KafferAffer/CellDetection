//To compile (win): gcc tester.c cbmp.c main.c -o test.exe -std=c99
//To run (win): test.exe 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char work_image[BMP_WIDTH][BMP_HEIGTH];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];


void printFailed(char * function, char * test);
void printPassed(char * function, char * test);
void testWorkToOutput();
void testErosion();
void resetArrays();
void testFraming();

int main(int argc, char** argv){
	read_bitmap("example.bmp", input_image);
	printf("tester testing!\n");
	testWorkToOutput();
	testErosion(plusShape);
	testErosion(fullShape);
	testFraming();
	return 0;
}

void resetArrays(){
	for(int x = 0; x<BMP_WIDTH;x++){
		for(int y = 0; y<BMP_HEIGTH;y++){
			work_image[x][y] = 0;
			for(int c = 0; c<BMP_CHANNELS;c++){
				output_image[x][y][c]=0;
			}
		}
	}
}

void printFailed(char * function, char * test){
	printf("%s failed test: %s!\n", function, test);
}

void printPassed(char * function, char * test){
	printf("%s passed test: %s!\n", function, test);
}

int countWork(){
	int count = 0;
	for(int x = 0; x<BMP_WIDTH;x++){
		for(int y = 0; y<BMP_HEIGTH;y++){
			if(work_image[x][y]==1){
				count++;
			}
		}
	}
	return count;
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
	bool check = true;
	//checking if output image lives up to expectations
	for(int i = 0; i<10; i++){
		for(int j = 0; j<10; j++){
			if(
				output_image[i][j][0] != 255 ||
				output_image[i][j][0] != 255 ||
				output_image[i][j][0] != 255
			){
				printFailed("workToOutput","1");
				check = false;
			}
		}
	}
	if(check){printPassed("workToOutput","1");}
}

void testErosion(int neighborArray[3][3]){
	resetArrays();
	//Empty array is supposed to erode nothing
	if(erodePicture(work_image,neighborArray)){
		printFailed("erodePicture","1");
	}else{
		printPassed("erodePicture","1");
	}
	resetArrays();
	//if there is only on pixel left on screen it should be removed by erode *CAN BE IMPROVED WITH RANDOM POSITION BUT 10 10 FOR NOW
	work_image[10][10] = 1;
	erodePicture(work_image,neighborArray);
	if(work_image[10][10] == 1){
		printFailed("erodePicture","2");
	}else{
		printPassed("erodePicture","2");
	}
	resetArrays();//In case previous test failed
	//If there is an 11 by 11 area the middle of it should still be 1 after erosion
	for(int i = 0; i<11; i++){
		for(int j = 0; j<11; j++){
			work_image[i][j]=1;
		}
	}
	erodePicture(work_image,neighborArray);
	if(work_image[5][5]=0){
		printFailed("erodePicture","3");
	}else{
		printPassed("erodePicture","3");
	}

	//After an erodePicture there should be fewer dots
	resetArrays();
	for(int i = 0; i<10; i++){
		for(int j = 0; j<10; j++){
			work_image[i][j]=1;
		}
	}
	int before = countWork();
	erodePicture(work_image,neighborArray);
	int after = countWork();
	if(after<before){
		printPassed("erodePicture","4");
	}else{
		printFailed("erodePicture","4");
	}
}

void testFraming(){
	resetArrays();
	//If there is a giant horizontal stripe through the world you should remove anything since the frame should never be that large
	for(int i=0;i<BMP_WIDTH;i++){
		work_image[i][10]=1;
	}
	frameloop(work_image);
	bool ok = true;
	for(int i=0;i<BMP_WIDTH;i++){
		if(work_image[i][10] != 1){
			ok = false;
		}
	}
	if(ok){
		printPassed("frameLoop","1");
	}else{
		printFailed("frameLoop","1");
	}

	resetArrays();
	//the same as before but for vertical
	for(int i=0;i<BMP_HEIGTH;i++){
		work_image[10][i]=1;
	}
	frameloop(work_image);
	ok = true;
	for(int i=0;i<BMP_HEIGTH;i++){
		if(work_image[10][i] != 1){
			ok = false;
		}
	}
	if(ok){
		printPassed("frameLoop","2");
	}else{
		printFailed("frameLoop","2");
	}

	resetArrays();
	//If there is a square in the middle it should be framed
	work_image[BMP_WIDTH/2][BMP_HEIGTH/2]=1;
	frameloop(work_image);
	ok = work_image[BMP_WIDTH/2][BMP_HEIGTH/2]==0;
	if(ok){
		printPassed("frameLoop","3");
	}else{
		printFailed("frameLoop","3");
	}
}