#include "entrenador.h"
#include "lista.h"
#include "pokemon.h"

struct _entrenador_t{
  char* nombre;
  size_t victorias;
  size_t cant_pokemones;
  lista_t* pokemones;
};

entrenador_t* crea_entrenador(char* nombre){
  if(!nombre)
    return NULL;
  char* nombre_aux = calloc(1, strlen(nombre)+1);
  if(!nombre_aux)
    return NULL;
  entrenador_t* entrenador = calloc(1, sizeof(entrenador_t));
  if(!entrenador){
    free(nombre_aux);
    return NULL;
  }
  lista_t* pokemones = lista_crear();
  if(!pokemones){
    free(nombre_aux);
    free(entrenador);
    return NULL;
  }
  strcpy(nombre_aux, nombre);
  entrenador->nombre = nombre_aux;
  entrenador->victorias = 0;
  entrenador->cant_pokemones = 0;
  entrenador->pokemones = pokemones;
  return entrenador;
}

char* obtener_nombre_entrenador(entrenador_t* entrenador){
  if(!entrenador)
    return NULL;
  return entrenador->nombre;
}

int agregar_pokemon(entrenador_t* entrenador, pokemon_t* pokemon){
  if(!entrenador || !pokemon)
    return ERROR;
  int insertado = lista_insertar(entrenador->pokemones, pokemon);
  entrenador->cant_pokemones++;
  return insertado;
}

pokemon_t* obtener_pokemon(entrenador_t* entrenador, char* nombre_pokemon){
  if(!entrenador || !nombre_pokemon)
    return NULL;
  bool encontrado = false;
  pokemon_t* pokemon_buscado = NULL;
  char* nombre_pokemon_buscado = NULL;
  lista_iterador_t* iterador = lista_iterador_crear(entrenador->pokemones);
  while(lista_iterador_tiene_siguiente(iterador) && !encontrado){
    pokemon_buscado = (pokemon_t*) lista_iterador_elemento_actual(iterador);
    nombre_pokemon_buscado = obtener_nombre(pokemon_buscado);
    if(strcmp(nombre_pokemon_buscado, nombre_pokemon) == IGUALES){
      encontrado = true;
    } else {
      lista_iterador_avanzar(iterador);
    }
  }
  lista_iterador_destruir(iterador);
  return pokemon_buscado;
}

int liberar_pokemon(entrenador_t* entrenador, char* nombre_pokemon){
  if(!entrenador || !nombre_pokemon)
    return ERROR;
  bool encontrado = false;
  size_t posicion_encontrado = 0;
  pokemon_t* pokemon_buscado = NULL;
  char* nombre_pokemon_buscado = NULL;
  lista_iterador_t* iterador = lista_iterador_crear(entrenador->pokemones);
  while(lista_iterador_tiene_siguiente(iterador) && !encontrado){
    pokemon_buscado = (pokemon_t*) lista_iterador_elemento_actual(iterador);
    nombre_pokemon_buscado = obtener_nombre(pokemon_buscado);
    if(strcmp(nombre_pokemon_buscado, nombre_pokemon) == IGUALES){
      encontrado = true;
    } else {
      posicion_encontrado++;
      lista_iterador_avanzar(iterador);
    }
  }
  lista_iterador_destruir(iterador);
  if(encontrado){
    if(lista_borrar_de_posicion(entrenador->pokemones, posicion_encontrado) == 0){
      entrenador->cant_pokemones--;
      destruye_pokemon(pokemon_buscado);
      return (int)posicion_encontrado;
    }
  }
  return ERROR;
}

lista_t* obtener_lista_pokemon(entrenador_t* entrenador){
  if(!entrenador)
    return NULL;
  return entrenador->pokemones;
}

int modificar_victorias(entrenador_t* entrenador, size_t victorias){
  if(!entrenador)
    return ERROR;
  entrenador->victorias = victorias;
  return (int)entrenador->victorias;
}

int cantidad_victorias(entrenador_t* entrenador){
  if(!entrenador)
    return ERROR;
  return (int)entrenador->victorias;
}

int cantidad_pokemones(entrenador_t* entrenador){
  if(!entrenador)
    return ERROR;
  return (int)entrenador->cant_pokemones;
}

bool destruye_nombre_pokemon(void* elemento, void* contexto){
  if(!elemento)
    return false;
  pokemon_t* pokemon = (pokemon_t*) elemento;
  destruye_pokemon(pokemon);
  return true;
}

void destruye_entrenador(entrenador_t* entrenador){
  if(!entrenador)
    return;
  lista_con_cada_elemento(entrenador->pokemones, destruye_nombre_pokemon, NULL);
  lista_destruir(entrenador->pokemones);
  free(entrenador->nombre);
  free(entrenador);
}
