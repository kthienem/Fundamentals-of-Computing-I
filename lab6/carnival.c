#include <stdio.h>
#include "gfx2.h"
#include <math.h>

#define xsize 650
#define ysize 650
#define pi 3.14159265

void square(int, float);
void spinArm(int, float);
void wheel(int, int, float);
void piston(int, int);
void color(char);

int main()
{
   char c;
   int xc = 150;
   int dx = 1; //change in position of slider
   float dA = 0; //change in angle of rotating objects
   int dR = 1; //change in radius of oscillating circle
   int radius = 1; // radius of oscillating circle

   gfx_open(xsize, ysize, "Carnival Ride");

   while (c != 'q'){
      gfx_clear();
      square(xc, dA);
      color('c');
      gfx_circle(xc, (ysize/2), radius);
      gfx_flush();
   
      usleep(10000);
      
      if (xc < 150)
         dx *= -1;
      else if ( xc > (xsize - 150))
         dx *= -1;

      xc += dx;
      dA += .01;

      if (radius >= 100)
        dR *= -1;
      if (radius < 1)
        dR *= -1;

      radius += dR;
      
      if (gfx_event_waiting()){
         c = gfx_wait();
      }
   }
}

void square(int xc, float dA)
{
   size_t i, k;
   int x[3], y[3];
   color('s');

   for (i = 0; i <= 3; i++){
      x[i] = xc + 15*cos((2*pi/4)*i + (pi/4));
      y[i] = (ysize/2) -  15*sin((2*pi/4)*i + (pi/4));
   }

   for (k = 0; k <= 2; k++){
      gfx_line(x[k], y[k], x[k+1], y[k+1]);
   }
   gfx_line(x[3], y[3], x[0], y[0]);
   
   spinArm(xc, dA);
}

void spinArm(int xc, float dA)
{
   int x2, y2;
   color('a');

   x2 = xc + 125*cos(dA);
   y2 = (ysize/2) + 125*sin(dA);
   
   gfx_line(xc, (ysize/2), x2, y2);

   wheel(x2, y2, dA);
}

void wheel(int x2, int y2, float dA)
{
   int i;
   int x3, y3;

   for (i = 1; i <= 4; i++){
      color('w');
      x3 = x2 + 30*cos((2*pi/4)*i + 2*dA);
      y3 = y2 + 30*sin((2*pi/4)*i + 2*dA);
      gfx_line(x2, y2, x3, y3);
      piston(x3, y3);
   }
}

void piston(int x3, int y3)
{
   color('p');

   gfx_circle(x3, y3, 10);
}

void color(char c)
{
   switch (c){
      case 'a':
         gfx_color(255, 255, 0);
         break;
      case 's':
         gfx_color(0, 255, 0);
         break;
      case 'c':
         gfx_color(255, 0, 0);
         break;
      case 'w':
         gfx_color(0, 0, 255);
         break;
      case 'p':
         gfx_color(255, 0, 255);
   }
}  
