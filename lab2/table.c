#include <stdio.h>

/*this program takes 2 positive integers and creates a multiplication table that is as big as the entered integers*/

int main()
{
	printf("This program creates a multiplication table based on a user ");
	printf("entered number of\n rows and columns.\n");

	int rows, columns;
	int irow, icolumn;
	int product;

	printf("Enter the number of rows: ");
	scanf("%i", &rows);

	printf("Enter the number of columns: ");
	scanf("%i", &columns);
	
	printf("  * ");
	for (icolumn = 1; icolumn <= columns; ++icolumn) {
		
		printf("%3i ", icolumn);
	}
	printf("\n");
	
	for (irow = 1; irow <= rows; ++irow) {

		printf("%3i ", irow);

		for (icolumn = 1; icolumn <= columns; ++icolumn) {

			product = irow*icolumn;
			printf("%3i ", product);
		}
		
		printf("\n");
	}
}
