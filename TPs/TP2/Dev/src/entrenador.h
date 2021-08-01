#ifndef ENTRENADOR_H_
#define ENTRENADOR_H_

#include <stdlib.h>
#include <string.h>
#include "pokemon.h"
#include "lista.h"

#define ERROR -1
#define VALIDO 0
#define IGUALES 0

typedef struct _entrenador_t entrenador_t;

entrenador_t* crea_entrenador(char* nombre);

entrenador_t* cargar_entrenador(char* nombre, size_t victorias, lista_t* pokemones);

char* obtener_nombre_entrenador(entrenador_t* entrenador);

int modificar_victorias(entrenador_t* entrenador, size_t victorias);

int cantidad_victorias(entrenador_t* entrenador);

int cantidad_pokemones(entrenador_t* entrenador);

int modfica_cantidad_pokemones(entrenador_t* entrenador, size_t cantidad_pokemones);

int liberar_pokemon(entrenador_t* entrenador, char* nombre_pokemon);

pokemon_t* obtener_pokemon(entrenador_t* entrenador, char* nombre_pokemon);

int agregar_pokemon(entrenador_t* entrenador, pokemon_t* pokemon);

void destruye_entrenador(entrenador_t* entrenador);

#endif // ENTRENADOR_H_
