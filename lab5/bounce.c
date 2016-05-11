#include <stdio.h>
#include "gfx.h"
#include <stdlib.h>

int main()
{
   int xsize = 500;
   int ysize = 500;
   char c = 1;
   int dx, dy;
   int directionX, directionY; // depending on value, multiply dx and dy by 1 or -1 so the ball can travel in all directions of the screen
   int xc = 250;
   int yc = 250;
   int r = 15; //radius of circle
  
   gfx_open(xsize, ysize, "Bouncing Ball");

   gfx_color(255, 255, 255);
   srand(time(NULL));

   directionX = rand()%2;
   if (directionX == 0)
      dx = -((rand()%10) + 1);
   else
      dx = (rand()%10) + 1;

   directionY = rand()%2;
   if (directionY == 0)
      dy = -((rand()%10) + 1);
   else
      dy = (rand()%10) + 1;

   while (c != 'q'){
      gfx_clear();
      gfx_circle(xc, yc, r);
      gfx_flush();

      if ((xc+r)>xsize){
         xc = xsize - r;
         dx = -dx;
      }
      else if ((xc-r)<0){
         xc = r;
         dx = -dx;
      }
      xc += dx;

      if ((yc+r)>ysize){
         yc = ysize - r;
         dy = -dy;
      }
      else if ((yc-r)<0){
         yc = r;
         dy = -dy;
      }
      yc += dy;

      usleep(10000);
      
      // Processes when user clicks mouse button to redraw circle and give it a new velocity and position
      if (gfx_event_waiting()){
         c = gfx_wait();
         if (c == 1){
            xc = gfx_xpos();
            yc = gfx_ypos();

            directionX = rand()%2;
            if (directionX == 0)
               dx = -((rand()%10) + 1);
            else
               dx = (rand()%10) + 1;

            directionY = rand()%2;
            if (directionY == 0)
               dy = -((rand()%10) + 1);
            else
               dy = (rand()%10) + 1;
         }
      }
   }
}
