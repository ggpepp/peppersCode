all: main.c
	cc -std=c11 -o main main.c database.c avlTree.c log.c -lncurses -Wall -g
	#grep -vwE "(short|tvEpisode|tvSeries|tvMovie|tvSpecial|tvShort|tvMiniSeries|video|videoGame)" title.basics.tsv > data.tsv