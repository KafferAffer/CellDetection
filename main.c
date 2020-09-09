//To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
//To run (linux/mac): ./main.out example.bmp example_inv.bmp

//To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"

//Declaring the array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char work_image[BMP_WIDTH][BMP_HEIGTH];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

void colorToBinary(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char work_image[BMP_WIDTH][BMP_HEIGTH]){
  for (int x = 0; x < BMP_WIDTH; x++){
    for (int y = 0; y < BMP_HEIGTH; y++){
      int r = input_image[x][y][0];
      int g = input_image[x][y][1];
      int b = input_image[x][y][2];
      int gray = 0.2126*r + 0.7152*g + 0.0722*b;
        if(gray > 90){
          work_image[x][y] = 1;
        }else{
          work_image[x][y] = 0;
        }
    }
  }
}

int checkNeighbor(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], int x, int y){
  //Check left
  if((x-1)<0 || work_image[x-1][y] == 0){
    return 0;
  }
  if((x+1)>=BMP_WIDTH || work_image[x+1][y] == 0){
    return 0;
  }
  if((y-1)<0 || work_image[x][y-1] == 0){
    return 0;
  }
  if((y+1)>=BMP_HEIGTH || work_image[x][y+1] == 0){
    return 0;
  }
  return 1;
}

void erodePicture(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH]){

  //Loop throug pixels
  for (int x = 0; x < BMP_WIDTH; x++){
    for (int y = 0; y < BMP_HEIGTH; y++){
      if(work_image[x][y]==1){
        if(checkNeighbor(work_image,x,y) == 0){
          work_image[x][y]=2;
        }
      }
    }
  }

  //Loop throug pixels
  for (int x = 0; x < BMP_WIDTH; x++){
    for (int y = 0; y < BMP_HEIGTH; y++){
      if(work_image[x][y]==2){
        work_image[x][y]=0;
      }
    }
  }
}

void workToOutput(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]){
  for (int x = 0; x < BMP_WIDTH; x++){
    for (int y = 0; y < BMP_HEIGTH; y++){
      for(int c = 0; c<BMP_CHANNELS; c++){
        output_image[x][y][c] = 255*work_image[x][y];
      }
    }
  }
}

//Main function
int main(int argc, char** argv)
{
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

  printf("Example program - 02132 - A1\n");

  //Load image from file
  read_bitmap(argv[1], input_image);

  //Run binary
  colorToBinary(input_image,work_image);

  workToOutput(work_image,output_image);
  write_bitmap(output_image, "startOutput.bmp");

  for(int i = 0; i<10; i++){
    //Erode
    erodePicture(work_image);

    //Make output image
    workToOutput(work_image,output_image);

    //Save image to file
    char name[20];
    sprintf(name, "testOutput_%i.bmp", i);
    write_bitmap(output_image, name);
  }
  

  printf("Done!\n");
  return 0;
}




