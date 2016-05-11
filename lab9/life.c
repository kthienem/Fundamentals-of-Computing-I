#include <stdio.h>
#include <ctype.h>

void initializeArrays(char [][41], char [][41]);
void copyGrid(char [][41], char [][41]);
void addCell(char [][41], FILE *, int);
void removeCell(char [][41], FILE *, int);
void advanceSimulation(char [][41], char [][41]);
void applyRules(char [][41], char [][41], int, int, int);
void checkSurroundings(char [][41], char [][41], int, int);

int main(int argc, char *argv[])
{
   char mainGrid[41][41]; //grid that is printed to terminal
   char tempGrid[41][41]; //used to produce next generation
   char choice[3]; //takes in user choice. Use array so that \n is not taken as
                   //an input
   FILE *ifp;

   if (argc > 2){
      printf("Too many arguments were entered in the command line.");
      return 1;
   }

   initializeArrays(mainGrid, tempGrid); // fills both arrays with edge
                                         // markers and blank spaces

   if (argc == 1){
      printf("Welcome to the Game of Life.\nPress the a, r, n, q, and p keys");
      printf(" to play.\n");
      printf("   a - Add cell\n");
      printf("   r - Remove cell\n");
      printf("   n - Advance simulation\n");
      printf("   q - Quit simulation\n");
      printf("   p - Plays simulation continuously. Press ctrl-c to exit\n\n");
   }

   if (argc == 2){
      ifp = fopen(argv[1], "r");
      if (ifp == NULL){
         printf("The input file does not exist.\n");
         return 1;
      }
   }

   while (1){
      printf("Choice: ");
      if (argc == 2)
         fscanf(ifp, "%s", choice);
      else{
         scanf("%s", choice);
      }
      switch (tolower(choice[0])){
         case 'a':
            addCell(mainGrid, ifp, argc);
            break;
         case 'r':
            removeCell(mainGrid, ifp, argc);
            break;
         case 'n':
            advanceSimulation(mainGrid, tempGrid);
            break;
         case 'q':
            break;
         case 'p':
            while (1){
               advanceSimulation(mainGrid, tempGrid);
               usleep(100000);
               system("clear");
            }
            break;
         default:
            printf("That is not a valid choice. Please try again.\n");
            break;
      }
      if (tolower(choice[0]) == 'q') break;
   }
}

void initializeArrays(char mainGrid[41][41], char tempGrid[41][41])
{
   int i, j, k;

//Places edge markers
   mainGrid[0][0] = ' ';
   tempGrid[0][0] = ' ';
   mainGrid[0][1] = '1';
   mainGrid[1][0] = '1';
   tempGrid[0][1] = '1';
   tempGrid[1][0] = '1';

   for (k = 2; k < 41; k++){
      mainGrid[0][k] = '-';
      mainGrid[k][0] = '|';
      tempGrid[0][k] = '-';
      tempGrid[k][0] = '|';
   }

//Fills rest of arrays with blank space
   for (i = 1; i < 41; i++){
      for (j = 1; j < 41; j++){
         mainGrid[i][j] = ' ';
         tempGrid[i][j] = ' ';
      }
   }
}

void addCell(char mainGrid[41][41], FILE *ifp, int argc)
{
   int x, y;

   if (argc == 2)
      fscanf(ifp, "%i %i", &x, &y);
   else{
      printf("Coordinates: ");
      scanf("%i %i", &x, &y);
   }

   if (x >= 1 && y >= 1 && x <= 40 && y <= 40)
      mainGrid[y][x] = 'X';
   else{
      printf("Those are not valid coordinates. Please enter coordinates");
      printf(" between 1 and 40.\n");
   }
}

void removeCell(char mainGrid [41][41], FILE *ifp, int argc)
{
   int x, y;

   if (argc == 2)
      fscanf(ifp, "%i %i", &x, &y);
   else{
      printf("Coordinates: ");
      scanf("%i %i", &x, &y);
   }

   if (x >= 1 && y >= 1 && x <= 40 && y <= 40)
      mainGrid[y][x] = ' ';
   else{
      printf("Those are not valid coordinates. Please enter coordinates");
      printf(" between 1 and 40.\n");
   }
}

void advanceSimulation(char mainGrid[41][41], char tempGrid[41][41])
{
   int i, j;

   for (i = 1; i < 41; i++){
      for (j = 1; j < 41; j++){
         checkSurroundings(mainGrid, tempGrid, i, j);
      }
   }

   copyGrid(mainGrid, tempGrid); //copies next generation into mainGrid

   for (i = 0; i < 41; i++){
      for (j = 0; j < 41; j++){
         printf("%c", mainGrid[i][j]);
      }
      printf("\n");
   }
}

void copyGrid(char mainGrid[41][41], char tempGrid[41][41])
{
   int i, j;

   for (i = 1; i < 41; i++){
      for (j = 1; j < 41; j++){
         mainGrid[i][j] = tempGrid[i][j];
      }
   }
}

void checkSurroundings(char mainGrid[41][41], char tempGrid[41][41], int i, int j)
{
//Checks the 8 surrounding positions of a cell for live cells and counts them
   int liveCells = 0;;

   if ((i-1) >= 1 && (j-1) >= 1 && (i-1) <= 41 && (j-1) <= 40){
      if (mainGrid[i-1][j-1] == 'X') liveCells++;
   }   
   if ((i) >= 1 && (j-1) >= 1 && (i) <= 41 && (j-1) <= 40){
      if (mainGrid[i][j-1] == 'X') liveCells++;
   }   
   if ((i+1) >= 1 && (j-1) >= 1 && (i+1) <= 41 && (j-1) <= 40){
      if (mainGrid[i+1][j-1] == 'X') liveCells++;
   }   
   if ((i-1) >= 1 && (j) >= 1 && (i-1) <= 41 && (j) <= 40){
      if (mainGrid[i-1][j] == 'X') liveCells++;
   }   
   if ((i+1) >= 1 && (j) >= 1 && (i+1) <= 41 && (j) <= 40){
      if (mainGrid[i+1][j] == 'X') liveCells++;
   }   
   if ((i-1) >= 1 && (j+1) >= 1 && (i-1) <= 41 && (j+1) <= 40){
      if (mainGrid[i-1][j+1] == 'X') liveCells++;
   }   
   if ((i) >= 1 && (j+1) >= 1 && (i) <= 41 && (j+1) <= 40){
      if (mainGrid[i][j+1] == 'X') liveCells++;
   }   
   if ((i+1) >= 1 && (j+1) >= 1 && (i+1) <= 41 && (j+1) <= 40){
      if (mainGrid[i+1][j+1] == 'X') liveCells++;
   }  

   applyRules(mainGrid, tempGrid, liveCells, i, j);
}

void applyRules(char mainGrid[41][41], char tempGrid[41][41], int liveCells, int i, int j)
{
   if (mainGrid[i][j] == 'X'){ // applies rules for live cells
      if (liveCells < 2)
         tempGrid[i][j] = ' ';
      else if (liveCells == 2 || liveCells == 3)
        tempGrid[i][j] = 'X';
      else if (liveCells > 3)
         tempGrid[i][j] = ' ';
   }
   else if (mainGrid[i][j] == ' '){ // applies rules for dead cells
      if (liveCells == 3)
         tempGrid[i][j] = 'X';
   }
}
