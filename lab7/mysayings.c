#include <stdio.h>
#include <string.h>

#define LENGTH 100 // number of rows in sayings array
#define WIDTH 80   // maximum length of a saying

int readFile(char [][WIDTH], FILE *);
void printSayings(char [][WIDTH], int);
int newSaying(char [][WIDTH], int);
void searchWord(char [][WIDTH], int);
void saveSayings(char [][WIDTH], int);

int main()
{
   char sayings[LENGTH][WIDTH];
   char fileIn [40];
   FILE *ifp;// pointer to startup file
   int choice, numSay; // choice is the user's task choice. numSay is the number
                       // of sayings in the array

   printf("Enter startup file: ");
   scanf("%s", fileIn);

   ifp = fopen(fileIn, "r");
   if (!ifp){
      printf("There was an error finding file %s\n", fileIn);
      return 1;
   }

   numSay = readFile(sayings, ifp);
   
   while (choice != 5){
      printf("\nTasks you can perform:\n");
      printf(" 1: show all sayings.\n");
      printf(" 2: enter a new saying.\n");
      printf(" 3: list sayings that contain a given word.\n");
      printf(" 4: save all sayings in a new text file.\n");
      printf(" 5: quit.\n");
      printf("Your choice?: ");
      scanf("%i", &choice);

      switch (choice){
         case 1:
            printSayings(sayings, numSay);
            break;
         case 2:
            numSay = newSaying(sayings, numSay);
            break;
         case 3:
            searchWord(sayings, numSay);
            break;
         case 4:
            saveSayings(sayings, numSay);
            break;
         case 5:
            printf("Goodbye!\n");
            return 0;
         default:
            printf("\nUnknown choice. Try again.\n");
            break;
      }
   }
}

int readFile(char sayings[LENGTH][WIDTH], FILE *ifp)
{
   int i = 0;
   char sentence[WIDTH];
   char *x; // pointer to check return value of fgets

   while (i <= LENGTH){
      x = fgets(sentence, WIDTH, ifp);
      if (!x) // breaks when fgets returns NULL
         break;      
      strcpy(sayings[i], sentence);
      i++;
   }
   return i;
}

void printSayings(char sayings[LENGTH][WIDTH], int n)
{
   int i;

   for (i = 0; i <= n-1; i++){
      printf(" ->%i: %s", i, sayings[i]);
   }
}

int newSaying(char sayings[LENGTH][WIDTH], int n)
{
   char say[WIDTH];

   printf("Enter a new saying: ");
   getchar();// scans \n character from previous line so fgets doesn't terminate
             // early
   fgets(say, WIDTH, stdin);
   strcpy(sayings[n], say);
   return (n+1);
}

void searchWord(char sayings[LENGTH][WIDTH], int n)
{
   int i;
   char word[WIDTH];

   printf("Enter the search word: ");
   scanf("%s", word);

   for (i = 0; i <= n; i++){
      if(strstr(sayings[i], word))
         printf("->%i: %s", i,  sayings[i]);
   }
}

void saveSayings(char sayings[LENGTH][WIDTH], int n)
{
   FILE *ofp; // pointer to new file where saying are saved
   char fileOut[40]; // name of file where new sayings are saved
   int i;

   printf("Enter the name of the file where all sayings will be saved: ");
   scanf("%s", fileOut);

   ofp = fopen(fileOut, "w");

   for (i = 0; i<=n; i++){
      fprintf(ofp, "%s", sayings[i]);
   }
}
