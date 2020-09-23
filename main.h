#include "cbmp.h"
#include <stdbool.h>

//The pattern used to check neighbors
static int plusShape[3][3] = {{0, 1, 0},{1, 1, 1},{0, 1, 0}};

//The pattern used to check neighbors
static int fullShape[3][3] = {{1, 1, 1},{1, 1, 1},{1, 1, 1}};

//Converts from color to binary
void colorToBinary(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char work_image[BMP_WIDTH][BMP_HEIGTH]);

//Checks the neighbors of the coordinate x,y to see if the match a given pattern
	//returns 0 if it doesnt fit returns 1 if it fits
int checkNeighbor(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], int x, int y, int neighborArray[3][3]);

//removes all pixels that dont fit
bool erodePicture(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], int neighborArray[3][3]);

//checks if the frame matches at x,y and if so it counts cell and romes everything within the frame
void tryToFrame(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], int x, int y);

//tries to frame all pixels
void frameloop(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH]);

//converts the 2d work array to a 3d output array that can be written
void workToOutput(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);

//Creates the final picture based on the found pixels 
void createOutputPic(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], char * outputname);

//Runs the actual algorithm
int detectCells(int argc, char** argv, int inframesize, int inthreshhold);

//To switch between x and plus shape
void plusLoop();
void fullLoop();
