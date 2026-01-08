#include "raylib.h"
#include <string>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>

//compile: g++ LEDcolour.cpp -o LEDcolour -lraylib -lm -ldl -lpthread -lGL -lX11
//run:     ./LEDcolour


// raylib uses float for most numbers, and so use 2.0f to convert int to float. Note that 2.0 will be a double


// Draw eraser with this program!!! store as charEraser
// output as python text

using namespace std;

int screenWidth = 1200; 
int screenHeight = 800;

int Grid[1000][1000];
int Grid2[1000][1000];
int Gridcells = 32;
int cellwidth = (screenHeight-10)/Gridcells;
int startx=6, starty=6;
int count = 0;
int palettex = screenWidth - 3*40-20;
int palettey = 20;
int palcellx = 0;
int palcelly = 0;

string focusfilename = "AAAA";

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
Color rbdarkgrey = HexToColour(0x7777777);
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

string AllColourwords[60] = {"light blue", "blue", "dark blue", "light red", "red", "dark red", "light orange", "orange", 
                       "dark orange","light green", "green", "dark green", "light pink", "pink", "dark pink", "light yellow", 
                       "yellow", "dark yellow", "light grey", "grey", "dark grey", "light brown", "brown", "dark brown", 
                       "light aqua", "aqua", "dark aqua", "light purple", "purple", "dark purple", "black", "eraser", "white"};                       

int selectedcolourindex = 1;

void IncHorFilename()
{
  string s;
  s = focusfilename.substr(2,2);
  if (s[1] < 'Z')
  {
    s[1]++;
  }
  else
  {
    s[1] = 'A';
    if (s[0] < 'Z') {s[0]++;}
  }
  focusfilename[2] = s[0];
  focusfilename[3] = s[1];

}

void IncVertFilename()
{
  string s;
  s = focusfilename.substr(0,2);
  if (s[1] < 'Z')
  {
    s[1]++;
  }
  else
  {
    s[1] = 'A';
    if (s[0] < 'Z') {s[0]++;}
  }
  focusfilename[0] = s[0];
  focusfilename[1] = s[1];

}

void DecHorFilename()
{
  string s;
  s = focusfilename.substr(2,2);
  if (s[1] > 'A')
  {
    s[1]--;
  }
  else
  {
    if (s[0] > 'A') 
    {
      s[0]--;
      s[1] = 'Z';
    }
  }
  focusfilename[2] = s[0];
  focusfilename[3] = s[1];

}

void DecVertFilename()
{
  string s;
  s = focusfilename.substr(0,2);
  if (s[1] > 'A')
  {
    s[1]--;
  }
  else
  {
    if (s[0] > 'A') 
    {
      s[0]--;
      s[1] = 'Z';
    }
  }
  focusfilename[0] = s[0];
  focusfilename[1] = s[1];

}

Color getColour(int myindex)
{
  if ( (myindex >= 1) and (myindex <= 33))
    return AllColours[myindex-1];
  else
    return rbblack; 
}

void DrawGrid()
{
   Color Mycolour;
   Rectangle rec = {startx-3.0f,starty-3.0f,Gridcells*cellwidth+6.0f,Gridcells*cellwidth+6.0f};
   DrawRectangleLinesEx(rec,4,GRAY);
   for (int i = 0; i< Gridcells; i++)
      for (int j = 0; j< Gridcells; j++)
      {
         DrawRectangleLines(startx+i*cellwidth,starty+j*cellwidth,cellwidth,cellwidth,GRAY); 
         if (Grid[j][i] != 0)
         { 
           Mycolour = getColour(Grid[j][i]);
           DrawRectangle(startx+i*cellwidth,starty+j*cellwidth,cellwidth-1,cellwidth-1,Mycolour); 
           if (ColorToInt(Mycolour) == ColorToInt(rbblack))  // cannot compare Colors directly since they are structs
            {
              DrawRectangleLines(startx+i*cellwidth,starty+j*cellwidth,cellwidth-1,cellwidth-1,YELLOW);
            }
         }
      }
}

void DrawPalette()
{
    Color Mycolour;
    for (int i=0;i < 11; i++)
      for (int j=0; j < 3; j++) 
      {
        Mycolour = getColour(i*3+j+1);
         Rectangle rec = {palettex+j*40.0f,palettey+i*40.0f,40.0f,40.0f};
        DrawRectangle(palettex+j*40,palettey+i*40,40,40,Mycolour);
        DrawRectangleLinesEx(rec,2,GRAY);
        if (selectedcolourindex == 1+j+i*3) // this is the selected colour
        { 
          DrawRectangleLinesEx(rec,6,rbgray1);
          DrawRectangleLinesEx(rec,4,rbgray2);
          DrawRectangleLinesEx(rec,3,rbgray3);
        }
        if (ColorToInt(Mycolour) == ColorToInt(rbblack))  // cannot compare Colors directly since they are structs
        {
          DrawRectangleLines(palettex+j*40,palettey+i*40,40,40,YELLOW);
        }
      }
}

void drawCharfromGrid(int previewx, int previewy, int psize)
     {
       Color Mycolour;
       for (int i=0;i < Gridcells; i++ )
         for (int j=0; j < Gridcells; j++)
          if (Grid[j][i] != 0)
            {
              Mycolour = getColour(Grid[j][i]);
              DrawRectangle(previewx+i*psize,previewy+j*psize,psize,psize,Mycolour);
            }        
     }


void ClearGrid()
{
  for (int j = 0; j< Gridcells; j++)
      for (int i = 0; i< Gridcells; i++) 
         Grid[j][i] = 0;
}

void ClearGrid2()
{
  for (int j = 0; j< Gridcells; j++)
      for (int i = 0; i< Gridcells; i++) 
         Grid2[j][i] = 0;
}

void CopyGrid()
{
  ClearGrid2();
  for (int j = 0; j< Gridcells; j++)
      for (int i = 0; i< Gridcells; i++) 
         Grid2[j][i] = Grid[j][i];
}

void PasteGrid()
{
  for (int j = 0; j< Gridcells; j++)
      for (int i = 0; i< Gridcells; i++) 
         if (Grid2[j][i] != 0)
            {Grid[j][i] = Grid2[j][i];}
}

void Outputtofile(string filename)
{
  ofstream outobject(filename); // file writer object --- file closes automatically when out of scope
  if (!outobject)
  {
    cout << "Error: Could not output to file " << filename << "\n";
    return;
  }
  for (int j = 0; j< Gridcells; j++)
      for (int i = 0; i< Gridcells; i++)
      { 
         if (Grid[j][i] != 0)
         {
          outobject << i << " " << j << " " << Grid[j][i] << "\n";
         }
      }
}

void Readfromfile(string filename)
{
  int cellx,celly, value;
  ifstream inobject(filename); // file reader object --- file closes automatically when out of scope
  if (!inobject)
  {
    //cout << "Error: Could not read file " << filename << "\n";
    return;
  }

while (inobject >> cellx >> celly >> value)
 {
  if ( (cellx >= 0) and (celly >= 0) and (cellx < Gridcells) and (celly < Gridcells) )
    {
      Grid[celly][cellx] = value;
    }
 }
}

     
int main() {
    mystring = "Hello there string";
    InitWindow(screenWidth, screenHeight, "LEDColour");
    int cellx, celly;
    Vector2 MousePos;
    SetTargetFPS(60);
    ClearGrid();
    Readfromfile("data/"+focusfilename+to_string(Gridcells)+".txt");
    while (!WindowShouldClose()) 
    {
        if (IsKeyPressed(KEY_SPACE))
        {
             Outputtofile("data/"+focusfilename+to_string(Gridcells)+".txt");
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
             IncHorFilename();
             ClearGrid();
             Readfromfile("data/"+focusfilename+to_string(Gridcells)+".txt");
        }
        if (IsKeyPressed(KEY_UP))
        {
             IncVertFilename();
             ClearGrid();
             Readfromfile("data/"+focusfilename+to_string(Gridcells)+".txt");
        }
        if (IsKeyPressed(KEY_LEFT))
        {
             DecHorFilename();
             ClearGrid();
             Readfromfile("data/"+focusfilename+to_string(Gridcells)+".txt");
        }
        if (IsKeyPressed(KEY_DOWN))
        {
             DecVertFilename();
             ClearGrid();
             Readfromfile("data/"+focusfilename+to_string(Gridcells)+".txt");
        }
        if (IsKeyPressed(KEY_ONE))
        {
          Gridcells = 8;
          cellwidth = (screenHeight-10)/Gridcells;
          focusfilename = "AAAA";
          ClearGrid();
          Readfromfile("data/"+focusfilename+to_string(Gridcells)+".txt");
        }
        if (IsKeyPressed(KEY_TWO))
        {
          Gridcells = 16;
          cellwidth = (screenHeight-10)/Gridcells;
          focusfilename = "AAAA";
          ClearGrid();
          Readfromfile("data/"+focusfilename+to_string(Gridcells)+".txt");
        }
        if (IsKeyPressed(KEY_THREE))
        {
          Gridcells = 24;
          cellwidth = (screenHeight-10)/Gridcells;
          focusfilename = "AAAA";
          ClearGrid();
          Readfromfile("data/"+focusfilename+to_string(Gridcells)+".txt");
        }
        if (IsKeyPressed(KEY_FOUR))
        {
          Gridcells = 32;
          cellwidth = (screenHeight-10)/Gridcells;
          focusfilename = "AAAA";
          ClearGrid();
          Readfromfile("data/"+focusfilename+to_string(Gridcells)+".txt");
        }
        if ( IsKeyPressed(KEY_C) and (IsKeyDown(KEY_LEFT_CONTROL) or IsKeyDown(KEY_RIGHT_CONTROL) ) )
        {
          CopyGrid();
        }
        if ( IsKeyPressed(KEY_V) and (IsKeyDown(KEY_LEFT_CONTROL) or IsKeyDown(KEY_RIGHT_CONTROL) ) )
        {
          PasteGrid();
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
          if (MousePos.x < screenHeight) // draw on grid
          {  
           cellx = (MousePos.x-startx)/cellwidth;
           celly = (MousePos.y-starty)/cellwidth;
           if ( (cellx >= 0) and (celly >= 0) and (cellx < Gridcells) and (celly < Gridcells) )
           {
             if (selectedcolourindex != 32) // 32 is rberaser
                Grid[celly][cellx] = selectedcolourindex;
              else
                Grid[celly][cellx] = 0;  // erased, not black!
             count++;
           }
          }
          else  // choose palette colour
          {
            palcellx = (MousePos.x-palettex)/40;
            palcelly = (MousePos.y-palettey)/40;
            if ( (palcellx >= 0) and (palcelly >= 0) and (palcellx < 3) and (palcelly < 11) )
                  selectedcolourindex = 1+palcellx+palcelly*3;
          }

        }
        BeginDrawing();
        ClearBackground(BLACK); // these two lines MUST go first

         DrawRectangleLines(0,0,screenWidth,screenHeight,YELLOW);
         DrawGrid();
         DrawPalette();
         MousePos = GetMousePosition();
         mystring = "(" +to_string(int(MousePos.x))+", "+to_string(int(MousePos.y))+")";
         DrawText(mystring.c_str(), screenWidth-120, screenHeight-40, 20, BLUE);
         cellx = (MousePos.x-startx)/cellwidth;
         celly = (MousePos.y-starty)/cellwidth;
         mystring = "(" +to_string(cellx)+", "+to_string(celly)+") - "+to_string(count);
         DrawText(mystring.c_str(), screenWidth-120, screenHeight-20, 20, BLUE);
         mystring = "palette=(" +to_string(palcellx)+", "+to_string(palcelly)+")";
         DrawText(mystring.c_str(), screenWidth-180, screenHeight-60, 20, BLUE);
         mystring = "Selected:";
         DrawText(mystring.c_str(), 1061, 474, 20, WHITE);
         mystring = AllColourwords[selectedcolourindex-1];
         DrawText(mystring.c_str(), 1061, 498, 20, WHITE);
         mystring = "File: "+focusfilename+".txt";
         DrawText(mystring.c_str(), 800, 160, 20, WHITE);
         DrawText("<Space> - Save",800,200,20, WHITE);
         DrawText("<Right Arrow> - Next Frame",800,240,10, WHITE);
         DrawText("<Left Arrow> - Previous Frame",800,260,10, WHITE);
         DrawText("<Up Arrow> - Next Picture",800,280,10, WHITE);
         DrawText("<Down Arrow> - Previous Picture",800,300,10, WHITE);
         DrawText("<1,2,3,4> - 8x8, 16x16, 24x24, 32x32",800,320,10, WHITE);
         DrawText("<Ctrl-C> - Copy Frame",800,340,10, WHITE);
         DrawText("<Ctrl-V> - Paste Frame",800,360,10, WHITE);
         drawCharfromGrid(790, 10, 1);
         drawCharfromGrid(790+Gridcells*2, 10, 2);
         drawCharfromGrid(790+Gridcells*2+Gridcells*3, 10, 3);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
