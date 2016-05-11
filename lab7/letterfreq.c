#include <stdio.h>
#include <ctype.h>

#define reps 7 // the number of letter frequencies that appear on one line

int count(int [], int []);// counts the frequency of letters
void printCount(int []);// prints the results of teh frequency of the letters
void statistics(int []);// prints number of letters, characters, white space and                           percentage of white space
int main()
{
   int alpha[26] = {0}, stats[3] = {0};
   // stats[0] = number of letters
   // stats[1] = number of characters
   // stats[2] = number of white spaces
   count(alpha, stats);
}

int count(int alpha[], int stats[])
{
   char c, filename[20];
   FILE *fp;

   printf("What file would you like to read? ");
   scanf("%s", filename);

   fp = fopen(filename, "r");
   if (!fp){
      printf("There was an error finding file %s\n", filename);
      return 1;
   }

   while (1)
   {
      fscanf(fp, "%c", &c);
      if (feof(fp))
         break;
     
      if (isalpha(c)){
         alpha[tolower(c) - 'a']++;
         stats[0]++;
      }
      else if (isspace(c))
         stats[2]++;

      stats[1]++;
   }
   printCount(alpha);
   statistics(stats);
}

void printCount(int alpha[])
{
   int i, line = 0;
   char letter = 97;// starts at ASCII code of 'a' and increments to print each                        letter
   printf("\nThe letter frequencies are: \n");
   for (i = 0; i <= 25; i++){
      printf("%c:%4i   ", letter,  alpha[i]);
      line++;
      letter++;
      if (line == reps){
         printf("\n");
         line = 0;
      }
   }
   printf("\n\n");
}

void statistics(int stats[])
{
   printf("There are %i letters.\n", stats[0]);
   printf("There are %i characters.\n", stats[1]);
   printf("THere are %i white space characters.\n", stats[2]);
   printf("There is %.1f% white space.\n", ((float)stats[2]/stats[1])*100);
}
