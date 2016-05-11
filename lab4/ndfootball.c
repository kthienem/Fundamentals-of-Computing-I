#include <stdio.h>
#include "nd_data.h"

void record(void);
void numberofWins(void);
void undefeatedSeasons(void);

int main()
{
   int option;

   printf("This program is used to extract information from Notre Dame's ");
   printf("football history. There are three facts that this program can");
   printf(" retrieve:\n");
   printf("Press 1 to incquire about a given years record.\n");
   printf("Press 2 to incquire about what years the team had a given number ");
   printf("of wins.\n");
   printf("Press 3 to incquire about what years the team went undefeated.\n");
   printf("Press 0 to exit the program.\n");

   while (1){
      printf("What would you like to know? ");
      scanf("%i", &option);

      switch (option){
         case 0:
            return 0;
         case 1:
            record();
            break;
         case 2:
            numberofWins();
            break;
         case 3:
            undefeatedSeasons();
            break;
         default:
            printf("That is not an option. Please select 1, 2, 3, or 0.\n");
            printf("What would you like to know? ");
            scanf("%i", &option);
            break;
      }   
   }
}

void record(void){
   int year;
   int yearArray;
   int w; // wins
   int l; // losses
   int n = sizeof(wins)/sizeof(wins[0]);

   printf("What year would you like to know the record for: ");
   scanf("%i", &year);

   yearArray = year - 1900;
    // subtract 1900 to use for accessing point in the arrays
   
   if (yearArray < 0 || yearArray > (n - 1)){
      printf("That is not a valid year. Please enter a year between 1900 and");
      printf(" the year of the\n most recent completed season\n");
   }
   else{
      w = wins[yearArray];
      l = losses[yearArray];

      printf("The record for %i was %i-%i\n", year, w, l);
   }
}

void numberofWins(void){
   int w; // number of wins
   int year;
   int j = 0;// allows for the statement to be printed only once and only when
             // there exists years with the given number of wins
   int i = 0; // used to keep track of number years without given number of wins
   size_t k; // loop counter for array position
   int n = sizeof(wins)/sizeof(wins[0]);
    // determines the number of elements in the array

   printf("Enter a number of wins to find the years where Notre Dame ");
   printf("had a record with\n that many wins.\n");

   printf("Enter a number of wins: ");
   scanf("%i", &w);

   for (k = 0; k < n; ++k){
      if (wins[k] == w){
         if (j == 0){
            printf("The years where Notre Dame had %i wins are:\n", w);
         }
         year = k + 1900;
         printf("%i\n", year);
         ++j;       
      }
      else if (wins[k] != w){
         ++i;
      }
   }
   if (i == n){
      printf("There are no years with %i wins.\n", w);
   }
   else{
      printf("There are %i years where Notre Dame had %i wins.\n", j, w);
   }
}

void undefeatedSeasons(void){
   int year;
   size_t k; // loop counter for array position
   int j = 0; // counts number of undefeated seasons
   int n = sizeof(losses)/sizeof(losses[0]);
   // determines the number of elements in the array

   printf("The years when Notre Dame went undefeated are:\n");
   for (k = 0; k < n; ++k){
      if (losses[k] == 0){
         year = k + 1900;
         printf("%i\n", year);
         ++j;
      }
   }

   printf("There are %i undefeated seasons.\n", j);
}
