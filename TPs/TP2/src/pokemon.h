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


/*
 * Crea el pokemon reservando la memoria necesaria para el.
 * Se le pasa por parametro el nombre del pokemon.
 * Devuelve un puntero al pokemon creado o NULL en caso de no poder crearlo.
 */
pokemon_t* crea_pokemon(char* nombre);

/*
 * Carga el pokemon con todos sus stats, reservando la memoria necesaria para el.
 * Se le pasa por parametro el nombre del pokemon, el nivel, la defensa, la fuerza, la inteligencia y la velocidad.
 * Devuelve un puntero al pokemon cargado o NULL en caso de no poder crearlo.
 */
pokemon_t* cargar_pokemon(char* nombre, size_t nivel, size_t defensa, size_t fuerza, size_t inteligencia, size_t velocidad);


/*
 * Obtiene el nombre del pokemon
 * Se le pasa por parametro el puntero del pokemon.
 * Devuelve un string con su nombre o NULL en caso de que pokemon sea nulo.
 */
char* obtener_nombre(pokemon_t* pokemon);

/*
 * Modifica el nivel del pokemon
 * Se le pasa por parametro el pokemon y el nivel.
 */
void modificar_nivel(pokemon_t* pokemon, size_t nivel);

/*
 * Obtiene el nivel del pokemon
 * Se le pasa por parametro el puntero del pokemon.
 * Devuelve ERROR si pokemon es nulo o retorna el nivel del pokemon.
 */
int obtener_nivel(pokemon_t* pokemon);

/*
 * Modifica la fuerza del pokemon
 * Se le pasa por parametro el pokemon y la fuerza.
 */
void modificar_fuerza(pokemon_t* pokemon, size_t fuerza);

/*
 * Obtiene la fuerza del pokemon
 * Se le pasa por parametro el puntero del pokemon.
 * Devuelve ERROR si pokemon es nulo o retorna la fuerza del pokemon.
 */
int obtener_fuerza(pokemon_t* pokemon);

/*
 * Modifica la inteligencia del pokemon
 * Se le pasa por parametro el pokemon y la inteigencia.
 */
void modificar_inteligencia(pokemon_t* pokemon, size_t inteligencia);

/*
 * Obtiene la inteligencia del pokemon
 * Se le pasa por parametro el puntero del pokemon.
 * Devuelve ERROR si pokemon es nulo o retorna la inteligencia del pokemon.
 */
int obtener_inteligencia(pokemon_t* pokemon);

/*
 * Modifica la velocidad del pokemon
 * Se le pasa por parametro el pokemon y la velocidad.
 */
void modificar_velocidad(pokemon_t* pokemon, size_t velocidad);

/*
 * Obtiene la velocidad del pokemon
 * Se le pasa por parametro el puntero del pokemon.
 * Devuelve ERROR si pokemon es nulo o retorna la velocidad del pokemon.
 */
int obtener_velocidad(pokemon_t* pokemon);

/*
 * Modifica la defensa del pokemon
 * Se le pasa por parametro el pokemon y la defensa.
 */
void modificar_defensa(pokemon_t* pokemon, size_t defensa);

/*
 * Obtiene la defensa del pokemon
 * Se le pasa por parametro el puntero del pokemon.
 * Devuelve ERROR si pokemon es nulo o retorna la defensa del pokemon.
 */
int obtener_defensa(pokemon_t* pokemon);

/*
 * Destruye la estructura pokemon liberando toda la memoria reservada.
 */
void destruye_pokemon(pokemon_t* pokemon);

#endif // POKEMON_H_
