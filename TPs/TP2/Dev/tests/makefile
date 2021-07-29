CFLAGS=-g -O2 -std=c99 -Wall -Wconversion -Wtype-limits -Werror -I ../src 
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2

valgrind: pruebas_pokemon
	valgrind $(VFLAGS) ./pruebas_pokemon 2>&1

pruebas_pokemon: pruebas_pokemon.c ../src/*
	gcc $(CFLAGS) -o pruebas_pokemon pruebas_pokemon.c ../src/* 2>&1

clean:
	rm pruebas_pokemon 2>&1
