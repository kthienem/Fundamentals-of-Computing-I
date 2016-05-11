#include <stdio.h>
#include<math.h>

int quadrant(float x, float y) {
	int quad;

	if (x > 0 && y > 0){ 
		quad = 1;
		printf("Your coordinate is in the first quadrant\n");
	}
	else if (x < 0 && y > 0){ 
		quad  = 2;
		printf("Your coordinate is in the second quadrant\n");
	}
	else if (x < 0 && y < 0){ 
		quad = 3;
		printf("Your coordinate is in the third quadrant\n");
	}
	else if (x > 0 && y < 0){ 
		quad = 4;
		printf("Your coordinate is in the fourth quadrant\n");
	}
	else if (x == 0 && (y > 0 || y < 0)){ 
		quad = 5;
		printf("Your coordinate is on the y axis\n");
	}
	else if (y == 0 && (x > 0 || x < 0)){ 
		quad = 6;
		printf("Your coordinate is on the x axis\n");
	}
	else if (x == 0 && y == 0){
		quad = 0;
		printf("Your coordinate is at the origin\n");
	}
	return quad;
}

float polarAngle(float x, float y) {
	float angle;
        float pi = 3.14159265359;
	int q; // quadrant condition for switch
	
	angle = atan(y/x)*(180/pi);
	q = quadrant(x, y);
	switch (q) {
	// use switch to adjust angle accordingly depending on quadrant

		case 0:
			angle = 0;
			break;
		case 1:
			angle = angle;
			break;
		case 2:
			angle += 180;
			break;
		case 3:
			angle += 180;
			break;
		case 4:
			angle += 360;
			break;
		case 5:
			if (y > 0)
				angle = 90;
			else if (y < 0)
				angle = 270;
			break;
		case 6:
			if (x > 0)
				angle = 0;
			else if (x < 0)
				angle = 180;
			break;
		}

	return angle;
}

float polarRadius(float x, float y) {
	return sqrt(x*x + y*y);
}

