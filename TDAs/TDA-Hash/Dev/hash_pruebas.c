#include "hash.h"
#include <stdio.h>
#include "pa2mm.h"

void CrearUnHash_ConCapacidadMenorATres_CreaUnHashConCapacidadTres(){
  hash_t* tabla = NULL;
  tabla = hash_crear(NULL, 0);
  pa2m_afirmar(tabla, "Tabla de hash es creada con capacidad menor a 3.");
  hash_destruir(tabla);
}

void CrearUnHash_ConCapacidadMayorATres_CreaUnHashConEsaCapacidad(){
  hash_t* tabla = NULL;
  tabla = hash_crear(NULL, 10);
  pa2m_afirmar(tabla, "Tabla de hash es creada con capacidad mayor a 3.");
  hash_destruir(tabla);
}

void UnaTablaHash_SiInsertoUnElemento_SeAgregaAlaTabla(){
  hash_t* tabla = hash_crear(NULL, 10);
  char* clave = "h";
  void* elemento = (void*)0xBEBECAF1;
  int test = hash_insertar(tabla, clave, elemento);
  pa2m_afirmar(test != -1, "Se agrego un elemento a la tabla.");
  hash_destruir(tabla);
}

void UnaTablaHash_SiSuperaFactorDeCarga_Rehashea(){
  hash_t* tabla = hash_crear(NULL, 3);
  char* clave1 = "h";
  void* elemento1 = (void*)0xBEBECAF1; 
  char* clave2 = "holis2"; 
  void* elemento2 = (void*)0xBEBECAF2;
  char* clave3 = "aa"; 
  void* elemento3 = (void*)0xBEBECAF3;
  hash_insertar(tabla, clave1, elemento1);
  hash_insertar(tabla, clave2, elemento2);
  int test3 = hash_insertar(tabla, clave3, elemento3);
  pa2m_afirmar(test3 != -1, "Se rehashea y se agrega un elemento a la tabla.");
  hash_destruir(tabla);
}

void UnaTablaHash_SiInsertoUnElementoConMismaClave_SobreEscribeElElemento(){
  hash_t* tabla = hash_crear(NULL, 3);
  char* clave1 = "h";
  void* elemento1 = (void*)0xBEBECAF1;
  char* clave2 = "h";
  void* elemento2 = (void*)0xBEBECAF2;
  hash_insertar(tabla, clave1, elemento1);
  int test2 = hash_insertar(tabla, clave2, elemento2);
  pa2m_afirmar(test2 != -1, "Se sobreescribio el primer elemento con otro elemento a la tabla.");
  hash_destruir(tabla);
}

void UnaTablaDeHash_SiSeBuscaUnElementoInsertado_SeEncuentra(){
  hash_t* tabla = hash_crear(NULL, 3);
  char* clave1 = "aa";
  void* elemento1 = (void*)0xBEBECAF1;
  char* clave2 = "dd";
  void* elemento2 = (void*)0xBEBECAF2;
  hash_insertar(tabla, clave1, elemento1);
  hash_insertar(tabla, clave2, elemento2);
  void* elemento = hash_obtener(tabla, clave2);
  pa2m_afirmar(elemento2 == elemento, "Se obtuvo el elemento buscado.");
  hash_destruir(tabla);
}

void UnaTablaDeHash_SiSeBuscaUnElementoNoInsertado_NoSeEncuentraElElemento(){
  hash_t* tabla = hash_crear(NULL, 10);
  char* clave1 = "aa";
  void* elemento1 = (void*)0xBEBECAF1;
  char* clave2 = "bb";
  hash_insertar(tabla, clave1, elemento1);
  void* elemento = hash_obtener(tabla, clave2);
  pa2m_afirmar(elemento == NULL, "No se encontro el elemento porque no esta dentro del hash.");
  hash_destruir(tabla);
}
int main(){
  pa2m_nuevo_grupo("Creacion de tabla de hash");
  CrearUnHash_ConCapacidadMenorATres_CreaUnHashConCapacidadTres();
  CrearUnHash_ConCapacidadMayorATres_CreaUnHashConEsaCapacidad();
  pa2m_nuevo_grupo("Insercion en la tabla de hash");
  UnaTablaHash_SiInsertoUnElemento_SeAgregaAlaTabla();
  UnaTablaHash_SiSuperaFactorDeCarga_Rehashea();
  UnaTablaHash_SiInsertoUnElementoConMismaClave_SobreEscribeElElemento();
  pa2m_nuevo_grupo("Obtener elemento en la tabla de hash");
  UnaTablaDeHash_SiSeBuscaUnElementoInsertado_SeEncuentra();
  UnaTablaDeHash_SiSeBuscaUnElementoNoInsertado_NoSeEncuentraElElemento();
  return pa2m_mostrar_reporte();
}
