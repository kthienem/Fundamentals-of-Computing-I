#include <stdio.h>
#include "gfx3.h"
#include <math.h>

#define pi 3.14159265
#define width 600
#define length 600

void sierpinski(int, int, int, int, int, int);
void shrinkingSquares(int, int, int);
void spiralSquares(int, int, int, float, int);
void circularLace(int, int, int);
void snowflake(int, int, int);
void tree(int, int, float, int);
void fern(int, int, int, float);

int main()
{
   char c;
   int margin = 20;

   gfx_open(width, length, "Fractals");

   while(1){
      c = gfx_wait();
      switch(c){
         case '1':
            gfx_clear();
            sierpinski(margin, margin, width-margin, margin, width/2, length-margin);
            break;
         case '2':
            gfx_clear();
            shrinkingSquares(width/2-150, length/2-150, 300);
            break;
         case '3':
            gfx_clear();
            spiralSquares(width/2, length/2, 0, 1, 1);
            break;
         case '4':
            gfx_clear();
            circularLace(width/2, length/2, 200);
            break;
         case '5':
            gfx_clear();
            snowflake(width/2, length/2, 200);
            break;
         case '6':
            gfx_clear();
            tree(width/2, length-margin, pi/2, 200);
            break;
         case '7':
            gfx_clear();
            fern(width/2, length-margin, 300, pi/2);
            break;
         default:
            break;
      }
      if (c == 'q') break;
   }
}

void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3)
{
   //Base case
   if (abs(x2-x1) < 3) return;

   //Draw triangle
   gfx_triangle(x1, y1, x2, y2, x3, y3);

   //Recursive calls
   sierpinski(x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2); // use midpoint between verteces for new parameters
   sierpinski((x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2);
   sierpinski((x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3);
}

void shrinkingSquares(int x, int y, int side)
{
   float scale = .45;

   //Base case
   if (side < 3) return;

   //Draw square
   gfx_rectangle(x, y, side, side);

   //Recursive calls
   shrinkingSquares(x-(side*scale/2), y-(side*scale/2), side*scale); // move by half the length of side of new square so center is at vertex
   shrinkingSquares(x-(side*scale/2)+side, y-(side*scale/2), side*scale);
   shrinkingSquares(x-(side*scale/2), y-(side*scale/2)+side, side*scale);
   shrinkingSquares(x-(side*scale/2)+side, y-(side*scale/2)+side, side*scale);
}

void spiralSquares(int x, int y, int r, float theta, int side)
{
   float scale = .061;

   //Base case
   if (x >= width || y >= length || x <= 0 || y <= 0) return;

   //Draw square
   gfx_rectangle(x, y, side, side);

   //Recursive calls
   spiralSquares(x+r*cos(theta), y-r*sin(theta), r+pow(scale*(theta/(pi/5)), 2), theta+(pi/5), side+pow(scale*(theta/(pi/4)),2));
}

void circularLace(int xc, int yc, int r)
{
   int i;
   float scale = .34;

   //Base case
   if (r < 1) return;

   //Draw circle
   gfx_circle(xc, yc, r);

   //Recursive calls
   for (i = 0; i <= 5; i++){
      circularLace(xc+r*cos((2*pi/6)*i), yc-r*sin((2*pi/6)*i), scale*r);
   }
}

void snowflake(int x, int y, int len)
{
   int i;
   int x2, y2;
   float scale = .36;

   //Base case
   if (len < 1) return;

   //Draw line and Recursive calls
   for (i = 0; i <= 4; i++){
      x2 = x+len*cos((2*pi/5)*i-(pi/2));
      y2 = y-len*sin((2*pi/5)*i-(pi/2));
      gfx_line(x, y, x2, y2);
      snowflake(x2, y2, scale*len);
   }
}

void tree(int x, int y, float theta, int len)
{
   int x2, y2;
   float scale = .68;

   x2 = x+len*cos(theta);
   y2 = y-len*sin(theta);

   //Base case
   if (len < 1) return;

   //Draw line
   gfx_line(x, y, x2, y2);

   //Recursive call
   tree(x2, y2, theta+(pi/5), len*scale);
   tree(x2, y2, theta-(pi/5), len*scale);
}

void fern(int x, int y, int len, float theta)
{
   int x2, y2;
   int i;
   float scale = .40;

   x2 = x+len*cos(theta);
   y2 = y-len*sin(theta);

   //Base case
   if (len < 3) return;

   //Draw line
   gfx_line(x, y, x2, y2);

   //Recursive call
   for (i = 0; i <= 3; i++){
      fern(x2-(len/4*i)*cos(theta), y2+(len/4*i)*sin(theta), scale*len, theta+(pi/5));
      fern(x2-(len/4*i)*cos(theta), y2+(len/4*i)*sin(theta), scale*len, theta-(pi/5));
   }
}
