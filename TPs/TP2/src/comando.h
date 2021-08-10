#ifndef COMANDO_H_
#define COMANDO_H_

#include <stdlib.h>
#include "hash.h"

#define ERROR -1

typedef struct _comando_t comando_t;

typedef void (*ejecutar_comando_t)(void*, char**, void*);

comando_t* comando_crear(const char* nombre, const char* descripcion, void (*ejecutar_comando_t)(void* salon, char** args, void* contexto));

char* obtener_nombre_comando(comando_t* comando);

char* obtener_descripcion_comando(comando_t* comando);

int cant_argumentos_comando(comando_t* comando);

ejecutar_comando_t obtener_ejecutar_comando(comando_t* comando);

//void comando_procesar(hash_t comandos, char* comando, void* resultado);

void comando_destruir(comando_t* comando);

#endif /* COMANDO_H_ */
