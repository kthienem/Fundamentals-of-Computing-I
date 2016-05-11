#include <stdio.h>
#include <math.h>

/*This program uses ASCII art to draw the graph of the function
 * y = 5.0*(2.0 + cos(2.0*x))*/

int main()
{
	float xmin, xmax;
	float y;
	float ix, iy;
	float ymin, ymax;
	float yminPos, ymaxPos;
	
	xmin = 0.0;
	xmax = 20.0;

	printf("A plot of y = 5*(2 + cos(2*x)) from x = %.1f to %.1f\n",
		 xmin, xmax);	
	printf("    X      Y\n");

	ymin = 5.0*(2.0 + cos(2.0*xmin));
	yminPos = xmin;
	ymax = 5.0*(2.0 + cos(2.0*xmin));
	ymaxPos = xmin;
	/*Set arbitrary min and max values to have a value to compare later
 * 	values to*/

	for (ix = xmin; ix <= xmax; ix += 0.2) {
		y = 5.0*(2.0 + cos(2.0*ix));
		printf("%5.2f%7.2f ", ix, y);

		for ( iy = 0; iy <= y; iy++) {
			printf("#");
		}
		
		printf("\n");

		if (y < ymin) {
			ymin = y;
			yminPos = ix;
		}
		
		else if (y > ymax) {
			ymax = y;
			ymaxPos = ix;
		}
	}
	
	printf("The maximum of %5.2f was at x = %5.2f\n", ymax, ymaxPos);
	printf("The minimum of %5.2f was at x = %5.2f\n", ymin, yminPos);
}
