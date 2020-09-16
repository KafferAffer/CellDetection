

#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"
#include "main.h"

int cellCount = 0;
int xcoordinates[400] = {};
int ycoordinates[400] = {};


//Declaring the array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char work_image[BMP_WIDTH][BMP_HEIGTH];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

//Function that converts the colorful 3d array to a 2d integer array filled with 1's and zeros.
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

//The pattern used to check neighbors
int neighbor[3][3] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0}
};


//Checks a certain point (x,y) to see if it fits the pattern shown above
int checkNeighbor(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], int x, int y){
  for(int xc = 0; xc<3; xc++){
    for(int yc = 0; yc<3; yc++){
      if(
        (x+xc-1)<0 ||
        (x+xc-1)>=BMP_WIDTH ||
        (y+yc-1)<0 ||
        (y+yc-1)>=BMP_HEIGTH
        
      ){
        break;
      }
      if((neighbor[xc][yc]==1) && (work_image[x+xc-1][y+yc-1]==0)){
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
  for (int i = 0; i < cellCount; i++){
    if (1 == 1){

      for (int j = -10; j <= 10; j++){
        if(xcoordinates[i]+j >= 0 && xcoordinates[i]+j < BMP_WIDTH){
          output_image[xcoordinates[i]+j][ycoordinates[i]][0] = 255;
          output_image[xcoordinates[i]+j][ycoordinates[i]][1] = 0;
          output_image[xcoordinates[i]+j][ycoordinates[i]][2] = 0;
        }
        if(ycoordinates[i]+j >= 0 && ycoordinates[i]+j < BMP_HEIGTH){
          output_image[xcoordinates[i]][ycoordinates[i]+j][0] = 255;
          output_image[xcoordinates[i]][ycoordinates[i]+j][1] = 0;
          output_image[xcoordinates[i]][ycoordinates[i]+j][2] = 0;
        }
      }
    }
  }
    
}

void createOutputPic(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], char * outputname){
  for (int x = 0; x < BMP_WIDTH; x++){
    for (int y = 0; y < BMP_HEIGTH; y++){
      for(int c = 0; c<BMP_CHANNELS; c++){
        output_image[x][y][c] = input_image[x][y][c];
      }
    }
  }


  for (int i = 0; i < cellCount; i++){
    if (1 == 1){

      for (int j = -10; j <= 10; j++){
        if(xcoordinates[i]+j >= 0 && xcoordinates[i]+j < BMP_WIDTH){
          output_image[xcoordinates[i]+j][ycoordinates[i]][0] = 255;
          output_image[xcoordinates[i]+j][ycoordinates[i]][1] = 0;
          output_image[xcoordinates[i]+j][ycoordinates[i]][2] = 0;
        }
        if(ycoordinates[i]+j >= 0 && ycoordinates[i]+j < BMP_HEIGTH){
          output_image[xcoordinates[i]][ycoordinates[i]+j][0] = 255;
          output_image[xcoordinates[i]][ycoordinates[i]+j][1] = 0;
          output_image[xcoordinates[i]][ycoordinates[i]+j][2] = 0;
        }
      }
    }
  }
  write_bitmap(output_image, outputname);
}



//Main function
int detectCells(int argc, char** argv)
{
  //Load image from file
  read_bitmap(argv[1], input_image);

  //Run binary
  colorToBinary(input_image,work_image);

  workToOutput(work_image,output_image);
  write_bitmap(output_image, "startOutput.bmp");

  //Erode
  erodePicture(work_image);

  printf("Done detecting\n");

  // create output
  createOutputPic(input_image,output_image, argv[2]);

  printf("Output image made!\n");
  return 0;
}


