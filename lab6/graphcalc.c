// Taylor series expansion of sin(x)
#include <stdio.h>
#include "gfx2.h"
#include <math.h>

#define xsize 650
#define ysize 650

char *num2str(int);
void drawAxes(int, int);
void graph(int, int[], int[]); //graphs expansion
void xCoords(int[]);
void compute(int, int[]); // computes y values of Taylor series

int main()
{
   char c;
   int i, j;
   int px = 0, py = 10; // position of numbers on axis
   int terms = 1;
   int ax[xsize], ay[ysize];

   gfx_open(xsize, ysize, "Graphing Calculator");
   
   while (c != 'q'){
      gfx_clear();
      drawAxes(px, py);
      graph(terms, ax, ay);
      gfx_flush();

      c = gfx_wait();
      if (c == '=')
        terms++;
      if (c == '-'){
        terms--;
        if (terms <= 0)
          terms = 1;
      }
   }
}

char *num2str(int n)
{
   static char a[4];
   sprintf(a, "%d", n);
   return (char *) a;
}

void drawAxes(int x, int y)
{
   int i,j;

   gfx_color(255, 255, 255);
   gfx_line(xsize/2, 0, xsize/2, ysize);
   gfx_line(0, ysize/2, xsize, ysize/2);

   for (i = 10; i >= -10; i--){ //draws y axis
         if (i != 0){
         gfx_text(xsize/2 - 20, y, num2str(i));
         gfx_text(xsize/2 - 3, y, "-");
         y += (ysize)/19;
      }
   }

   for (j = -10; j <= 10; j++){ //draws x axis
      if (j != 0){
         gfx_text(x, ysize/2 + 13, num2str(j));
         gfx_text(x, ysize/2 + 3, "|");
         x += (xsize)/19;
      }
   }
}

void graph(int terms, int ax[], int ay[])
{
   int j, k;
   int sum = 0;
   gfx_color(255, 255, 0);  

   compute(terms, ay);
   xCoords(ax);

   for (k = 0; k <= xsize-2; k++){
      gfx_line(ax[k], ay[k], ax[k+1], ay[k+1]);
   }
}

void compute(int terms, int ay[])
{
   int i, j;
   int pos = ysize; // position of element in array ay
   float k;
   double poly = 1, sum = 0;

   for (k = -10; k <=10; k += (20./xsize)){
      for (i = 0; i <= terms-1; i++){
         for (j = 1; j <= (2*i + 1); j++){
            poly *= (k/j);         
         }
         sum += pow(-1, i)*poly;
         poly = 1;
      }
      ay[pos-1] = sum*(ysize/20)+ (ysize/2);
      pos--;
      sum = 0;
   }
}

void xCoords(int ax[])
{
   int i;

   for (i = 1; i <= xsize; i++){
      ax[i-1] = i;
   }
}
