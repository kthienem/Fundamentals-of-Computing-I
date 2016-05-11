#include <stdio.h>
#include "part2fn.h"

int main()
{
   float xcoord, ycoord;
   float pRadius;
   float pAngle;

   printf("Enter your x and y coordinates: ");
   scanf("%f %f", &xcoord, &ycoord);

   pAngle = polarAngle(xcoord, ycoord);
   pRadius = polarRadius(xcoord, ycoord);

   printf("The polar coordinates are (%.2f, %.2f deg)\n", pRadius, pAngle);
}
