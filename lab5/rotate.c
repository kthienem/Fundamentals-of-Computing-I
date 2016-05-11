#include <stdio.h>
#include "gfx.h"
#include <math.h>

#define pi 3.14159265

void drawPolygon(int, float);
void color(int);// sets color of polygons

int main()
{
   int xsize = 500, ysize = 500;
   char c;
   float dAngle = 0;
   float shift = .01; // speed of rotation

   printf("This program draws a rotating ferris wheel. The speed can be ");
   printf("changed by pressing\nkeys 1-9, 1 being the slowest and 9 being ");
   printf("the fastest.\n");

   gfx_open(xsize, ysize, "Ferris Wheel");

   while (c != 'q'){
      gfx_clear();
      gfx_color(255, 255, 255);
      gfx_circle(250, 250, 100);
      // draw hexagons around perimeter of circle
      drawPolygon(0, dAngle);
      drawPolygon(1, dAngle);
      drawPolygon(2, dAngle);
      drawPolygon(3, dAngle);
      drawPolygon(4, dAngle);
      drawPolygon(5, dAngle);
      gfx_flush();

      dAngle += shift;

      usleep(10000);
      if (gfx_event_waiting()){
         c = gfx_wait();
         // changes speed of rotation
         if (c == '1')
            shift = 0.01;
         else if (c == '2')
            shift = 0.02;
         else if (c == '3')
            shift = 0.03;
         else if (c == '4')
            shift = 0.04;
         else if (c == '5')
            shift = 0.05;
         else if (c == '6')
            shift = 0.07;
         else if (c == '7')
            shift = 0.07;
         else if (c == '8')
            shift = 0.08;
         else if (c == '9')
            shift = 0.09;
      }
   }
}

void color(int c){
   switch(c){
      case 0:
         gfx_color(255, 0, 0);
         break;
      case 1:
         gfx_color(255, 127, 0);
         break;
      case 2:
         gfx_color(255, 255, 0);
         break;
      case 3:
         gfx_color(0, 255, 0);
         break;
      case 4:
         gfx_color(0, 0, 255);
         break;
      case 5:
         gfx_color(75, 0, 130);
         break;
   }
}

void drawPolygon(int c, float dA){
   int xc, yc;// center of polygons
   int x[5], y[5];
   size_t i, k;
   
   xc = 250 + 100*cos((2*pi/6)*c+dA);
   yc = 250 + 100*sin((2*pi/6)*c+dA);

   color(c);
   for (i = 0; i <= 5; i++){
      x[i] = xc + 25*cos((2*pi/6)*i);
      y[i] = yc + 25*sin((2*pi/6)*i);
   }
   for (k = 0; k <= 4; k++){
      gfx_line(x[k], y[k], x[k+1], y[k+1]);
   }
   gfx_line(x[5], y[5], x[0], y[0]);
}   
