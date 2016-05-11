#include <stdio.h>
#include "gfx.h"
#include <math.h>

#define PI 3.14159265

void blueSquare(void);
void greenTriangle(void);
void whiteCircle(void);
void polygon(int);

int main()
{
   int xsize = 500, ysize = 500;
   char c;

   gfx_open(xsize, ysize, "Symbolic Typewriter");

   while (c != 'q'){
      c = gfx_wait();
      switch(c){
         case 1:
            blueSquare();
            break;
         case 't':
            greenTriangle();
            break;
         case 'c':
            whiteCircle();
            break;
         case '3':
            polygon(3);
            break;
         case '4':
            polygon(4);
            break;
         case '5':
            polygon(5);
            break;
         case '6':
            polygon(6);
            break;
         case '7':
            polygon(7);
            break; 
         case '8':
            polygon(8);
            break;
         case '9':
            polygon(9);
            break;
      }
   }
}

void blueSquare(){
   int centerX = gfx_xpos();
   int centerY = gfx_ypos();
   gfx_color(50, 30, 250);
   
   gfx_line(centerX - 10, centerY - 10, centerX - 10, centerY + 10);
   gfx_line(centerX - 10, centerY + 10, centerX + 10, centerY + 10);
   gfx_line(centerX + 10, centerY + 10, centerX + 10, centerY - 10);
   gfx_line(centerX + 10, centerY - 10, centerX - 10, centerY - 10);
}

void greenTriangle(){
   int centerX = gfx_xpos();
   int centerY = gfx_ypos();
   gfx_color(0, 200, 0);

   gfx_line(centerX, centerY - 10, centerX - 10, centerY + 10);
   gfx_line(centerX - 10, centerY + 10, centerX + 10, centerY + 10);
   gfx_line(centerX + 10, centerY + 10, centerX, centerY - 10);
}

void whiteCircle(){
   gfx_color(255, 255, 255);

   gfx_circle(gfx_xpos(), gfx_ypos(), 10);
}

void polygon(int sides){
   int xc = gfx_xpos();
   int yc = gfx_ypos();
   size_t i, k;
   int x[sides-1], y[sides-1];
   gfx_color(255, 0, 255);
  
   for(i = 0; i <= sides-1; i++){
     x[i] = xc + 15*cos((2*PI/sides)*i);
     y[i] = yc - 15*sin((2*PI/sides)*i);
   }

   for (k = 0; k <= sides-2; k++){
     gfx_line(x[k], y[k], x[k+1], y[k+1]);
   }
   gfx_line(x[sides-1], y[sides-1], x[0], y[0]);;
}
