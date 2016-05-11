#include <stdio.h>
#include <string.h>

struct Clues{
   char direction[10];
   int xpos;
   int ypos;
};

void initializeArray(char[][15],int,int);
void userWords(char[][15],int,int,int *);
void makeUpper(char [][15], int, int *);
void sortWords(char[][15],int *,int);
void printClues(char[][15],int,int,int *, struct Clues *, int);
void copyWords(char[][15],char[][15],int *);
void scrambleWords(char[][15], int *);
int generateBoard(char [][15], char[][16], int, int *, struct Clues *);
void poundGrid(char [][16]);
void placeFirstWord(char [][15], char[][16], struct Clues *);
int placeWord(char[][15], char[][16], int *, struct Clues *);
int checkVert(char[][16],char *);
int checkHor(char[][16],char *);
int checkVertSurroundings(char [][16], char *, int, int);
int checkHorSurroundings(char[][16], char *, int, int);

int main()
{
	int wordMax=20, charMax=15;	// array of words(m,n) is size (wordMax,charMax)
	char words[wordMax][charMax], board[15][16];
	int wordCount=0, boardWords;
	int *wc=&wordCount;
	struct Clues clueArray[20];
	struct Clues *p;
	p = clueArray;
	initializeArray(words,wordMax,charMax);	// set array values to zero
	printf("\nHello! Given a list of words, this program will create a blank crossword puzzle with some anagram clues.\n");
	userWords(words,wordMax,charMax,wc);	// get user input words
	makeUpper(words, charMax, wc);
	sortWords(words,wc,charMax);
        boardWords = generateBoard(words, board, charMax, wc, p);
	poundGrid(board);
	printClues(words,wordMax,charMax,wc, p, boardWords);
}

void initializeArray(char words[20][15], int wordMax, int charMax)
{
	int i,j;
	for(i=0;i<=wordMax;i++){
		for(j=0;j<=charMax;j++){
			words[i][j]='\0';
		}
	}
}

void userWords(char words[20][15], int wordMax, int charMax,int *wc)
{
	printf("Please note that you may enter a maximum of 20 words, each no longer than 15 letters.\n");
	printf("What words would you like to use?:\n");
	int i,j;
	char enteredWord[40];
	for(i=1;i<=20;i++){
		scanf("%s",enteredWord);
		if(strlen(enteredWord)>15){
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
	for(i=*wc;i>0;i--){
		for(j=0;j<i;j++){
			if(strlen(words[j])<strlen(words[j+1])){
				strcpy(temp,words[j]);
				strcpy(words[j],words[j+1]);
				strcpy(words[j+1],temp);
			}
		}
	}
}

void printClues(char words[20][15], int wordMax, int charMax, int *wc, struct Clues *p, int wordCount)
{
	int i;
	char anagram[wordMax][charMax];
	copyWords(words, anagram, wc);

	scrambleWords(anagram, wc);
	printf("\nClues:\n\n");
	for (i = 0; i < wordCount; i++){
		printf("%2i,%2i %s %s\n", (*p).xpos, (*p).ypos, (*p).direction, anagram[i]);
		p++;
	}
}

void copyWords(char words[20][15],char anagram[20][15],int *wc)
{
	int i;
	for(i=0;i<=*wc;i++) strcpy(anagram[i],words[i]);
}

void scrambleWords(char anagram[20][15], int *wc)
{
	int i;
	for (i = 0; i < *wc; i++){
		strfry(anagram[i]);
	}
}
int generateBoard(char words[20][15], char board[15][16], int charMax, int *wc, struct Clues *p)
{
   int c, i, j, k, wordCount;

   for (i = 0; i < charMax; i++){
      for (j = 0; j < charMax; j++){
         board[i][j] = '.';
      }
      board[i][charMax] = '\0';
   }
   
   placeFirstWord(words, board, p);

   wordCount = placeWord(words, board, wc, p);
   
   printf("\n\nSolution:\n\n");
   for(k = 0; k < 15; k++){
      printf("%s\n", board[k]);
   }
   return wordCount;
}

void poundGrid(char board[15][16])
{
	int i, j;
	printf("\nCrossword Puzzle:\n\n");
	for (i = 0; i < 15; i++){
		for (j = 0; j < 15; j ++){
			if (board[i][j] == '.')
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
}
   
void placeFirstWord(char words[20][15], char board[15][16], struct Clues *p)
{
   int c, i, j = 0;

   c = 7 - (strlen(words[0])/2);

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
           for(wPos = 0; wPos < strlen(words[i]); wPos++){
            	cfound = strchr(board[bPos], words[i][wPos]);
            	if (cfound != NULL){
			
			vertFull=checkVert(board,cfound);
			horFull=checkHor(board,cfound);
			length=strlen(words[i]);
 
			switch(vertFull+horFull){
				case 1://place horizontally
					inputWord = checkHorSurroundings(board, cfound, length, wPos);
					if (inputWord == 0){
					*(cfound -= wPos);
				        for (j = 0; j < strlen(words[i]); j++){
     						*cfound = words[i][j];
						*(cfound ++);
       					}
					strcpy((*p).direction, "Across");
					(*p).xpos = ((cfound-&board[0][0])%16)+1-length;
					(*p).ypos = bPos + 1;
					}
					else
						cfound = NULL;
					break;
				case 2://place vertically
		        		inputWord = checkVertSurroundings(board, cfound, length, wPos);
					if (inputWord == 0){
					*(cfound -= 16*wPos);
				        for (j = 0; j < strlen(words[i]); j++){
		          			*cfound = words[i][j];
				          	*(cfound += 16);
		       			}
					strcpy((*p).direction, "Down");
					(*p).xpos = ((cfound - &board[0][0])%16)+1;
					(*p).ypos = bPos - wPos + 1;
					}
					else
						cfound = NULL;
					break;
				case 3://both full, dont place
					cfound = NULL;
					break;
				default:
					break;
			}
		}
		if (cfound != NULL) break;
           }
           if (cfound != NULL) break;
        }
       		if(cfound == NULL){
          		printf("%s could not be placed\n", words[i]);
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
	return(vertFull);
}

int checkHor(char board[15][16], char *cfound)
{
	int horFull=0;
	*(cfound++);
	if(isalpha(*cfound)) horFull=2;
	*(cfound-=2);
	if(isalpha(*cfound)) horFull=2;
	*(cfound++);
	return(horFull);
}

int checkHorSurroundings(char board[15][16], char *cfound, int length, int wPos)
{
	int i, availableHor = 0, availableVert = 0, inputWord = 0;
	*(cfound -= wPos);

	for(i = 0; i < length; i++){
		if (i != wPos)
			availableVert = checkVert(board, cfound);
		if (i == 0 || i == (length - 1))
			if (i == (wPos - 1)){
				*(cfound--);
				if(isalpha(*cfound))
					availableHor = 1;
				*(cfound++);
			}
			else if (i == (wPos + 1)){
				*(cfound++);
				if(isalpha(*cfound))
					availableHor = 1;
				*(cfound--);
				
			}
			else
				availableHor = checkHor(board, cfound);
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
	*(cfound -= 16*wPos);

	for(i = 0; i < length; i++){
		if (i != wPos)
			availableHor = checkHor(board, cfound);
		if (i == 0 || i == (length - 1))
			if (i == (wPos - 1)){
				*(cfound -= 16);
				if(isalpha(*cfound))
					availableVert = 1;
				*(cfound += 16);
			}
			else if (i == (wPos + 1)){
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
