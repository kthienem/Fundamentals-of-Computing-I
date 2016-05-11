#include <stdio.h>
#include "gfx3.h"
#include <math.h>
#include <stdlib.h>

#define pi 3.14159265
#define width 600
#define length 600

void tree(int, int, float, int);

int main()
{
   char c;
   int i;

   gfx_open(width, length, "Gallery");
   srand(time(NULL));

   while (1){
      c = gfx_wait();
      switch(c){
         case 'q':
            break;
         default:
            gfx_clear();
            for (i = 1; i <= 16; i++){
               gfx_color(rand()%255+1, rand()%255+1, rand()%255+1);
               tree(rand()%480+100, rand()%480+100, pi/2, 50);
            }
            break;
      }
      if (c == 'q') break;
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
   tree(x2, y2, theta+(pi/(rand()%(10)+2)), len*scale);
   tree(x2, y2, theta-(pi/(rand()%(10)+2)), len*scale);
}
