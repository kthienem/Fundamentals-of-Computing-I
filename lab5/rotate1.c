#include <stdio.h>
#include "gfx.h"
#include <math.h>

void drawShip(int, int, float);
void color(int);

#define xsize 500
#define ysize 500
#define pi 3.14159265

int main()
{
   char c;
   int xc = 250, yc = 250;
   float dAngle = 0;
   int dx, dy, dVx = 0, dVy = 0;

   gfx_open(xsize, ysize, "Spaceship");
   
   printf("This program allows you to fly a spaceship around the screen using ");
   printf("the WASD keys.\n");
   printf("Press A and D to turn the ship left and right respectively.\n");
   printf("Press W and S to accelerate and brake the ship respectively.\n");

   while (c != 'q'){
      gfx_clear();
      drawShip(xc, yc, dAngle);
      gfx_flush();
 
      dy = -1 + dVy;
      yc += dy;
      
      if (gfx_event_waiting){
         c = gfx_wait();
            if (c == 'a')
               dAngle += 1/(2*pi);
            else if (c == 'd')
               dAngle -= 1/(2*pi);
            else if (c == 'w')
               dVy = -1;
            else if (c == 's')
               dVy = 1;
      }
   }
}

void drawShip(int x, int y, float dA){
   float r = 15;
   float xAngle, yAngle;

   if (x <= 20 || x >= xsize - 20 || y < 20 || y >= ysize - 20)
      color(2);
   else 
      color(1);

   xAngle = cos((pi/2)+dA);
   yAngle = sin((pi/2)+dA);

   gfx_line(x + r*xAngle, y - r*yAngle, x - r*yAngle, y + r*yAngle);
   gfx_line(x - r*yAngle, y + r*yAngle, x, y);
   gfx_line(x, y, x + r*yAngle, y + r*yAngle);
   gfx_line(x + r*yAngle, y + r*yAngle, x + r*xAngle, y - r*yAngle);
}

void color(int c){
   switch(c){
      case 1:
         gfx_color(95, 158, 160);
         break;
      case 2:
         gfx_color(255, 0, 0);
         break;
   }
}
