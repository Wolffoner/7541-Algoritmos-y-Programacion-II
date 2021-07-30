CFLAGS=-g -O2 -std=c99 -Wall -Wconversion -Wtype-limits -Werror -I ../src 
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2

valgrind_p: pruebas_pokemon
	valgrind $(VFLAGS) ./pruebas_pokemon 2>&1

valgrind_e: pruebas_entrenador
	valgrind $(VFLAGS) ./pruebas_entrenador 2>&1

pruebas_pokemon: pruebas_pokemon.c ../src/*
	gcc $(CFLAGS) -o pruebas_pokemon pruebas_pokemon.c ../src/* 2>&1

pruebas_entrenador: pruebas_entrenador.c ../src/*
	gcc $(CFLAGS) -o pruebas_entrenador pruebas_entrenador.c ../src/* 2>&1

clean:
	rm pruebas_pokemon pruebas_entrenador 2>&1
