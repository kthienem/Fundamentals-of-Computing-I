/* Asks users for number of touchdowns, extra points, field goals, and safeties
	scored by the Irish, then computes and displays the total number of
	points scored by the team*/

#include <stdio.h>

int main()
{
	int touchdowns; /*number of touchdowns*/
	int extrapoints; /*number of extra points*/
	int fieldgoals; /*number of field goals*/
	int safeties; /*number of safeties*/
	int score; /*total score of the Irish*/

	printf("How many touchdowns were scored?\n"); 
	scanf("%i", &touchdowns);

	printf("How many extra points were scored?\n");
	scanf("%i", &extrapoints);

	printf("How many field goals were scored?\n");
	scanf("%i", &fieldgoals);

	printf("How many safeties occured?\n");
	scanf("%i", &safeties);

	score = touchdowns*6 + extrapoints + fieldgoals*3 + safeties*2;
	/*total number of points scored by the Irish*/

	printf("The Irish scored %i points!\n", score);
}
