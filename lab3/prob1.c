#include <stdio.h>

int getgcd(int, int); /*Function prototype*/

int main()
{
	int number1, number2;
	int gcd;

	printf("Enter two integers: ");
	scanf("%i %i", &number1, &number2);

	gcd = getgcd(number1, number2);

	printf("The greatest common divisor of %i and ", number1);
	printf("%i is: %i\n", number2, gcd);
}

int getgcd(int x, int y) {
	int gcd;

	while (x != y) {
		if (x > y)
			x -= y;
		else
			y -= x;
	}

	gcd = x;
	return gcd;
}
