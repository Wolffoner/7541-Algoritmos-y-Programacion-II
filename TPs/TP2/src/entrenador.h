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

/*
 * Crea el entrenador reservando la memoria necesaria para el.
 * Se le pasa por parametro el nombre del entrenador.
 * Devuelve un puntero al entrenador creado o NULL en caso de no poder crearlo.
 */
entrenador_t* crea_entrenador(char* nombre);

/*
 * Carga un entrenador con todos sus atributos: (nombre, victorias, pokemones), reservando la memoria necesaria para el.
 * Se le pasa por parametro el nombre del entrenador, victorias, pokemones.
 * Devuelve un puntero al entrenador cargado o NULL en caso de no poder cargarlo.
 */
entrenador_t* cargar_entrenador(char* nombre, size_t victorias, lista_t* pokemones);

/*
 * Obtiene el nombre del entrenador
 * Se le pasa por parametro el puntero del entrenador.
 * Devuelve un string con su nombre o NULL en caso de que entrenador sea nulo.
 */
char* obtener_nombre_entrenador(entrenador_t* entrenador);

/*
 * Modifica las victorias del entrenador
 * Se le pasa por parametro el entrenador y las victorias.
 * Devuelve ERROR en caso de que no lo haya podido modificar o VALIDO si se pudo modificar correctamente.
 */
int modificar_victorias(entrenador_t* entrenador, size_t victorias);

/*
 * Cantidad de victorias del entrenador.
 * Se le pasa por parametro el entrenador.
 * Devuelve ERROR en caso de que entrenador sea nulo o VALIDO si pudo obtener las victorias del entrenador.
 */
int cantidad_victorias(entrenador_t* entrenador);

/*
 * Cantidad de pokemones del entrenador.
 * Se le pasa por parametro el entrenador.
 * Devuelve ERROR en caso de que entrenador sea nulo o VALIDO si pudo obtener la cantidad de pokemones del entrenador.
 */
int cantidad_pokemones(entrenador_t* entrenador);

/*
 * Modifica la cantidad de pokemones del entrenador
 * Se le pasa por parametro el entrenador y la cantidad de pokemones.
 * Devuelve ERROR en caso de que no lo haya podido modificar o VALIDO si se pudo modificar correctamente.
 */
int modfica_cantidad_pokemones(entrenador_t* entrenador, size_t cantidad_pokemones);

/*
 * Libera pokemon de entrenador
 * Se le pasa por parametro el entrenador y el nombre pokemon.
 * Devuelve ERROR en caso de que no exista el entrenador o no exista el pokemon y VALIDO si se pudo liberar el pokemon.
 */
int liberar_pokemon(entrenador_t* entrenador, char* nombre_pokemon);

/*
 * Obtener pokemon de entrenador
 * Se le pasa por parametro el entrenador y el nombre pokemon.
 * Devuelve NULL en caso de que no exista el entrenador o no exista el pokemon y puntero al pokemon si se pudo obtener el pokemon.
 */
pokemon_t* obtener_pokemon(entrenador_t* entrenador, char* nombre_pokemon);

/*
 * Obtener lista pokemon de entrenador
 * Se le pasa por parametro el entrenador
 * Devuelve NULL en caso de que no exista el entrenador o puntero a lista si se pudo obtener el pokemon.
 */
lista_t* obtener_lista_pokemon(entrenador_t* entrenador);

/*
 * Agregar pokemon a entrenador
 * Se le pasa por parametro el entrenador y el pokemon
 * Devuelve ERROR en caso de que no exista el entrenador o no exita el pokemon y VALIDO si se pudo agregar el pokemon.
 */
int agregar_pokemon(entrenador_t* entrenador, pokemon_t* pokemon);

/*
 * Destruye la estructura entrenador junto con sus pokemones.
 */
void destruye_entrenador(entrenador_t* entrenador);

#endif // ENTRENADOR_H_
