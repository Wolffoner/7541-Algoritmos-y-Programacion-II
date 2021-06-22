CFLAGS=-g -O2 -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes

agenda: agenda.c agenda.h main.c
	gcc $(CFLAGS) agenda.c main.c -o agenda

test: agenda
	valgrind $(VFLAGS) ./agenda
