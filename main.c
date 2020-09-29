

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h> 
#include "cbmp.h"
#include "main.h"

int cellCount = 0;
int xcoordinates[4000] = {};
int ycoordinates[4000] = {};

int frameSize;
int threshhold;
FILE *fptr;


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
        if(gray > threshhold){ //TH
          work_image[x][y] = 1;
        }else{
          work_image[x][y] = 0;
        }
    }
  }
}


//Checks a certain point (x,y) to see if it fits the pattern shown above
int checkNeighbor(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], int x, int y, int neighborArray[3][3]){
  for(int xc = 0; xc<3; xc++){
    for(int yc = 0; yc<3; yc++){
      if
      (
        (x+xc-1)<0 ||
        (x+xc-1)>=BMP_WIDTH ||
        (y+yc-1)<0 ||
        (y+yc-1)>=BMP_HEIGTH
      ){
        continue;
      }else if(
        ((neighborArray[xc][yc]==1) && (work_image[x+xc-1][y+yc-1]==0))
      ){
        return 0;
      }
    }
  }
  return 1;
}

bool erodePicture(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], int neighborArray[3][3]){
  //Time test for erosion loop
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  //Loop throug pixels
  for (int x = 0; x < BMP_WIDTH; x++){//-1??
    for (int y = 0; y < BMP_HEIGTH; y++){//-1??
      if(work_image[x][y]==1){
        if(checkNeighbor(work_image,x,y,neighborArray) == 0){
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

  //End time test
  end = clock();
  cpu_time_used = end-start;
  if(fptr!=NULL)fprintf(fptr,"Time on erosion: %f ms\n", cpu_time_used * 1000.0 /CLOCKS_PER_SEC);

  if (checkbox == 1){
    return true;
  }
  return false;
}

void tryToFrame(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], int x, int y){
  int radius = frameSize/2;

  //Loop throug pixels
  if(work_image[x][y]==1){
    //check frame
    //top and buttom
    for (int i = x-radius; i <= x+radius; i++){
      //top framepoint = (i, y-(radius))
      if(!(0>y-(radius) || y-(radius)>=BMP_HEIGTH)&&(work_image[i][y-(radius)]==1)){
        //printf("bye");
        return;
      }
      //buttom framep. = (i, y+(radius))
      if(!(0>y+(radius) || y+(radius)>=BMP_HEIGTH)&&(work_image[i][y+(radius)]==1)){
        //printf("bye");
        return;
      }
    }
    //sides
    for (int i = y-radius+1; i <= y+radius-1; i++){
      //left framepoint = (x-radius,i)
      if(!(0>x-(radius) || x-(radius)>=BMP_WIDTH)&&(work_image[x-radius][i]==1)){
        //printf("bye");
        return;
      }
      //rig. framepoint = (x+radius,i)
      if(!(0>x+(radius) || x+(radius)>=BMP_WIDTH)&&(work_image[x+radius][i]==1)){
        //printf("bye");
        return;
      }
    }
    //Save coordinates
    xcoordinates[cellCount] = x;
    ycoordinates[cellCount] = y;
    cellCount++;
    //printf("%i [ %i, %i ]\n",cellCount,x,y); //print coordinates


    //Fill frame
    for (int i = x-radius+1; i <= x+radius-1; i++){
      for (int j = y-radius+1; j <= y+radius-1; j++){
        if(i>=0&&i<BMP_WIDTH&&j>=0&&j<BMP_HEIGTH){
          work_image[i][j] = 0;
        }
      }
    }
  }
   
}

int picCount = 0;
void frameloop(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH]){
  //Time test for frame loop
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  for (int x = 0; x < BMP_WIDTH; x++){
    for (int y = 0; y < BMP_HEIGTH; y++){
      tryToFrame(work_image,x,y);
    }
  }

  //Make output image
  workToOutput(work_image,output_image);

  //fixed length of num
  char * intPrefix = "";
  int intWantedLength = 3;
  if (picCount < 100){
    intPrefix ="0";
  }
  if (picCount < 10){
    intPrefix ="00";
  }

  //Save image to file
  char name[20];
  sprintf(name, "testOutput_%s%i.bmp", intPrefix, picCount);
  picCount++;
  write_bitmap(output_image, name);

  //End time test
  end = clock();
  cpu_time_used = end-start;
  if(fptr!=NULL)fprintf(fptr,"Time on fram (Size: %i) loop: %f ms\n", frameSize, cpu_time_used * 1000.0 /CLOCKS_PER_SEC);
}



void workToOutput(unsigned char work_image[BMP_WIDTH][BMP_HEIGTH], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]){
  for (int x = 0; x < BMP_WIDTH; x++){
    for (int y = 0; y < BMP_HEIGTH; y++){
      for(int c = 0; c<BMP_CHANNELS; c++){
        output_image[x][y][c] = 255*work_image[x][y];
      }
    }
  }

  for (int i = 0; i < cellCount; i++){
      output_image[xcoordinates[i]][ycoordinates[i]][0] = 255;

      for (int j = -10; j <= 10; j++){
        if(0<=xcoordinates[i]+j&&xcoordinates[i]+j<BMP_WIDTH){
          output_image[xcoordinates[i]+j][ycoordinates[i]][0] = 255;
          output_image[xcoordinates[i]+j][ycoordinates[i]][1] = 0;
          output_image[xcoordinates[i]+j][ycoordinates[i]][2] = 0;
        }
        if(0<=ycoordinates[i]+j&&ycoordinates[i]+j<BMP_HEIGTH){
          output_image[xcoordinates[i]][ycoordinates[i]+j][0] = 255;
          output_image[xcoordinates[i]][ycoordinates[i]+j][1] = 0;
          output_image[xcoordinates[i]][ycoordinates[i]+j][2] = 0;
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
      for (int j = -10; j <= 10; j++){
        if(0<=xcoordinates[i]+j&&xcoordinates[i]+j<BMP_WIDTH){
          output_image[xcoordinates[i]+j][ycoordinates[i]][0] = 255;
          output_image[xcoordinates[i]+j][ycoordinates[i]][1] = 0;
          output_image[xcoordinates[i]+j][ycoordinates[i]][2] = 0;
        }
        if(0<=ycoordinates[i]+j&&ycoordinates[i]+j<BMP_HEIGTH){
          output_image[xcoordinates[i]][ycoordinates[i]+j][0] = 255;
          output_image[xcoordinates[i]][ycoordinates[i]+j][1] = 0;
          output_image[xcoordinates[i]][ycoordinates[i]+j][2] = 0;
        }
      }
  }
  write_bitmap(output_image, outputname);
}

//The pattern used to check neighbors
int plusShape[3][3] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0}
};

//The pattern used to check neighbors
int fullShape[3][3] = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
};


void plusLoop(){
  if(erodePicture(work_image,plusShape)){
    frameloop(work_image);
    fullLoop();
  }
}

void fullLoop(){
  if(erodePicture(work_image,fullShape)){
    frameloop(work_image);
    plusLoop();
  }
}


//Main function
int detectCells(int argc, char** argv, int inframesize, int inthreshhold)
{
  fptr = fopen("timeTest.txt", "w+");

  //Time test for it all
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  frameSize = inframesize;
  threshhold = inthreshhold;
  //Load image from file
  read_bitmap(argv[1], input_image);

  //Run binary
  colorToBinary(input_image,work_image);

  workToOutput(work_image,output_image);
  write_bitmap(output_image, "startOutput.bmp");

  //Erode
  fullLoop();

  //printf("Done detecting\n");

  // create output
  createOutputPic(input_image,output_image, argv[2]);

  //printf("Output image made!\n");

  printf("Total cellCount: %i ", cellCount );

  //End time test
  end = clock();
  cpu_time_used = end-start;
  if(fptr!=NULL)fprintf(fptr, "Total time: %f ms\n", cpu_time_used * 1000.0 /CLOCKS_PER_SEC);

  return 0;
}


