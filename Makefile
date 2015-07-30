all:
	gcc -ggdb -lm -lpng -o zordview zordinate.c zordview.c

test:
	gcc -ggdb -lm -o test zordinate.c test.c
