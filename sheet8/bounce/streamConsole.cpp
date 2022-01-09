#include <iostream>         // std IO
#include <stdio.h>          // printf()
#include <math.h>           // abs()
#include <stdlib.h>         // exit()
 
using namespace std;
 
// --- --------------------
// --- console canvas class
// --- --------------------
 
class Canvas                    
{
private:
 static const int nColors = 6;
 string forwardColors[6], backwardColors[6];   // ANSI colors
 int dimX, dimY;              // dimensions of drawing panel
 int x, y;                    // current cursor position;
public:
 Canvas()                     // overwriting the default constructor
   {
   cout << "(Canvas): wrong constructor\n"; 
   exit(EXIT_FAILURE);        // exit(0) for success
   }   
 Canvas(int dimX, int dimY)   // regular constructor (to be used)
   {
   this->dimX = dimX;
   this->dimY = dimY;
   forwardColors[0] = "\x1b[30m"; backwardColors[0] = "\x1b[40m";  // black
   forwardColors[1] = "\x1b[31m"; backwardColors[1] = "\x1b[41m";  // red
   forwardColors[2] = "\x1b[32m"; backwardColors[2] = "\x1b[42m";  // green
   forwardColors[3] = "\x1b[33m"; backwardColors[3] = "\x1b[43m";  // yellow
   forwardColors[4] = "\x1b[34m"; backwardColors[4] = "\x1b[44m";  // blue
   forwardColors[5] = "\x1b[37m"; backwardColors[5] = "\x1b[47m";  // white
   x = 0;
   y = 0;
   }
 
 void moveCursor(int deltaX, int deltaY)
   {
   static const string first("\x1b[");
   static const string plusY("A");
   static const string minusY("B");
   static const string plusX("C");
   static const string minusX("D");
   char strDeltaX[50];
   char strDeltaY[50];
   string escapeCharX, escapeCharY;
   sprintf(strDeltaX, "%d",(deltaX>0)?deltaX:(-deltaX)); // write to string 
   sprintf(strDeltaY, "%d",(deltaY>0)?deltaY:(-deltaY)); 
//
   if (deltaX>0)
     escapeCharX = first + strDeltaX + plusX;
   else
     escapeCharX = first + strDeltaX + minusX;
//
   if (deltaY>0)
     escapeCharY = first + strDeltaY + plusY;
   else
     escapeCharY = first + strDeltaY + minusY;
//
   if (deltaX!=0)
     cout << escapeCharX;                // stream control sequence
   if (deltaY!=0)
     cout << escapeCharY;   
   x = x + deltaX;
   y = y + deltaY;
   }
 
 void clearCanvas()
   {
   moveCursor(-x,dimY-y); 
   for (int i=0;i<dimY;i++)
     {
     for (int j=0;j<dimX;j++)
       {
       cout << " ";
       x++;
       }
     moveCursor(-x,-1); 
     }
   }      
 
 void drawBorder()
   {
   moveCursor(-x,dimY-y); 
   cout << backwardColors[4];
   for (int j=0;j<dimX;j++)
     { cout << " "; x++; }
   for (int i=1;i<dimY;i++)
     { moveCursor(-1,-1); cout << " "; x++;}
//
   moveCursor(-x,dimY-y); 
   for (int i=1;i<dimY;i++)
     { cout << " "; x++; moveCursor(-1,-1);}
   for (int j=0;j<dimX;j++)
     { cout << " "; x++; }
//
   cout << "\x1b[0m";          // clear all formatting, if any
   }
 
 void colorText(string text, int color, int xPos, int yPos)
   {
   moveCursor(-x,-y);        // got to lower left corner
   moveCursor(xPos,yPos);    // writing here
   cout << forwardColors[color];
   cout << text ;
   x += text.length();
   cout << "\x1b[0m";          // clear all formatting, if any
   }
 
};        // end of Canvas class
 
// --- ----
// --- main
// --- ----
 
int main()
 {
 cout << "       "; 
//
 Canvas *myCanvas = new Canvas(40,20);
 myCanvas->clearCanvas();
 myCanvas->drawBorder();
 myCanvas->colorText("this is a canvas,",1,5,13);
 myCanvas->colorText("which can be used for",2,5,11);
 myCanvas->colorText("simple animations",3,5,9);
 
 myCanvas->colorText(" ",0,0,0);  // goto orgin
 cout << "\x1b[0m";            // clear all formatting, if any
 
 return 0;
 }
