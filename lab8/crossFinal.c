#include <stdio.h>
#include <string.h>

struct Clues{
   char direction[10];
   int xpos;
   int ypos;
}; // structure containing whether a word is across or down, and the grid position of the first letter of the word

void initializeArray(char[][15],int,int);
void userWords(char[][15],int,int,int *);
void fileWords(char [][15],int,int,int *, FILE *);
void makeUpper(char [][15], int, int *);
void sortWords(char[][15],int *,int);
void printClues(char[][15],int,int,int *, struct Clues *, int, FILE *);
void copyWords(char[][15],char[][15],int *);
void scrambleWords(char[][15], int *);
int generateBoard(char [][15], char[][16], int, int *, struct Clues *, FILE *);
void poundGrid(char [][16], FILE *);
void placeFirstWord(char [][15], char[][16], struct Clues *);
int placeWord(char[][15], char[][16], int *, struct Clues *);
int checkVert(char[][16],char *);
int checkHor(char[][16],char *);
int checkVertSurroundings(char [][16], char *, int, int);
int checkHorSurroundings(char[][16], char *, int, int);

int main(int argc, char *argv[])
{
   int wordMax=20, charMax=15;			// array of words(m,n) is size (wordMax,charMax)
   char words[wordMax][charMax], board[15][16];	// array of words for crossword puzzle, array of crossword board
   int wordCount=0, boardWords;
   int *wc=&wordCount;				// number of words entered
   struct Clues clueArray[20];
   struct Clues *p;
   p = clueArray;
   FILE *ofp; 					// file pointer to the output file is a user enters one
   initializeArray(words,wordMax,charMax);	// set array values to zero
   printf("\nHello! Given a list of words, this program will create a blank crossword puzzle with some anagram clues.\n");
   if (argc == 2 || argc == 3){
      FILE *ifp;
      ifp = fopen(argv[1], "r");		// open input file containing list of words for puzzle
      fileWords(words, wordMax, charMax, wc, ifp);// get words from file
   }
   else
      userWords(words,wordMax,charMax,wc);	// get user input words
   makeUpper(words, charMax, wc);		// make input words upper case
   sortWords(words,wc,charMax);			// sort words in order from largest to smallest string
   if (argc == 3){
      ofp = fopen(argv[2], "w");		// open file to output puzzle to
   }
   boardWords = generateBoard(words, board, charMax, wc, p, ofp);	// place words in board and draw crossword solution
   poundGrid(board, ofp);						// draws blank board
   printClues(words,wordMax,charMax,wc, p, boardWords, ofp);		// prints anagrams, word position, and word direction
}

void initializeArray(char words[20][15], int wordMax, int charMax)
{
   int i,j;
   for(i=0;i<=wordMax;i++){
      for(j=0;j<=charMax;j++){
         words[i][j]='\0';	// set array words to NULL
      }
   }
}

void userWords(char words[20][15], int wordMax, int charMax,int *wc)	// words input from user in terminal
{
   printf("Please note that you may enter a maximum of 20 words, each no longer than 15 letters. Enter a period instead of a word to signal the end of the list\n");
   printf("What words would you like to use?:\n");
   int i,j;
   char enteredWord[40];		// 40 bytes allocated for the user entered word so that input does not overflow into unallocated memory
   for(i=1;i<=20;i++){
      scanf("%s",enteredWord);
      if(strlen(enteredWord)>15){	// if the word is too long, do not accept it into the crossword puzzle
         printf("Word entered exceeds character limit of 15, please enter a shorter word.\n");
         for(j=0;j<=charMax;j++) enteredWord[j]='\0';
         i--;
         continue;
      }
      if(enteredWord[0]=='.') break;
      (*wc)++;
      strcpy(words[i],enteredWord);
   }
}

void fileWords(char words[20][15], int wordMax, int charMax,int *wc, FILE *ifp)	// words input from a text file
{
   printf("Please note the a maximum of 20 words will be accepted, each no longer than 15 characters. A period signals end of file input if there are less than 20 words.\n\n");
   int i,j;
   char enteredWord[40];		// 40 bytes allocated for the user entered word so that input does not overflow into unallocated memory
   for(i=1;i<=20;i++){
      fscanf(ifp, "%s", enteredWord);
      if(strlen(enteredWord)>15){	// if the word is too long, do not accept it into the crossword puzzle
         printf("Word in row %i of file was skipped because it was too long.\n", i);
         for(j=0;j<=charMax;j++) enteredWord[j]='\0';
         i--;
         continue;
      }
      if(enteredWord[0]=='.') break;
      (*wc)++;
      strcpy(words[i],enteredWord);
   }
}

void makeUpper (char words[20][15], int charMax, int *wc)
{
   int i, j;
   for (i = 0; i <= *wc; i++){
      for (j = 0; j < charMax; j++){
         words[i][j] = toupper(words[i][j]);
      }
   }
}

void sortWords(char words[20][15], int *wc, int charMax)
{
   int i,j;
   char temp[charMax];
   for (i=*wc;i>0;i--){		// Bubble sort
      for (j=0;j<i;j++){
         if (strlen(words[j])<strlen(words[j+1])){
            strcpy(temp,words[j]);
            strcpy(words[j],words[j+1]);
            strcpy(words[j+1],temp);
         }
      }
   }
}

void printClues(char words[20][15], int wordMax, int charMax, int *wc, struct Clues *p, int wordCount, FILE *ofp)
{
   int i;
   char anagram[wordMax][charMax];	// array of stored anagram clues
   copyWords(words, anagram, wc);
   scrambleWords(anagram, wc);		// jumble letters to create anagrams
   if (ofp == NULL){
      printf("\nClues:\n\n");		// print clues to terminal
      for (i = 0; i < wordCount; i++){
         printf("%2i,%2i %s %s\n", (*p).xpos, (*p).ypos, (*p).direction, anagram[i]);
         p++;
      }
   }
   else{
      fprintf(ofp, "\nClues:\n\n");	// print clues to file
      for (i = 0; i < wordCount; i++){
         fprintf(ofp, "%2i,%2i %s %s\n", (*p).xpos, (*p).ypos, (*p).direction, anagram[i]);
         p++;
      }
   }
}

void copyWords(char words[20][15],char anagram[20][15],int *wc)
{
   int i;
   for(i=0;i<=*wc;i++) strcpy(anagram[i],words[i]);	// store list of words in anagram array
}

void scrambleWords(char anagram[20][15], int *wc)
{
   int i;
   for (i = 0; i < *wc; i++){
      strfry(anagram[i]);	// jumbles letters to create anagrams
   }
}

int generateBoard(char words[20][15], char board[15][16], int charMax, int *wc, struct Clues *p, FILE *ofp)
{
   int c, i, j, k, wordCount;
   for (i = 0; i < charMax; i++){
      for (j = 0; j < charMax; j++){
         board[i][j] = '.';			// fill board with periods
      }
      board[i][charMax] = '\0';			// adds a null character to the end of each row to signal end of string 
   }
   placeFirstWord(words, board, p);		// place longest word horizontally in center of the board
   wordCount = placeWord(words, board, wc, p);	// place remaining words in decreasing order of size until one cannot fit on board
   if (ofp == NULL){
      printf("\n\nSolution:\n\n");		// print board to terminal
      for(k = 0; k < 15; k++){
         printf("%s\n", board[k]);
      }
   }
   else{
      fprintf(ofp, "Solution:\n\n");		// print board to file
      for(k = 0; k < 15; k++){
         fprintf(ofp, "%s\n", board[k]);
      }
   }
   return wordCount;
}

void poundGrid(char board[15][16], FILE *ofp)
{
   int i, j;

   if (ofp == NULL){
      printf("\nCrossword Puzzle:\n\n");	// prints #'s to terminal
      for (i = 0; i < 15; i++){
         for (j = 0; j < 15; j ++){
            if (board[i][j] == '.')
               printf("#");			// fill board with #'s unless a word has been placed there in crossword puzzle
            else
               printf(" ");
         }
         printf("\n");
      }
   }
   else{
      fprintf(ofp, "\nCrossword Puzzle:\n\n");	// prints #'s to terminal
      for (i = 0; i < 15; i++){
         for (j = 0; j < 15; j ++){
            if (board[i][j] == '.')
               fprintf(ofp, "#");		// fill board with #'s unless a word has been placed there in crossword puzzle
            else
               fprintf(ofp, " ");
         }
         fprintf(ofp, "\n");
      }
   }
}
   
void placeFirstWord(char words[20][15], char board[15][16], struct Clues *p)
{
   int c, i, j = 0;
   c = 7 - (strlen(words[0])/2);	// x location of first character of first word placed horizontally in center
   for (i = c; i < (c + strlen(words[0])); i++){
      board[7][i] = words[0][j];
      j++;
   }   
   strcpy((*p).direction, "Across");
   (*p).xpos = c + 1;
   (*p).ypos = 8;
}

int placeWord(char words[20][15], char board[15][16], int *wc, struct Clues *p)
{
   int i, wPos, bPos, j, vertFull, horFull, length, inputWord;
   char *cfound;
   p++;
   for (i = 1; i < *wc; i++){
      for (bPos = 0; bPos < 15; bPos++){
         for (wPos = 0; wPos < strlen(words[i]); wPos++){
            cfound = strchr(board[bPos], words[i][wPos]);
            if (cfound != NULL){
               vertFull=checkVert(board,cfound);	// returns 1 if immediately above or below matching character is occupied
               horFull=checkHor(board,cfound);		// returns 2 if immediately right or left of matching character is occupied
               length=strlen(words[i]);
               switch(vertFull+horFull){
                  case 1://place horizontally
                     inputWord = checkHorSurroundings(board, cfound, length, wPos);	// checks if other placed words will interfere with placement
                     if (inputWord == 0){
                        *(cfound -= wPos);
                        for (j = 0; j < strlen(words[i]); j++){				// place new word
                           *cfound = words[i][j];
                           *(cfound ++);
                        }
                        strcpy((*p).direction, "Across");
                        (*p).xpos = ((cfound-&board[0][0])%16)+1-length;
                        (*p).ypos = bPos + 1;
                     }
                     else
                        cfound = NULL;							// dont place new word, continue checking elsewhere
                     break;
                  case 2://place vertically
                     inputWord = checkVertSurroundings(board, cfound, length, wPos);	// checks if other placed words will interfere with placement
                     if (inputWord == 0){
                        *(cfound -= 16*wPos);
                        for (j = 0; j < strlen(words[i]); j++){				// place new word
                           *cfound = words[i][j];
                           *(cfound += 16);
                        }
                        strcpy((*p).direction, "Down");
                        (*p).xpos = ((cfound - &board[0][0])%16)+1;
                        (*p).ypos = bPos - wPos + 1;
                     }
                     else
                        cfound = NULL;							// dont place new word
                     break;
                  case 3://both full, dont place
                     cfound = NULL;
                     break;
                  default:
                     break; 
               }
            }
            if (cfound != NULL) break;	// word has been placed, do not continue checking for matching characters
         }
         if (cfound != NULL) break;	// word has been placed, do not continue checking for matching characters
      }
      if(cfound == NULL){
         printf("\n%s could not be placed\n", words[i]);
         break;
      }
      p++;
   }
   return i;
}

int checkVert(char board[15][16], char *cfound)
{
   int vertFull=0;
   *(cfound-=16);
   if(isalpha(*cfound)) vertFull=1;
   *(cfound+=32);
   if(isalpha(*cfound)) vertFull=1;
   *(cfound-=16);
   return(vertFull);	// return 1 if immediately above or below position in board is full
}

int checkHor(char board[15][16], char *cfound)
{
   int horFull=0;
   *(cfound++);
   if(isalpha(*cfound)) horFull=2;
   *(cfound-=2);
   if(isalpha(*cfound)) horFull=2;
   *(cfound++);
   return(horFull);	// return 2 if immediately to the right or left of the position in board is full
}

int checkHorSurroundings(char board[15][16], char *cfound, int length, int wPos)
{
   int i, availableHor = 0, availableVert = 0, inputWord = 0;
   *(cfound -= wPos);
   
   for(i = 0; i < length; i++){
      if (i != wPos)
         availableVert = checkVert(board, cfound);	// if the word is being placed horizontally, check above and below every position a character of the word would potentially be placed
      if (i == 0 || i == (length - 1)){			// if it is the first or last character...
         if (i == (wPos - 1)){					// if it is one space away from the intersecting character, do not check location of intersecting character, and only check the side opposite
            *(cfound--);
            if(isalpha(*cfound))
               availableHor = 1;
            *(cfound++);
         }
         else if (i == (wPos + 1)){				// if it is one space away from the intersecting character, do not check location of intersecting character, and only check the side opposite
            *(cfound++);
            if(isalpha(*cfound))
               availableHor = 1;
            *(cfound--);
         }
         else
            availableHor = checkHor(board, cfound);
      }
      if ((availableVert + availableHor) > 0){
         inputWord = 1;
         break;
      }
      if (*cfound != '.' && i != wPos){
         inputWord = 1;
         break;
      }
      *(cfound++);    
   }
   *(cfound -= i);
   return(inputWord);
}


int checkVertSurroundings(char board[15][16], char *cfound, int length, int wPos)
{
	int i, availableHor = 0, availableVert = 0, inputWord = 0;
	*(cfound -= 16*wPos);					// rows are 16 characters long, so maneuver vertically by adding/subtracting in increments of 16

	for(i = 0; i < length; i++){
		if (i != wPos)
			availableHor = checkHor(board, cfound);	// if the word is being placed vertically, check to the right and left of every position a character of the word would potentially be placed
		if (i == 0 || i == (length - 1))			// if it is the first or last character...
			if (i == (wPos - 1)){					// if it is one space away from the intersecting character, do not check location of intersecting character, and only check the side opposite
				*(cfound -= 16);
				if(isalpha(*cfound))
					availableVert = 1;
				*(cfound += 16);
			}
			else if (i == (wPos + 1)){				// if it is one space away from the intersecting character, do not check location of intersecting character, and only check the side opposite
				*(cfound += 16);
				if(isalpha(*cfound))
					availableVert = 1;
				*(cfound -= 16);
			}
			else
				availableVert = checkVert(board, cfound);
		if ((availableVert + availableHor) > 0){
			inputWord = 1;
			break;
		}
		if (*cfound != '.' && i != wPos){
			inputWord = 1;
			break;
		}
		*(cfound += 16);
	}
	*(cfound -= 16*i);
	return(inputWord);
}
