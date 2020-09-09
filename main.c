//To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
//To run (linux/mac): ./main.out example.bmp example_inv.bmp

//To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"

int cellCount = 0;
int xcoordinates[400] = {};
int ycoordinates[400] = {};


void frameloop(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH]);
void workToOutput(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);


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

int neighbor[3][3] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0}
};

int checkNeighbor(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], int x, int y){
  for(int xc = 0; xc<3; xc++){
    for(int yc = 0; yc<3; yc++){
      if(
        (x+xc-1)<0 ||
        (x+xc-1)>=BMP_WIDTH ||
        (y+yc-1)<0 ||
        (y+yc-1)>=BMP_HEIGTH ||
        ((neighbor[xc][yc]==1) && (work_image[x+xc-1][y+yc-1]==0))
      ){
        return 0;
      }
    }
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

  int checkbox = 0;
  //Loop throug pixels
  for (int x = 0; x < BMP_WIDTH; x++){
    for (int y = 0; y < BMP_HEIGTH; y++){
      if(work_image[x][y]==2){
        checkbox = 1;
        work_image[x][y]=0;
      }
    }
  }
  if (checkbox == 1){
    frameloop(work_image);
  }
}

void tryToFrame(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], int x, int y){
  //overflow fix pls

  int frameSize = 11;
  int radius = frameSize/2;

  //Loop throug pixels
  if(work_image[x][y]==1){
    //check frame
    //top and buttom
    for (int i = x-radius; i <= x+radius; i++){
      //top framepoint = (i, y-(radius))
      if(work_image[i][y-(radius)]==1){
        //printf("bye");
        return;
      }
      //buttom framep. = (i, y+(radius))
      if(work_image[i][y+(radius)]==1){
        //printf("bye");
        return;
      }
    }
    //sides
    for (int i = y-radius+1; i <= y+radius-1; i++){
      //left framepoint = (x-radius,i)
      if(work_image[x-radius][i]==1){
        //printf("bye");
        return;
      }
      //rig. framepoint = (x+radius,i)
      if(work_image[x+radius][i]==1){
        //printf("bye");
        return;
      }
    }
    //Save coordinates
    xcoordinates[cellCount] = x;
    ycoordinates[cellCount] = y;
    cellCount++;
    printf("%i [ %i, %i ]\n",cellCount,x,y);


    //Fill frame
    for (int i = x-radius+1; i <= x+radius-1; i++){
      for (int j = y-radius+1; j <= y+radius-1; j++){
        work_image[i][j] = 0;
      }
    }
  }
   
}

int picCount = 0;
void frameloop(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH]){
  for (int x = 0; x < BMP_WIDTH; x++){
    for (int y = 0; y < BMP_HEIGTH; y++){
      tryToFrame(work_image,x,y);
    }
  }
  //Make output image
  workToOutput(work_image,output_image);

  //Save image to file
  char name[20];
  sprintf(name, "testOutput_%i.bmp", picCount);
  picCount++;
  write_bitmap(output_image, name);
  erodePicture(work_image);
}



void workToOutput(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]){
  for (int x = 0; x < BMP_WIDTH; x++){
    for (int y = 0; y < BMP_HEIGTH; y++){
      for(int c = 0; c<BMP_CHANNELS; c++){
        output_image[x][y][c] = 255*work_image[x][y];
      }
    }
  }


  //output_image[xcoordinates[0]][ycoordinates[0]][0] = 255;
  for (int i = 0; i < 400; i++){
    if (xcoordinates[i]!=0){
      output_image[xcoordinates[i]][ycoordinates[i]][0] = 255;

      for (int j = -10; j <= 10; j++){
        output_image[xcoordinates[i]+j][ycoordinates[i]][0] = 255;
        output_image[xcoordinates[i]][ycoordinates[i]+j][0] = 255;
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

  //Erode
  erodePicture(work_image);

  

  printf("Done!\n");
  return 0;
}

