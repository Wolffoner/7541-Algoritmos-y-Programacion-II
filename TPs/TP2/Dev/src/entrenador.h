#ifndef ENTRENADOR_H_
#define ENTRENADOR_H_

#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "pokemon.h"

typedef struct _entrenador_t entrenador_t;

entrenador_t* crea_entrenador(char* nombre);

entrenador_t* cargar_entrenador(char* nombre, size_t victorias, hash_t* pokemones);

size_t modificar_victorias(entrenador_t* entrenador);

size_t cantidad_victorias(entrenador_t* entrenador);

size_t cantidad_pokemones(entrenador_t* entrenador);

size_t liberar_pokemon(entrenador_t* entrenador, char* nombre_pokemon);

pokemon_t* obtener_pokemon(entrenador_t* entrenador, char* nombre_pokemon);

int agregar_pokemon(entrenador_t* entrenador, pokemon_t* pokemon);

void destruye_entrenador(entrenador_t* entrenador);

#endif // ENTRENADOR_H_
