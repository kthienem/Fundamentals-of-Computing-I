#include <stdio.h>
#include <math.h>

int main()
{
	printf("This program computes the real roots\n");
	printf("of a quadratic formula.\n");
	printf("Please enter the coefficients of the quadratic formula.\n");

	float a,b,c;

	printf("Enter a: ");
	scanf("%f", &a);

	printf("Enter b: ");
	scanf("%f", &b);

	printf("Enter c: ");
	scanf("%f", &c);

	float root1, root2;

	if ((b*b - 4*a*c) < 0) {
		printf("Answer is imaginary. This program cannot compute\n");
		printf("imaginary roots\n");

		return 0;
	}
	else {

		root1 =(-b + sqrt(b*b - 4*a*c))/(2*a);
		root2 =(-b - sqrt(b*b - 4*a*c))/(2*a);

		printf("The roots are %.2f and %.2f\n", root1, root2);
	}
}
