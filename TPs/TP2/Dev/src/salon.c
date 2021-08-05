#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "entrenador.h"
#include "lista.h"
#include "salon.h"
#include "util.h"
#include "pokemon.h"
#include "hash.h"
#include "abb.h"

#define SEPARADOR ';'
#define MIN_CANTIDAD_POKEMONES 0

struct _salon_t{
    abb_t* entrenadores;
    size_t cant_entrenadores;
};

int comparar_nombres(void* _elemento1, void* _elemento2){
  entrenador_t* entrenador1 = (entrenador_t*) _elemento1;
  entrenador_t* entrenador2 = (entrenador_t*) _elemento2;
  char* elemento1 = obtener_nombre_entrenador(entrenador1);
  char* elemento2 = obtener_nombre_entrenador(entrenador2);
  return strcmp(elemento1, elemento2);
}

void insercion_entrenadores(salon_t* salon, entrenador_t* entrenador){
  if(!salon || !entrenador)
    return;
  if(cantidad_pokemones(entrenador) > MIN_CANTIDAD_POKEMONES){
    arbol_insertar(salon->entrenadores, entrenador);
    salon->cant_entrenadores++;
  } else if(cantidad_pokemones(entrenador) == MIN_CANTIDAD_POKEMONES){
    destruye_entrenador(entrenador);
  }
}

salon_t* salon_leer_archivo(const char* nombre_archivo){
    FILE* file = fopen(nombre_archivo, "r");
    if(!file)
      return NULL;
    
    abb_t* entrenadores = arbol_crear(comparar_nombres, NULL);
    if(!entrenadores){
      fclosen(file);
      return NULL;
    }
    salon_t* salon = calloc(1, sizeof(salon_t));
    if(!salon){
      free(entrenadores);
      fclosen(file);
      return NULL;
    }
    salon->cant_entrenadores = 0;
    salon->entrenadores = entrenadores;

    entrenador_t* entrenador = NULL;
    pokemon_t* pokemon = NULL;
    char* str = fgets_alloc(file);
    char** str_div = NULL;

    while(str != NULL){
      str_div = split(str, SEPARADOR);
      if(vtrlen(str_div) == 2){
        insercion_entrenadores(salon, entrenador);
        entrenador = crea_entrenador(str_div[0]);
        modificar_victorias(entrenador, (size_t)atoi(str_div[1]));
      } else {
          pokemon = cargar_pokemon(str_div[0], (size_t)atoi(str_div[1]), (size_t)atoi(str_div[2]), (size_t)atoi(str_div[3]), (size_t)atoi(str_div[4]), (size_t)atoi(str_div[5]));
          agregar_pokemon(entrenador, pokemon);
      }
      free(str);
      vtrfree(str_div);
      str = fgets_alloc(file);
    }
    insercion_entrenadores(salon, entrenador);
    fclosen(file);
    return salon;
}

bool guardar_pokemones(void* _pokemon, void* _file){
  if(!_pokemon || !_file)
    return false;
  pokemon_t* pokemon = (pokemon_t*) _pokemon;
  FILE* file = (FILE*) _file;
  fprintf(file, "%s;%i;%i;%i;%i;%i\n",
      obtener_nombre(pokemon),
      obtener_nivel(pokemon),
      obtener_fuerza(pokemon),
      obtener_inteligencia(pokemon),
      obtener_velocidad(pokemon),
      obtener_defensa(pokemon));
  return true;
}

bool guarda_entrenadores(void* _entrenador, void* _file){
  if(!_entrenador || !_file)
    return true;
  entrenador_t* entrenador = (entrenador_t*) _entrenador;
  FILE* file = (FILE*) _file;
  fprintf(file, "%s;%i\n", obtener_nombre_entrenador(entrenador), cantidad_victorias(entrenador));
  lista_con_cada_elemento(obtener_lista_pokemon(entrenador), guardar_pokemones, file);
  return false;
}

int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
  if(!salon || !nombre_archivo)
    return ERROR;
  FILE* file = fopen(nombre_archivo, "w");
  if(!file)
    return ERROR;
  abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, guarda_entrenadores , file);
  fclosen(file);
  return VALIDO;
}

salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    return NULL;
}

lista_t* salon_filtrar_entrenadores(salon_t* salon , bool (*f)(entrenador_t*, void*), void* extra){
    return NULL;
}

char* salon_ejecutar_comando(salon_t* salon, const char* comando){
    return NULL;
}


bool destruye_entrenadores(void* elemento, void* contexto){
  if(!elemento)
    return true;
  entrenador_t* entrenador = (entrenador_t*) elemento;
  destruye_entrenador(entrenador);
  return false;
}

void salon_destruir(salon_t* salon){
  if(!salon)
    return;
  abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, destruye_entrenadores, NULL);
  arbol_destruir(salon->entrenadores);
  free(salon);
}
