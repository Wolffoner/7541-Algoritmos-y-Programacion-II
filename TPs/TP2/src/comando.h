#ifndef COMANDO_H_
#define COMANDO_H_

#include <stdlib.h>
#include "hash.h"

#define ERROR -1

typedef struct _comando_t comando_t;

/* 
 * Ejecutar comando almacenado en la estructura comando.
 * Se le pasan 3 parametros al ejecutar.
*/
typedef void (*ejecutar_comando_t)(void*, char**, void*);

/*
 * Crea el comando reservando la memoria necesaria para el.
 * ejecutar es el comando que se utilizara para ejecutar el mismo.
 * Devuelve un puntero al comando creado o NULL en caso de no poder
 * crearlo.
 */
comando_t* comando_crear(const char* nombre, const char* descripcion, void (*ejecutar_comando_t)(void* salon, char** args, void* contexto));

/*
 * Obtiene el nombre del comando
 * Devuelve un string con el nombre de comando o NULL en caso de que el comando sea nulo.
 */
char* obtener_nombre_comando(comando_t* comando);

/*
 * Obtiene la descripcion del comando
 * Devuelve un string con la descripcion del comando o NULL en caso de que el comando sea nulo.
 */
char* obtener_descripcion_comando(comando_t* comando);

/*
 * Obtiene el ejecutar del comando
 * Devuelve el ejecutar del comando o NULL en caso de que el comando sea nulo.
 */
ejecutar_comando_t obtener_ejecutar_comando(comando_t* comando);

/*
 * Destruye el comando liberando la memoria reservada.
 */
void comando_destruir(comando_t* comando);

#endif /* COMANDO_H_ */
