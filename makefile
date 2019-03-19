all: main.c
	cc -o main main.c database.c -lncurses -Wall