
Wordle : game.o
	gcc -std=c17 -Wall -o Wordle game.o

game.o : game.c
	gcc -std=c17 -Wall -c game.c