all: main.c
	cc -o main main.c database.c -lncurses -Wall
	grep -vwE "(short|tvEpisode|tvSeries|tvMovie|tvSpecial|tvShort|tvMiniSeries|video|videoGame)" title.basics.tsv > data.tsv