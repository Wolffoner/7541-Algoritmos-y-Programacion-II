#include "pokemon.h"

struct _pokemon_t{
  char* nombre;
  size_t nivel;
  size_t fuerza;
  size_t inteligencia;
  size_t velocidad;
  size_t defensa;
};

pokemon_t* crea_pokemon_inicializado(char* nombre, size_t nivel, size_t fuerza, size_t inteligencia, size_t velocidad, size_t defensa){
  if(!nombre)
    return NULL;

  char* nombre_aux = calloc(1, strlen(nombre)+1);
  if(!nombre_aux)
    return NULL;

  pokemon_t* pokemon = calloc(1, sizeof(pokemon_t));
  if(!pokemon){
    free(nombre_aux);
    return NULL;
  }
  strcpy(nombre_aux, nombre);
  pokemon->nombre = nombre_aux;
  pokemon->nivel = nivel;
  pokemon->fuerza = fuerza;
  pokemon->inteligencia = inteligencia;
  pokemon->velocidad = velocidad;
  pokemon->defensa = defensa;
  return pokemon;
}

pokemon_t* crea_pokemon(char* nombre){
    pokemon_t* pokemon = crea_pokemon_inicializado(nombre, NIVEL_INICIAL, FUERZA_INICIAL, INTELIGENCIA_INICIAL, VELOCIDAD_INICIAL, DEFENSA_INICIAL);
    if(!pokemon)
      return NULL;
    return pokemon;
}

pokemon_t* cargar_pokemon(char* nombre, size_t nivel, size_t fuerza, size_t inteligencia, size_t velocidad, size_t defensa){
  pokemon_t* pokemon = crea_pokemon_inicializado(nombre, nivel, fuerza, inteligencia, velocidad, defensa);
  if(!pokemon)
    return NULL;
  return pokemon;
}

char* obtener_nombre(pokemon_t* pokemon){
  if(!pokemon)
    return NULL;
  return pokemon->nombre;
}

void modificar_nivel(pokemon_t* pokemon, size_t nivel){
  if(!pokemon){
    return;
  }
  pokemon->nivel = nivel;
}

int obtener_nivel(pokemon_t* pokemon){
  if(!pokemon)
    return ERROR;
  return (int)pokemon->nivel;
}

void modificar_fuerza(pokemon_t* pokemon, size_t fuerza){
  if(!pokemon)
    return;
  pokemon->fuerza = fuerza;
}

int obtener_fuerza(pokemon_t* pokemon){
  if(!pokemon)
    return ERROR;
  return (int)pokemon->fuerza;
}

void modificar_inteligencia(pokemon_t* pokemon, size_t inteligencia){
  if(!pokemon)
    return;
  pokemon->inteligencia = inteligencia;
}

int obtener_inteligencia(pokemon_t* pokemon){
  if(!pokemon)
    return ERROR;
  return (int)pokemon->inteligencia;
}

void modificar_velocidad(pokemon_t* pokemon, size_t velocidad){
  if(!pokemon)
    return;
  pokemon->velocidad = velocidad;
}

int obtener_velocidad(pokemon_t* pokemon){
  if(!pokemon)
    return ERROR;
  return (int)pokemon->velocidad;
}

void modificar_defensa(pokemon_t* pokemon, size_t defensa){
  if(!pokemon)
    return;
  pokemon->defensa = defensa;
}

int obtener_defensa(pokemon_t* pokemon){
  if(!pokemon)
    return ERROR;
  return (int)pokemon->defensa;
}

void destruye_pokemon(pokemon_t* pokemon){
  if(!pokemon)
    return;
  free(pokemon->nombre);
  free(pokemon);
}

