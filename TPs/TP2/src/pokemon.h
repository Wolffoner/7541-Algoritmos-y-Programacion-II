#ifndef POKEMON_H_
#define POKEMON_H_

#include <stdlib.h>
#include <string.h>

#define NIVEL_INICIAL 5
#define FUERZA_INICIAL 5
#define INTELIGENCIA_INICIAL 5
#define VELOCIDAD_INICIAL 5
#define DEFENSA_INICIAL 5
#define ERROR -1
#define VALIDO 0

typedef struct _pokemon_t pokemon_t;


pokemon_t* crea_pokemon(char* nombre);

pokemon_t* cargar_pokemon(char* nombre, size_t nivel, size_t defensa, size_t fuerza, size_t inteligencia, size_t velocidad);

char* obtener_nombre(pokemon_t* pokemon);

void modificar_nivel(pokemon_t* pokemon, size_t nivel);

int obtener_nivel(pokemon_t* pokemon);

void modificar_fuerza(pokemon_t* pokemon, size_t fuerza);

int obtener_fuerza(pokemon_t* pokemon);

void modificar_inteligencia(pokemon_t* pokemon, size_t inteligencia);

int obtener_inteligencia(pokemon_t* pokemon);

void modificar_velocidad(pokemon_t* pokemon, size_t velocidad);

int obtener_velocidad(pokemon_t* pokemon);

void modificar_defensa(pokemon_t* pokemon, size_t defensa);

int obtener_defensa(pokemon_t* pokemon);

void destruye_pokemon(pokemon_t* pokemon);

#endif // POKEMON_H_
