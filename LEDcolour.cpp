#include "raylib.h"
#include <string>
#include <time.h>
#include <math.h>
#include <iostream>

//compile: g++ LEDcolour.cpp -o LEDcolour -lraylib -lm -ldl -lpthread -lGL -lX11

//To run ./LEDcolour

// raylib uses float for most numbers, and so use 2.0f to convert int to float. Note that 2.0 will be a double

using namespace std;

int screenWidth = 1200; 
int screenHeight = 800;

const int Gridcells = 24;
int Grid[Gridcells][Gridcells];
int cellwidth = (screenHeight-10)/Gridcells;
int startx=6, starty=6;
int count = 0;
int palettex = screenWidth - 300;
int palettey = 20;
int palcellx = 0;
int palcelly = 0;

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
Color rblightblue = HexToColour(0xB5B3F5);
Color rbblue = HexToColour(0x0000FF);
Color rbdarkblue = HexToColour(0x00008B);
Color rblightred = HexToColour(0xFF6666);
Color rbred = HexToColour(0xFF0000);
Color rbdarkred = HexToColour(0x8B0000);

Color AllColours[60] = {rblightblue, rbblue, rbdarkblue, rblightred, rbred, rbdarkred};

int selectedcolourindex = 1;

Color getColour(int myindex)
{
if ((myindex >= 1) and (myindex <= 6) )
   return AllColours[myindex-1];
else
   return rbblack; 
}

void DrawGrid()
{
   Rectangle rec = {startx-2.0f,starty-2.0f,Gridcells*cellwidth+4.0f,Gridcells*cellwidth+4.0f};
   DrawRectangleLinesEx(rec,4,GRAY);
   for (int i = 0; i< Gridcells; i++)
      for (int j = 0; j< Gridcells; j++)
      {
         DrawRectangleLines(startx+i*cellwidth,starty+j*cellwidth,cellwidth,cellwidth,GRAY); 
         if (Grid[j][i] != 0)
         {
           DrawRectangle(startx+i*cellwidth,starty+j*cellwidth,cellwidth-1,cellwidth-1,getColour(Grid[j][i])); 
         }
      }
}

void DrawPalette()
{
    DrawRectangle(palettex,palettey,40,40,rblightblue);
    DrawRectangle(palettex+40,palettey,40,40,rbblue);
    DrawRectangle(palettex+80,palettey,40,40,rbdarkblue);

    DrawRectangle(palettex,palettey+40,40,40,rblightred);
    DrawRectangle(palettex+40,palettey+40,40,40,rbred);
    DrawRectangle(palettex+80,palettey+40,40,40,rbdarkred);

}

int main() {
    mystring = "Hello there string";
    InitWindow(screenWidth, screenHeight, "LEDColour");
    int cellx, celly;
    Vector2 MousePos;
    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
          if (MousePos.x < screenHeight)
          {  
           cellx = (MousePos.x-startx)/cellwidth;
           celly = (MousePos.y-starty)/cellwidth;
           if ( (cellx >= 0) and (celly >= 0) and (cellx < Gridcells) and (celly < Gridcells) )
           {
             Grid[celly][cellx] = selectedcolourindex;
             count++;
           }
          }
          else
          {
            palcellx = (MousePos.x-palettex)/40;
            palcelly = (MousePos.y-palettey)/40;
            selectedcolourindex = 1+palcellx+palcelly*3;
          }

        }
        BeginDrawing();
        ClearBackground(BLACK); // these two lines MUST go first

         DrawGrid();
         DrawPalette();
         MousePos = GetMousePosition();
         mystring = "(" +to_string(MousePos.x)+", "+to_string(MousePos.y)+")";
         DrawText(mystring.c_str(), screenWidth-200, 300, 20, BLUE);
         cellx = (MousePos.x-startx)/cellwidth;
         celly = (MousePos.y-starty)/cellwidth;
         mystring = "(" +to_string(cellx)+", "+to_string(celly)+") - "+to_string(count);
         DrawText(mystring.c_str(), screenWidth-200, 400, 20, BLUE);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
