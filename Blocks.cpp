#include "raylib.h"
#include <string>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>

//compile: g++ Blocks.cpp -o Blocks -lraylib -lm -ldl -lpthread -lGL -lX11
//run:     ./Blocks


// raylib uses float for most numbers, and so use 2.0f to convert int to float. Note that 2.0 will be a double


// Make level editor
// Make random block level
// Move blocks with hero


using namespace std;

int screenWidth = 1200; 
int screenHeight = 800;

string mystring;
// note that mystring.c_str() converts the C++ string mystring to the C array of characters

Color HexToColour(int hexValue) {
    Color c;
    c.r = (hexValue >> 16) & 0xFF;  // red
    c.g = (hexValue >> 8) & 0xFF;   // green
    c.b = hexValue & 0xFF;          // blue
    c.a = 255;                      // default opaque
    return c;
}

Color rbblack = HexToColour(0x000000);
Color rberaser = HexToColour(0x000001); 
Color rbwhite = HexToColour(0xFFFFFF);
Color rblightblue = HexToColour(0xB5B3F5);
Color rbblue = HexToColour(0x0000FF);
Color rbdarkblue = HexToColour(0x00008B);
Color rblightred = HexToColour(0xFF6666);
Color rbred = HexToColour(0xFF0000);
Color rbdarkred = HexToColour(0x8B0000);
Color rborange = HexToColour(0xFF5900);
Color rblightorange = HexToColour(0xFFD580);
Color rbdarkorange = HexToColour(0xFF8C00);  
Color rblightgreen = HexToColour(0x66C266);
Color rbgreen = HexToColour(0x279627);  
Color rbdarkgreen = HexToColour(0x006400);
Color rblightpink = HexToColour(0xFFD1F0);
Color rbpink = HexToColour(0xF498EC);  
Color rbdarkpink = HexToColour(0xC71585);
Color rblightyellow = HexToColour(0xFFFFE0);
Color rbyellow = HexToColour(0xFFFF00);
Color rbdarkyellow = HexToColour(0xB8860B);  
Color rblightgrey = HexToColour(0xDDDDDD);
Color rbgrey = HexToColour(0xAAAAAA);
Color rbdarkgrey = HexToColour(0x777777);
Color rblightbrown = HexToColour(0xC19153);
Color rbbrown = HexToColour(0x8B4513);
Color rbdarkbrown = HexToColour(0x4C3A23);
Color rblightaqua = HexToColour(0xE0FFFF);
Color rbaqua = HexToColour(0x00FFFF);
Color rbdarkaqua = HexToColour(0x008B8B);
Color rblightpurple = HexToColour(0xE6E6FA);
Color rbpurple = HexToColour(0xBE1CBE);
Color rbdarkpurple = HexToColour(0x4B0082);

Color rbgray1 = HexToColour(0xAAAAAA);
Color rbgray2 = HexToColour(0xCCCCCC);
Color rbgray3 = HexToColour(0xEEEEEE);

Color AllColours[60] = {rblightblue, rbblue, rbdarkblue, rblightred, rbred, rbdarkred, rblightorange, rborange, rbdarkorange,
                       rblightgreen, rbgreen, rbdarkgreen, rblightpink, rbpink, rbdarkpink, rblightyellow, rbyellow, rbdarkyellow,
                       rblightgrey, rbgrey, rbdarkgrey, rblightbrown, rbbrown, rbdarkbrown, rblightaqua, rbaqua, rbdarkaqua,
                       rblightpurple, rbpurple, rbdarkpurple, rbblack, rberaser, rbwhite};                    


int Char1[64] = {1,18,23,23,23,23,18,18,1,18,18,23,23,23,18,18,14,16,16,16,16,16,16,16,17,16,0,0,16,0,0,16,0,16,0,0,16,0,0,16,0,16,16,16,16,16,16,16,0,18,1,1,1,1,17,17,23,23,23,18,18,18,23,23};
int CharBlock[576] = {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19};


int Grid[100][100];
int gridsize = 10;
int gridwidth = 50;
float griddensity = 0.35f;
float herox = (gridsize-1)*gridwidth+(gridwidth-24)/2;
float heroy = (gridsize-1)*gridwidth+(gridwidth-24)/2;


void fillgrid(float density)
{
     for (int i = 0; i < gridsize; i++)
       for (int j = 0; j < gridsize; j++)
       {
          if (GetRandomValue(0,100)/100.0f < density  and i+j != 2*gridsize-2) 
          {
              Grid[j][i] = 1;
          }
       }
}



Color getColour(int myindex)
{
  if ( (myindex >= 1) and (myindex <= 33))
    return AllColours[myindex-1];
  else
    return rbblack; 
}

void drawCharfromArray(int previewx, int previewy, int psize, int bitwidth, int myarray[])
     {
       Color Mycolour;
       int loc = 0;
       for (int i=0;i < bitwidth; i++ )
         for (int j=0; j < bitwidth; j++)
            {
              Mycolour = getColour(myarray[loc]);
              DrawRectangle(previewx+j*psize,previewy+i*psize,psize,psize,Mycolour);
              loc++;
            }        
     }

void drawgrid()
{
     for (int i = 0; i < gridsize; i++)
       for (int j = 0; j < gridsize; j++)
       {
            if ( Grid[j][i] == 1 )
            {
               drawCharfromArray(i*gridwidth, j*gridwidth, 2,24, CharBlock);
            }
       }
}

int main() {
    int c = 0;
    InitWindow(screenWidth, screenHeight, "Blocks");
    Vector2 MousePos;
    SetTargetFPS(60);
    fillgrid(griddensity);
    while (!WindowShouldClose()) 
    {
        if (IsKeyPressed(KEY_SPACE))
        {
             c++;
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
             herox += gridwidth;
        }
        if (IsKeyPressed(KEY_UP))
        {
             heroy -= gridwidth;
        }
        if (IsKeyPressed(KEY_LEFT))
        {
             herox -= gridwidth;
        }
        if (IsKeyPressed(KEY_DOWN))
        {
             heroy += gridwidth;
        }
        if (IsKeyPressed(KEY_ONE))
        {
          c++;
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
         c++;
        }
        BeginDrawing();
        ClearBackground(BLACK); // these two lines MUST go first

        drawgrid(); 
        DrawRectangleLines(0,0,screenWidth,screenHeight,YELLOW);
         MousePos = GetMousePosition();
         DrawText("<Space> - Save",800,200,20, WHITE);
         drawCharfromArray(herox, heroy, 3,8, Char1);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
