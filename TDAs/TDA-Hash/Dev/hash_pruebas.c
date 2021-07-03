#include "hash.h"
#include <stdio.h>
#include "pa2mm.h"

void CrearUnHash_ConCapacidadMenorATres_CreaUnHashConCapacidadTres(){
  hash_t* tabla = NULL;
  tabla = hash_crear(NULL, 0);
  pa2m_afirmar(tabla, "Tabla de hash es creada con capacidad menor a 3");
  hash_destruir(tabla);
}

void CrearUnHash_ConCapacidadMayorATres_CreaUnHashConEsaCapacidad(){
  hash_t* tabla = NULL;
  tabla = hash_crear(NULL, 10);
  pa2m_afirmar(tabla, "Tabla de hash es creada con capacidad mayor a 3");
  hash_destruir(tabla);
}


int main(){
  pa2m_nuevo_grupo("Creacion de tabla de hash");
  CrearUnHash_ConCapacidadMenorATres_CreaUnHashConCapacidadTres();
  CrearUnHash_ConCapacidadMayorATres_CreaUnHashConEsaCapacidad();
  return pa2m_mostrar_reporte();
}
