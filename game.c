#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

void red() {
	printf("\033[1;31m");
}

void yellow() {
	printf("\033[1;33m");
}

void green() {
	printf("\033[0;32m");
}

void white() {
	printf("\033[0;37m");
}

// int strcmp(char *str1, char *str2) {

// }

int inList(char *str1, char **list, int n) {
	// gonna make this faster by using binary search
	for (int i = 0; i < n; i++) {
		if (strcmp(str1,list[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int check(char *str1, char *str3, char **list, int n) {
	// when we return check we will return it with an int value
	// 0 : means invalid word
	// 1 : means good keep going
	// 2: means all green stop game

	// string 2 is the word we are guessing
	// create a copy of the word for checking then if a letter is used use the * emoji to get rid of its use

	char str2[10];
	for (int i = 0; i < 6; i++) {
		str2[i] = str3[i];
	}

	for (int i = 0; i < 5; i++) {
		if (str1[i] == 0) {
			return 0;
		}
		str1[i] = toupper(str1[i]);
	}
	if (str1[5] != 0) {
		return 0;
	}

	if (!inList(str1,list,n)) {
		return 0;
	}


	// Array to decide which color to assign each letter 
	char gyw[5] = {'w','w','w','w','w'};

	// Works
	for (int i = 0; i < 5; i++) {
		//printf("check\n");
		if (str2[i] == str1[i]) {
			//printf("check1\n");
			str2[i] = '*';
			gyw[i] = 'g';
		}
	}
	
	// Working on this
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			//printf("%c : ",str1[i]);
			//printf("%c\n",str2[j]);
			if (i != j && str1[i] == str2[j]) {
				str2[j] = '*';
				gyw[i] = 'y';
				break;
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		if (gyw[i] == 'g'){
			green();
		}
		else if (gyw[i] == 'y') {
			yellow();
		} else {
			white();
		}
		printf("%c",str1[i]);
	}
	
	printf("\n");
	white();

	// check if the whole thing is green
	for (int i = 0; i < 5; i++) {
		if (gyw[i] == 'w' || gyw[i] == 'y') {
			return 1;
		}
	}
	return 2;

}

int main(void) {
	FILE* ptr;
	
	ptr = fopen("words.txt","r");

	if (NULL == ptr) {
		printf("file can't be opened \n");
	}


	// CALLOC STORAGE FOR ALL 2317 WORDS
	char **catalog = (char**)malloc(2317*sizeof(char*));
	for (int i = 0; i < 2317; i++) {
		catalog[i] = (char*)calloc(6,sizeof(char));
	}

	//char output[50];
	char str[100];
	for ( int i = 0; i < 2317; i++) {
		for (int num = 0; num < 6; num++){
			fscanf(ptr,"%s",str);
		}
		//printf("%s\n",str);
		
		// must be pointing to string and not setting it equal
		// set each individual
		for(int x = 0;x < 6; x++) {
			catalog[i][x] = str[x];
		}
		
	}	

	for(int i = 0; i < 2317; i++) {
		//printf("%s\n",catalog[i]);
	}

	srand(time(NULL));
	int number = rand()%2317;
	//char ans[50] = "MONEY";

	char ans[50];
	strcpy(ans,catalog[number]);

	// yellow();
	// printf("%s\n",catalog[number]);
	// green();
	// printf("%s\n",catalog[number]);
	// white();
	// printf("%s\n",catalog[number]);

	char **turn_word = (char**)malloc(5*sizeof(char*));
	for (int i = 0; i < 5; i++) {
		turn_word[i] = (char*)calloc(6,sizeof(char));
	}
	// FIRST ITERATION
	printf("\e[1;1H\e[2J"); 
	printf("----------------------------------------\n");
	printf("HELLO TODAY YOU WILL BE PLAYING WORDLE\n");
	red();
	printf("Please pick your 1st 5 letter word!!\n");
	white();
	int turn = 0;
	

	char in_word[50];
	scanf("%s",in_word);
	

	int j = 0;
	while (in_word[j] != 0) {
		turn_word[turn][j] = in_word[j];
		j++;
	}

	// SECOND ITERATION
	turn = 1;
	int state;
	while (turn < 6) {
		printf("\e[1;1H\e[2J"); 
		printf("\e[1;1H\e[2J"); 
		printf("----------------------------------------\n");
		printf("HELLO TODAY YOU WILL BE PLAYING WORDLE\n");
		red();
		printf("Please pick your 5 letter word!!\n");
		white();
	// print word with all colors included

	//printf("%s\n",in_word);
	//printf("len = %d\n",len(in_word));
		for (int i = 0; i < turn; i++) {
			state = check(turn_word[i],ans, catalog, 2317);
			if (state == 2) {
				turn = 5;
				break;
			}
			if (state == 0) {
				turn -= 1;
			}
		}

		if (turn < 5) {
			scanf("%s",turn_word[turn]);
		}
		turn += 1;
	}
	//scanf("%s",in_word);
	
	if (state == 1) {
		white();
		printf("\nTHE WORD WAS ");
		green();
		printf("\"%s\"",ans);
		white();
		printf(" !!\nTHANKS FOR PLAYING!!\n");
	}

	if (state == 2) {
		white();
		printf("GO OFF !!\n");
	}

	fclose(ptr);
	// free catalog and turn word
	for (int i = 0; i < 5; i++) {
		free(turn_word[i]);
	}
	free(turn_word);
	for ( int i = 0; i < 2317; i++) { 
		free(catalog[i]);
	}
	free(catalog);
	// remember to free all allocated memory
	return 0;
}
