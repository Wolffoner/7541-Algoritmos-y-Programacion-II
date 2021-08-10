#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "entrenador.h"
#include "lista.h"
#include "salon.h"
#include "util.h"
#include "pokemon.h"
#include "comando.h"
#include "hash.h"
#include "abb.h"

#define SEPARADOR ';'
#define MIN_CANTIDAD_POKEMONES 0
#define VICTORIAS "victorias"
#define INSUFICIENTE_CANT_POKEMON 0
#define ERROR_RESULTADO "ERROR"

struct _salon_t{
    abb_t* entrenadores;
    size_t cant_entrenadores;
    hash_t* comandos;
};
/***********************************************************************
                               COMANDOS 
***********************************************************************/

/* 
 * concatena todos los entrenadores dentro del salon al resultado
 * si el entrenador es nulo retorna true, si es distinto de nulo retorna false;
*/
bool imprimir_entrenadores(void* _entrenador, void* _resultado){
  entrenador_t* entrenador = (entrenador_t*) _entrenador;
  char* resultado = (char*) _resultado;
  if (!entrenador)
    return true;
  char victorias[10];
  sprintf(victorias, "%i", cantidad_victorias(entrenador));
  strcat(resultado, obtener_nombre_entrenador(entrenador));
  strcat(resultado, ",");
  strcat(resultado, victorias);
  strcat(resultado, "\n");
  return false;
}

/* 
 * concatena todos los entrenadores dentro del salon al resultado segun la cantidad_victorias minima
 * si el entrenador es nulo retorna true, si es distinto de nulo retorna false;
*/
bool imprimir_entrenadores_segun_victorias(void* _entrenador, void* _lista){
  entrenador_t* entrenador = (entrenador_t*) _entrenador;
  lista_t* lista = (lista_t*) _lista;
  char* resultado = (char*)lista_elemento_en_posicion(lista, 0);
  char* procesar_victorias = lista_elemento_en_posicion(lista,1);
  int minimo_victorias = atoi(procesar_victorias);
  if (!entrenador)
    return true;
  if(cantidad_victorias(entrenador) >= minimo_victorias){
    strcat(resultado, obtener_nombre_entrenador(entrenador));
    strcat(resultado, "\n");
  }
  return false;
}

/* 
 * concatena todos los entrenadores dentro del salon al resultado si el entrenador tiene el pokemon.
 * si el entrenador es nulo retorna true, si es distinto de nulo retorna false;
*/
bool imprimir_entrenadores_segun_pokemon(void* _entrenador, void* _lista){
  entrenador_t* entrenador = (entrenador_t*) _entrenador;
  lista_t* lista = (lista_t*) _lista;
  char* resultado = (char*)lista_elemento_en_posicion(lista, 0);
  char* nombre_pokemon = (char*)lista_elemento_en_posicion(lista, 1);
  if (!entrenador)
    return true;
  pokemon_t* pokemon = obtener_pokemon(entrenador, nombre_pokemon);
  if(pokemon){
    strcat(resultado, obtener_nombre_entrenador(entrenador));
    strcat(resultado, "\n");
  }
  return false;
}

/* 
 * Lista entrenadores dependiendo de los argumentos obtenidos,
 * Si hay algun error en los argumentos se concatena a resultado ERROR_RESULTADO.
*/
void listar_entrenadores(void* _salon, char** argumentos, void* resultado){
  if(!_salon || !resultado || !argumentos)
    return;
  salon_t* salon = (salon_t*) _salon;
  size_t cant_arg = vtrlen(argumentos);
  char** sub_argumentos = NULL;
  if(cant_arg == 1){
    abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, imprimir_entrenadores, resultado);
  } else if(cant_arg == 2){
    sub_argumentos = split(argumentos[1], ',');
    if(!sub_argumentos){
      strcat(resultado, ERROR_RESULTADO);
      return;
    }
    if(vtrlen(sub_argumentos) != 2){
      strcat(resultado, ERROR_RESULTADO);
      vtrfree(sub_argumentos);
      return;
    }
    lista_t* lista_aux = lista_crear();
    if(!lista_aux)
      return;
    lista_encolar(lista_aux, resultado);
    lista_encolar(lista_aux, sub_argumentos[1]);
    if(strcmp(sub_argumentos[0], VICTORIAS) == 0){
      abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, imprimir_entrenadores_segun_victorias, lista_aux);
    } else {
      abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, imprimir_entrenadores_segun_pokemon, lista_aux);
    }
    vtrfree(sub_argumentos);
    lista_destruir(lista_aux);
  }
}

/* 
 * concatena un pokemon con sus respectivas stats a resultado
 * Si el pokemon es nulo retorna false, si es valido retorna true.
*/
bool imprimir_pokemones(void* _pokemon, void* _resultado){
  if(!_pokemon || !_resultado)
    return false;
  pokemon_t* pokemon = (pokemon_t*) _pokemon;
  char* resultado = (char*) _resultado;
  char nivel[10];
  char defensa[10];
  char fuerza[10];
  char inteligencia[10];
  char velocidad[10];
  sprintf(nivel, "%i", obtener_nivel(pokemon));
  sprintf(defensa, "%i", obtener_defensa(pokemon));
  sprintf(fuerza, "%i", obtener_fuerza(pokemon));
  sprintf(inteligencia, "%i", obtener_inteligencia(pokemon));
  sprintf(velocidad, "%i", obtener_velocidad(pokemon));
  strcat(resultado, obtener_nombre(pokemon));
  strcat(resultado, ",");
  strcat(resultado, nivel);
  strcat(resultado, ",");
  strcat(resultado, defensa);
  strcat(resultado, ",");
  strcat(resultado, fuerza);
  strcat(resultado, ",");
  strcat(resultado, inteligencia);
  strcat(resultado, ",");
  strcat(resultado, velocidad);
  strcat(resultado, "\n");
  return true;
}

/* 
 * imprime pokemones segun el entrenador brindado
 * Si el _entrenador es nulo o fue encontrado retorna true, si es valido pero no fue encontrado retorna false.
*/
bool imprimir_pokemones_segun_entrenador(void* _entrenador, void* _lista){
  if(!_entrenador || !_lista)
    return true;
  entrenador_t* entrenador = (entrenador_t*) _entrenador;
  lista_t* lista = (lista_t*) _lista;
  void* resultado = lista_elemento_en_posicion(lista, 0);
  char* nombre_entrenador = (char*)lista_elemento_en_posicion(lista, 1);
  if(strcmp(nombre_entrenador, obtener_nombre_entrenador(entrenador)) == 0){
    lista_t* lista_aux = obtener_lista_pokemon(entrenador);
    lista_con_cada_elemento(lista_aux, imprimir_pokemones , resultado);
    return true;
  }
  return false;
}

/* 
 * Lista los equipos segun entrenador
 * Recorre el arbol para imprimir los pokemones del entrenador brindado.
*/
void listar_equipo_segun_entrenador(void* _salon, char** argumentos, void* resultado){
  if(!_salon || !resultado || !argumentos)
    return;
  salon_t* salon = (salon_t*) _salon;
  if(vtrlen(argumentos) != 2){
    strcat(resultado, ERROR_RESULTADO);
    return;
  }
  lista_t* lista_aux = lista_crear();
  if(!lista_aux)
    return;
  lista_encolar(lista_aux, resultado);
  lista_encolar(lista_aux, argumentos[1]);
  abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, imprimir_pokemones_segun_entrenador, lista_aux);
  if(strlen(resultado) == 0){
    strcat(resultado, ERROR_RESULTADO);
  }
  lista_destruir(lista_aux);
}

/* 
 * Compara 2 pokemones segun las reglas de batalla moderna.
 * Retorna el resultado de su batalla.
*/
int comparar_pokemones_moderno(pokemon_t* pokemon, pokemon_t* pokemon_rival){
  if(!pokemon)
    return -1;
  if(!pokemon_rival)
    return 1;
  double pokemon_stat = 0.5 * obtener_nivel(pokemon) + 0.9 * obtener_defensa(pokemon) + 3 * obtener_inteligencia(pokemon);
  double pokemon_rival_stat = 0.5 * obtener_nivel(pokemon_rival) + 0.9 * obtener_defensa(pokemon_rival) + 3 * obtener_inteligencia(pokemon_rival);
  return (int)(pokemon_stat - pokemon_rival_stat);
}

/* 
 * Compara 2 pokemones segun las reglas de batalla clasico.
 * Retorna el resultado de su batalla.
*/

int comparar_pokemones_clasico(pokemon_t* pokemon, pokemon_t* pokemon_rival){
  if(!pokemon)
    return -1;
  if(!pokemon_rival)
    return 1;
  double pokemon_stat = 0.8 * obtener_nivel(pokemon) + obtener_fuerza(pokemon) + 2 * obtener_velocidad(pokemon);
  double pokemon_rival_stat = 0.8 * obtener_nivel(pokemon_rival) + obtener_fuerza(pokemon_rival) + 2 * obtener_velocidad(pokemon_rival);
  return (int)(pokemon_stat - pokemon_rival_stat);
}

/* 
 * Compara 2 pokemones segun las reglas de batalla fuerza.
 * Retorna el resultado de su batalla.
*/
int comparar_pokemones_fuerza(pokemon_t* pokemon, pokemon_t* pokemon_rival){
  if(!pokemon)
    return -1;
  if(!pokemon_rival)
    return 1;
  double pokemon_stat = obtener_fuerza(pokemon);
  double pokemon_rival_stat = obtener_fuerza(pokemon_rival);
  return (int)(pokemon_stat - pokemon_rival_stat);
}

/* 
 * Compara 2 pokemones segun las reglas de batalla inteligencia.
 * Retorna el resultado de su batalla.
*/
int comparar_pokemones_inteligencia(pokemon_t* pokemon, pokemon_t* pokemon_rival){
  if(!pokemon)
    return -1;
  if(!pokemon_rival)
    return 1;
  double pokemon_stat = obtener_inteligencia(pokemon);
  double pokemon_rival_stat = obtener_inteligencia(pokemon_rival);
  return (int)(pokemon_stat - pokemon_rival_stat);
}

/* 
 * Compara 2 pokemones segun las reglas de batalla defensa.
 * Retorna el resultado de su batalla.
*/
int comparar_pokemones_defensa(pokemon_t* pokemon, pokemon_t* pokemon_rival){
  if(!pokemon)
    return -1;
  if(!pokemon_rival)
    return 1;
  double pokemon_stat = obtener_defensa(pokemon);
  double pokemon_rival_stat = obtener_defensa(pokemon_rival);
  return (int)(pokemon_stat - pokemon_rival_stat);
}

/* 
 * Busca entrenador segun su nombre,
 * Si el entrenador es nulo o fue encontrado retorna true, si es valido y no fue encontrado retorna false.
*/
bool busca_entrenador(void* _entrenador, void* extra){
  if(!_entrenador || !extra)
    return true;
  entrenador_t* entrenador = (entrenador_t*) _entrenador;
  lista_t* lista = (lista_t*) extra;
  char* nombre = (char*) lista_elemento_en_posicion(lista, 0);
  if(strcmp(nombre, obtener_nombre_entrenador(entrenador)) == 0){
    lista_encolar(lista, entrenador);
    return true;
  }
  return false;
}

/* 
 * compara pokemones segun las reglas de batalla.
 * dependiendo del modo de batalla se ejecuta cada regla, para comparar los pokemones y concatena en _resultado los resultados de la batalla.
*/
void comparar_segun_reglas(void* _salon, char** sub_argumentos, void* _resultado){
  if(!_salon || !_resultado || !sub_argumentos)
    return;
  salon_t* salon = (salon_t*) _salon;
  char* resultado = (char*) _resultado;
  lista_t* lista_aux = lista_crear();
  if(!lista_aux)
    return;
  entrenador_t* entrenador1 = NULL;
  entrenador_t* entrenador2 = NULL;

  lista_encolar(lista_aux, sub_argumentos[0]);
  abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, busca_entrenador, lista_aux);
  if(lista_elementos(lista_aux) != 2){
    strcat(resultado, ERROR_RESULTADO);
    lista_destruir(lista_aux);
    return;
  }
  entrenador1 = (entrenador_t*)lista_elemento_en_posicion(lista_aux, 1);
  lista_desencolar(lista_aux);
  lista_desencolar(lista_aux);
   
  lista_encolar(lista_aux, sub_argumentos[1]);
  abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, busca_entrenador, lista_aux);
  if(lista_elementos(lista_aux) != 2){
    strcat(resultado, ERROR_RESULTADO);
    lista_destruir(lista_aux);
    return;
  }
  entrenador2 = (entrenador_t*)lista_elemento_en_posicion(lista_aux, 1);
  lista_t* lista1 = obtener_lista_pokemon(entrenador1);
  lista_t* lista2 = obtener_lista_pokemon(entrenador2);
  lista_iterador_t* iterador1 = lista_iterador_crear(lista1);
  lista_iterador_t* iterador2 = lista_iterador_crear(lista2);
  pokemon_t* pokemon1 = NULL;
  pokemon_t* pokemon2 = NULL;
  int resultado_comparar = 0;
  comando_t* sub_comando = hash_obtener(salon->comandos, sub_argumentos[2]);
  if(!sub_comando){
    strcat(resultado, ERROR_RESULTADO);
    lista_destruir(lista_aux);
    return;
  }
  while(lista_iterador_tiene_siguiente(iterador1) && lista_iterador_tiene_siguiente(iterador2)){
    pokemon1 = lista_iterador_elemento_actual(iterador1);
    pokemon2 = lista_iterador_elemento_actual(iterador2);
    if(strcmp(obtener_nombre_comando(sub_comando),"CLASICO") == 0){
      resultado_comparar = comparar_pokemones_clasico(pokemon1, pokemon2);
    } else if(strcmp(obtener_nombre_comando(sub_comando),"MODERNO") == 0){
      resultado_comparar = comparar_pokemones_moderno(pokemon1, pokemon2);
    } else if(strcmp(obtener_nombre_comando(sub_comando),"FUERZA") == 0){
      resultado_comparar = comparar_pokemones_fuerza(pokemon1, pokemon2);
    } else if(strcmp(obtener_nombre_comando(sub_comando),"INTELIGENCIA") == 0){
      resultado_comparar = comparar_pokemones_inteligencia(pokemon1, pokemon2);
    } else if(strcmp(obtener_nombre_comando(sub_comando),"DEFENSA") == 0){
      resultado_comparar = comparar_pokemones_defensa(pokemon1, pokemon2);
    }
    if(resultado_comparar < 0){
      strcat(resultado, "2\n");
      lista_iterador_avanzar(iterador1);
    } else {
      strcat(resultado, "1\n");
      lista_iterador_avanzar(iterador2);
    }
  }
  lista_destruir(lista_aux);
  lista_iterador_destruir(iterador1);
  lista_iterador_destruir(iterador2);
}

/* 
 * compara entrenadores en una batalla con todos sus pokemones.
*/
void comparar_entrenadores(void* _salon, char** argumentos, void* _resultado){
  if(!_salon || !_resultado || !argumentos)
    return;
  salon_t* salon = (salon_t*) _salon;
  char** sub_argumentos = split(argumentos[1], ',');
  comando_t* regla_batalla = hash_obtener(salon->comandos, sub_argumentos[2]);
  if(!regla_batalla){
    vtrfree(sub_argumentos);
    strcat(_resultado, ERROR_RESULTADO);
    return;
  }
  if(regla_batalla){
    ejecutar_comando_t ejecutar = obtener_ejecutar_comando(regla_batalla);
    ejecutar(_salon, sub_argumentos, _resultado);
  }
  vtrfree(sub_argumentos);
}

/* 
 * Concatena en _resultado todas las reglas de batalla creadas para los enfrentamientos.
*/
void listar_reglas(void* _salon, char** argumentos, void* _resultado){
  if(!_salon || !_resultado || !argumentos)
    return;
  if(vtrlen(argumentos) != 1){
    strcat(_resultado, ERROR_RESULTADO);
    return;
  }
  salon_t* salon = (salon_t*) _salon;
  char* resultado = (char*) _resultado;
  comando_t* reglas_clasico = hash_obtener(salon->comandos, "CLASICO");
  comando_t* reglas_moderno = hash_obtener(salon->comandos, "MODERNO");
  comando_t* reglas_fuerza = hash_obtener(salon->comandos, "FUERZA");
  comando_t* reglas_inteligencia = hash_obtener(salon->comandos, "INTELIGENCIA");
  comando_t* reglas_defensa = hash_obtener(salon->comandos, "DEFENSA");
  strcat(resultado, obtener_nombre_comando(reglas_clasico));
  strcat(resultado, ",");
  strcat(resultado, obtener_descripcion_comando(reglas_clasico));
  strcat(resultado, "\n");
  strcat(resultado, obtener_nombre_comando(reglas_moderno));
  strcat(resultado, ",");
  strcat(resultado, obtener_descripcion_comando(reglas_moderno));
  strcat(resultado, "\n");
  strcat(resultado, obtener_nombre_comando(reglas_fuerza));
  strcat(resultado, ",");
  strcat(resultado, obtener_descripcion_comando(reglas_fuerza));
  strcat(resultado, "\n");
  strcat(resultado, obtener_nombre_comando(reglas_inteligencia));
  strcat(resultado, ",");
  strcat(resultado, obtener_descripcion_comando(reglas_inteligencia));
  strcat(resultado, "\n");
  strcat(resultado, obtener_nombre_comando(reglas_defensa));
  strcat(resultado, ",");
  strcat(resultado, obtener_descripcion_comando(reglas_defensa));
  strcat(resultado, "\n");
}

/* 
 * Agrega un pokemon a un entrenador del salon. y concatena OK si pudo hacerlo o ERROR_RESULTADO si no pudo.
*/
void agregar_pokemon_nuevo(void* _salon, char** argumentos, void* _resultado){
  if(!_salon || !_resultado || !argumentos)
    return;
  salon_t* salon = (salon_t*) _salon;
  char* resultado = (char*) _resultado;
  char** sub_argumentos = split(argumentos[1], ',');
  if(!sub_argumentos)
    return;
  if(vtrlen(sub_argumentos) != 7){
    strcat(resultado, ERROR_RESULTADO);
    vtrfree(sub_argumentos);
    return;
  }
  pokemon_t* pokemon = cargar_pokemon(
      sub_argumentos[1], 
      (size_t)atoi(sub_argumentos[2]), 
      (size_t)atoi(sub_argumentos[3]), 
      (size_t)atoi(sub_argumentos[4]),
      (size_t)atoi(sub_argumentos[5]),
      (size_t)atoi(sub_argumentos[6]));
  if(!pokemon){
    vtrfree(sub_argumentos);
    return;
  }
  lista_t* lista_aux = lista_crear();
  if(!lista_aux){
    destruye_pokemon(pokemon);
    vtrfree(sub_argumentos);
    return;
  }
  entrenador_t* entrenador1 = NULL;
  lista_encolar(lista_aux, sub_argumentos[0]);
  abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, busca_entrenador, lista_aux);
  entrenador1 = (entrenador_t*)lista_elemento_en_posicion(lista_aux, 1);
  if(!entrenador1){
    strcat(resultado, ERROR_RESULTADO);
    destruye_pokemon(pokemon);
    lista_destruir(lista_aux);
    vtrfree(sub_argumentos);
    return;
  }
  if(agregar_pokemon(entrenador1, pokemon) != ERROR){
    strcat(resultado, "OK");
  } else {
    destruye_pokemon(pokemon);
    strcat(resultado, ERROR_RESULTADO);
  }
  lista_destruir(lista_aux);
  vtrfree(sub_argumentos);
}

/* 
 * Quita un pokemon a un entrenador del salon. y concatena OK si pudo hacerlo o ERROR_RESULTADO si no pudo.
*/
void quitar_pokemon(void* _salon, char** argumentos, void* _resultado){
   if(!_salon || !_resultado || !argumentos)
    return;
  salon_t* salon = (salon_t*) _salon;
  char* resultado = (char*) _resultado;
  char** sub_argumentos = split(argumentos[1], ',');
  if(!sub_argumentos)
    return;
  lista_t* lista_aux = lista_crear();
  if(!lista_aux){
    vtrfree(sub_argumentos);
    return;
  }
  entrenador_t* entrenador1 = NULL;
  lista_encolar(lista_aux, sub_argumentos[0]);
  abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, busca_entrenador, lista_aux);
  entrenador1 = (entrenador_t*)lista_elemento_en_posicion(lista_aux, 1);
  if(!entrenador1){
    strcat(resultado, ERROR_RESULTADO);
    vtrfree(sub_argumentos);
    lista_destruir(lista_aux);
    return;
  }
  if(cantidad_pokemones(entrenador1) > 1){
    if(liberar_pokemon(entrenador1, sub_argumentos[1]) != ERROR){
      strcat(resultado, "OK");
    } else {
      strcat(resultado, ERROR_RESULTADO);
    }
  } else {
    strcat(resultado, ERROR_RESULTADO);
  }
  
  lista_destruir(lista_aux);
  vtrfree(sub_argumentos);
}

/* 
 * Guarda salon, concatena a resultado OK si pudo guardar o ERROR_RESULTADO en caso de que no haya podido guardarlo.
*/
void guardar(void* _salon, char** argumentos, void* _resultado){
   if(!_salon || !_resultado || !argumentos)
    return;
  salon_t* salon = (salon_t*) _salon;
  char* resultado = (char*) _resultado;
  if(salon_guardar_archivo(salon, argumentos[1]) != ERROR){
    strcat(resultado, "OK");
  }else{
    strcat(resultado, ERROR_RESULTADO);
  }
}
/******************************************************************************/


/*
 * Crea y agrega comandos al salon.
 */
void agregar_comandos(salon_t* salon){
  comando_t* comando1 = comando_crear("ENTRENADORES", 
      "Pide el listado de los entrenadores almacenados en el salon de la fama.Devuelve registros por orden alfabetico",
      listar_entrenadores);
  comando_t* comando2 = comando_crear("EQUIPO",
      "Devuelve el equipo pokemon del entrenador llamado <nombre>. Cada registro consta de los datos de un pokemon",
      listar_equipo_segun_entrenador);
  comando_t* comando3 = comando_crear("REGLAS",
      "Devuelve el equipo pokemon del entrenador llamado <nombre>. Cada registro consta de los datos de un pokemon",
      listar_reglas);
  comando_t* sub_comando1 = comando_crear("CLASICO",
      "Las reglas clasicas indican que un combate lo gana el Pokemon con el coeficiente de batalla mas alto en base al siguiente calculo: 0.8 ∗ nivel + fuerza + 2 ∗ velocidad",
      comparar_segun_reglas);
  comando_t* sub_comando2 = comando_crear("MODERNO",
      "Las reglas modernas indican que un combate lo gana el Pokemon con el coeficiente de batalla mas alto en base al siguiente calculo: 0.5 ∗ nivel + 0.9 ∗ defensa + 3 ∗ inteligencia",
      comparar_segun_reglas);
  comando_t* sub_comando3 = comando_crear("FUERZA",
      "Las reglas de fuerza indican que un combate lo gana el Pokemon con el coeficiente de fuerza mas alto.",
      comparar_segun_reglas);
  comando_t* sub_comando4 = comando_crear("INTELIGENCIA",
      "Las reglas de inteligencia indican que un combate lo gana el Pokemon con el coeficiente de inteligencia mas alto.",
      comparar_segun_reglas);
  comando_t* sub_comando5 = comando_crear("DEFENSA",
      "Las reglas de defensa indican que un combate lo gana el Pokemon con el coeficiente de defensa mas alto.",
      comparar_segun_reglas);
  comando_t* comando4 = comando_crear("COMPARAR",
    "Compara dos entrenadores según una regla de batalla. Devuelve un registro por cada una de los enfrentamientos. Cada registro es un 1 si ganó el pokemon del entrenador 1 o 2 si ganó el pokemon del entrenador 2.",
    comparar_entrenadores);
  comando_t* comando5 = comando_crear("AGREGAR_POKEMON",
    "Agrega un pokemon a un entrenador. Devuelve el string OK.",
    agregar_pokemon_nuevo);
  comando_t* comando6 = comando_crear("QUITAR_POKEMON",
    "Quita un pokemon de un entrenador. Devuelve el string OK si pudo. Tener en cuenta que un entrenador no puede tener menos de 1 Pokemon.",
    quitar_pokemon);
  comando_t* comando7 = comando_crear("GUARDAR",
    "Guarda los datos del salón en un archivo con el nombre dado. Devuelve el string OK si pudo.",
    guardar);
  hash_insertar(salon->comandos, obtener_nombre_comando(comando1), comando1);
  hash_insertar(salon->comandos, obtener_nombre_comando(comando2), comando2);
  hash_insertar(salon->comandos, obtener_nombre_comando(comando3), comando3);
  hash_insertar(salon->comandos, obtener_nombre_comando(sub_comando1), sub_comando1);
  hash_insertar(salon->comandos, obtener_nombre_comando(sub_comando2), sub_comando2);
  hash_insertar(salon->comandos, obtener_nombre_comando(sub_comando3), sub_comando3);
  hash_insertar(salon->comandos, obtener_nombre_comando(sub_comando4), sub_comando4); 
  hash_insertar(salon->comandos, obtener_nombre_comando(sub_comando5), sub_comando5);
  hash_insertar(salon->comandos, obtener_nombre_comando(comando4), comando4);
  hash_insertar(salon->comandos, obtener_nombre_comando(comando5), comando5);
  hash_insertar(salon->comandos, obtener_nombre_comando(comando6), comando6);
  hash_insertar(salon->comandos, obtener_nombre_comando(comando7), comando7);
}

/*
 * Compara los nombres de los entrenadores.
 */
int comparar_nombres(void* _elemento1, void* _elemento2){
  entrenador_t* entrenador1 = (entrenador_t*) _elemento1;
  entrenador_t* entrenador2 = (entrenador_t*) _elemento2;
  char* elemento1 = obtener_nombre_entrenador(entrenador1);
  char* elemento2 = obtener_nombre_entrenador(entrenador2);
  return strcmp(elemento1, elemento2);
}

/*
 * Destruye comando.
 */
void destruye_comandos(void* _comando){
  comando_t* comando = (comando_t*) _comando;
  if(comando)
    comando_destruir(comando);
}

/*
 * Destruye entrenadores.
 */
void destruye_entrenadores(void* _entrenador){
  entrenador_t* entrenador = (entrenador_t*) _entrenador;
  if(entrenador)
    destruye_entrenador(entrenador);
}

bool verifica_entrenador_duplicado(void* _entrenador1, void* _lista){
  if(!_entrenador1 || !_lista){
    return true;
  }
  lista_t* lista = (lista_t*) _lista;
  entrenador_t* entrenador1 = (entrenador_t*)_entrenador1;
  entrenador_t* entrenador2 = lista_elemento_en_posicion(lista, 1);
  bool* duplicado = lista_elemento_en_posicion(lista, 0);
  if(strcmp(obtener_nombre_entrenador(entrenador1), obtener_nombre_entrenador(entrenador2)) == 0){
    *duplicado = true;
    return true;
  }
  return false;
}

/*
 * Verifica si se puede insertar el entrenador
 */
int insercion_entrenadores(salon_t* salon, entrenador_t* entrenador){
  int insercion = -1;
  if(!salon || !entrenador)
    return insercion;
  lista_t* lista_aux = lista_crear();
  if(!lista_aux){
    return insercion;
  }
  bool duplicado = false;
  lista_encolar(lista_aux, &duplicado);
  lista_encolar(lista_aux, entrenador);
  abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN, verifica_entrenador_duplicado, lista_aux);
  if(duplicado){
    destruye_entrenador(entrenador);
    lista_destruir(lista_aux);
    insercion = 0;
    return insercion;
  }
  if(cantidad_pokemones(entrenador) > MIN_CANTIDAD_POKEMONES){
    arbol_insertar(salon->entrenadores, entrenador);
    salon->cant_entrenadores++;
    insercion = 1;
  } else if(cantidad_pokemones(entrenador) == MIN_CANTIDAD_POKEMONES){
    destruye_entrenador(entrenador);
    insercion = 0;
  }
  lista_destruir(lista_aux);
  return insercion;
}

salon_t* salon_leer_archivo(const char* nombre_archivo){
  FILE* file = fopen(nombre_archivo, "r");
  if(!file)
    return NULL;
  
  abb_t* entrenadores = arbol_crear(comparar_nombres, destruye_entrenadores);
  if(!entrenadores){
    fclosen(file);
    return NULL;
  }
  hash_t* comandos = hash_crear(destruye_comandos, 20);
  if(!comandos){
    fclosen(file);
    free(entrenadores);
    return NULL;
  }
  salon_t* salon = calloc(1, sizeof(salon_t));
  if(!salon){
    free(entrenadores);
    fclosen(file);
    free(comandos);
    return NULL;
  }
  salon->cant_entrenadores = 0;
  salon->entrenadores = entrenadores;
  salon->comandos = comandos;

  agregar_comandos(salon);
  entrenador_t* entrenador = NULL;
  pokemon_t* pokemon = NULL;
  char* str = fgets_alloc(file);
  char** str_div = NULL;
  int insercion = -1;
  while(str != NULL){
    str_div = split(str, SEPARADOR);
    if(vtrlen(str_div) == 2){
      insercion = insercion_entrenadores(salon, entrenador);
      if(insercion == INSUFICIENTE_CANT_POKEMON){
        salon_destruir(salon);
        fclosen(file);
        free(str);
        vtrfree(str_div);
        return NULL;
      }
      entrenador = crea_entrenador(str_div[0]);
      modificar_victorias(entrenador, (size_t)atoi(str_div[1]));
    } else if(vtrlen(str_div) == 6){
      int nivel = atoi(str_div[1]);
      int defensa = atoi(str_div[2]);
      int fuerza = atoi(str_div[3]);
      int inteligencia = atoi(str_div[4]);
      int velocidad = atoi(str_div[5]);
        pokemon = cargar_pokemon(str_div[0], (size_t)nivel, (size_t)defensa, (size_t)fuerza, (size_t)inteligencia, (size_t)velocidad);
        agregar_pokemon(entrenador, pokemon);
    }
    free(str);
    vtrfree(str_div);
    str = fgets_alloc(file);
  }
  insercion = insercion_entrenadores(salon, entrenador);
  if(insercion == INSUFICIENTE_CANT_POKEMON){
    salon_destruir(salon);
    fclosen(file);
    return NULL;
  }
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
      obtener_defensa(pokemon),
      obtener_fuerza(pokemon),
      obtener_inteligencia(pokemon),
      obtener_velocidad(pokemon));
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
  if(!salon || !entrenador)
    return NULL;
  if(cantidad_pokemones(entrenador) == 0)
    return NULL;

  arbol_insertar(salon->entrenadores, entrenador);
  return salon;
}

lista_t* salon_filtrar_entrenadores(salon_t* salon , bool (*f)(entrenador_t*, void*), void* extra){
  if(!salon)
    return NULL;
  lista_t* lista = lista_crear();
  void** entrenadores = calloc(1, sizeof(void*)*salon->cant_entrenadores);
  if(!entrenadores)
    return NULL;
  arbol_recorrido_inorden(salon->entrenadores, entrenadores, salon->cant_entrenadores);
  entrenador_t** entrenadores_cast = (entrenador_t**) entrenadores;
  for(int i = 0; i < salon->cant_entrenadores; i++){
    bool insertar = f(entrenadores_cast[i], extra);
    if(insertar)
      lista_insertar(lista, entrenadores_cast[i]);
  }
  free(entrenadores);
  return lista;
}
// procesar comando
void procesar_comando(salon_t* salon, const char* comando, char* resultado) {
  if(!salon || !comando || !resultado)
    return;
  char** argumentos = split(comando, ':');
  if(!argumentos){
    return;
  }
  comando_t* comando_aux = hash_obtener(salon->comandos, argumentos[0]);
  if(comando_aux){
    ejecutar_comando_t ejecutar = obtener_ejecutar_comando(comando_aux);
    ejecutar((void*)salon, argumentos, (void*)resultado);
  } else {
    strcat(resultado, ERROR_RESULTADO);
  }
  vtrfree(argumentos);
}

char* salon_ejecutar_comando(salon_t* salon, const char* comando){
  if (!salon || !comando)
      return NULL;
  char *resultado = calloc(1, sizeof(char) * 2048);
  if (!resultado)
      return NULL;
  procesar_comando(salon, comando, resultado);
  if(strcmp(resultado, ERROR_RESULTADO) == 0){
    free(resultado);
    return NULL;
  }
  return resultado;
}

void salon_destruir(salon_t* salon){
  if(!salon)
    return;
  hash_destruir(salon->comandos);
  arbol_destruir(salon->entrenadores);
  free(salon);
}
