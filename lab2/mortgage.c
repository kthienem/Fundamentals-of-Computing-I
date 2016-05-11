#include <stdio.h>

/*This program takes in a user inputed principal, interest rate, and monthly
 * payment and then calculates how long it will take to pay off the mortgage 
 * and how much money is spent over that period. It displays a table showing
 * the month, your monthly payment, the interest added to the total, and the
 * balance for every month. Once the balance reaches zero, it diplays how much
 * was spent and how long it took to pay off. */

int main()
{
	float principal, interestRate, monthlyPayment;
	float balance;
	float interest;
	int month;
	int months;
	int years;
	float totalPaid;

	printf("This program calculates the amount of time taken to pay off");
	printf(" a mortgage and\n how much money you actually pay.\n");

	printf("How much is your principal($)? ");
	scanf("%f", &principal);
	if (principal < 0) {
		printf("You cannot have a negative principal. Please try ");
		printf("again: ");
		scanf("%f", &principal);
	}

	printf("What is your annual interest rate(%)? ");
	scanf("%f", &interestRate);
	if (interestRate < 0) {
		printf("You cannot have a negative interest rate. Please try ");
		printf("again: ");
		scanf("%f", &interestRate);
	}
	if (interestRate > 100) {
		printf("You cannot have an interest rate greater than 100  ");
		printf("percent. Please try again: ");
		scanf("%f", &interestRate);
	}

	printf("What is your monthly payment($)? ");
	scanf("%f", &monthlyPayment);
	if (monthlyPayment < 0) {
		printf("You cannot have a negative monthly payment. Please ");
		printf("try again: ");
		scanf("%f", &monthlyPayment);
	}

	balance = principal;
	month = 0;
	printf("Month     Payment     Interest     Balance\n");

	while (balance > 0) {
		++month;
		interest = balance*(interestRate/(100*12));
		 /*Dividing the interest rate by 100 changes it to deciaml form.			 Dividing by 12 gives the monthly interest rate*/

		if (interest >= monthlyPayment) {
			printf("The monthly payment is too small. At your ");
			printf("current interest rate the\n balance due will ");
			printf("continue to increase.\n");
			return 0;
		}

		balance += interest;
		if (monthlyPayment > balance) {
			monthlyPayment = balance;
		}

		balance -= monthlyPayment;

		printf("%-5i     $%6.2f", month, monthlyPayment);
		printf("     $%7.2f     $%8.2f\n",interest, balance);
		totalPaid += monthlyPayment;
	}
	
	years = month/12;
	months = month%12;

	printf("You paid a total of %.2f over %i years", totalPaid, years);
	printf(" and %i months.\n", months);	
}
