#include "../pa2mm.h"
#include "../src/comando.h"
#include <string.h>

void CreaComando_SiNombreEsNull_NoCreaComando(){
  comando_t* comando = comando_crear(NULL, "a", NULL);
  pa2m_afirmar(!comando, "Comando no se puede crear con nombre nulo.");
  comando_destruir(comando);
}

void CreaComando_SiDescripcionEsNull_NoCreaComando(){
  comando_t* comando = comando_crear("test", NULL, NULL);
  pa2m_afirmar(!comando, "Comando no se puede crear con descripcion nula.");
  comando_destruir(comando);
}

void CreaComando_SiEjecutarEsNull_NoCreaComando(){
  comando_t* comando = comando_crear("test", "test", NULL);
  pa2m_afirmar(!comando, "Comando no se puede crear con funcion ejecutar nula.");
  comando_destruir(comando);
}

void funcion_test(void* ptr, char** aux, void* ptr_aux){
}

void CreaComando_ConValoresValidos_CreaComando(){
  comando_t* comando = comando_crear("test", "test", funcion_test);
  pa2m_afirmar(comando, "Comando creado con exito.");
  comando_destruir(comando);
}

void ObtenerEjecutarComando_SiComandoEsNull_NoDevuelveEjecutar(){
  ejecutar_comando_t ejecutar = obtener_ejecutar_comando(NULL);
  pa2m_afirmar(!ejecutar, "No se puede ejecutar porque comando es NULL.");
}

void ObtenerEjecutarComando_SiComandoEsValido_DevuelveEjecutar(){
  comando_t* comando = comando_crear("test", "test", funcion_test);
  ejecutar_comando_t ejecutar = obtener_ejecutar_comando(comando);
  pa2m_afirmar(ejecutar, "Se obtuvo el ejecutar del comando con exito.");
  comando_destruir(comando);
}

void ObtenerNombre_SiComandoEsNull_NoDevuelveNombre(){
  char* nombre = obtener_nombre_comando(NULL);
  pa2m_afirmar(!nombre, "No se puede obtener nombre porque comando es NULL.");
}

void ObtenerNombre_SiComandoEsValido_DevuelveNombre(){
  comando_t* comando = comando_crear("test", "test", funcion_test);
  char* nombre = obtener_nombre_comando(comando);
  pa2m_afirmar(nombre, "Se obtuvo nombre con exito.");
  pa2m_afirmar(strcmp(nombre, "test") == 0, "El nombre es el adecuado.");
  comando_destruir(comando);
}

void ObtenerDescripcion_SiComandoEsNull_NoDevuelveDescripcion(){
  char* descripcion = obtener_descripcion_comando(NULL);
  pa2m_afirmar(!descripcion, "No se puede obtener nombre porque comando es NULL.");
}

void ObtenerDescripcion_SiComandoEsValido_DevuelveDescripcion(){
  comando_t* comando = comando_crear("test", "test", funcion_test);
  char* descripcion = obtener_descripcion_comando(comando);
  pa2m_afirmar(descripcion, "Se obtuvo nombre con exito.");
  pa2m_afirmar(strcmp(descripcion, "test") == 0, "La descripcion es la adecuada.");
  comando_destruir(comando);
}
int main(){
  pa2m_nuevo_grupo("Test Comando");
  pa2m_nuevo_grupo("Crea Comando");
  CreaComando_SiNombreEsNull_NoCreaComando();
  CreaComando_SiDescripcionEsNull_NoCreaComando();
  CreaComando_SiEjecutarEsNull_NoCreaComando();
  CreaComando_ConValoresValidos_CreaComando();
  pa2m_nuevo_grupo("Obtener Ejecutar");
  ObtenerEjecutarComando_SiComandoEsNull_NoDevuelveEjecutar();
  ObtenerEjecutarComando_SiComandoEsValido_DevuelveEjecutar();
  pa2m_nuevo_grupo("Obtener Nombre");
  ObtenerNombre_SiComandoEsNull_NoDevuelveNombre();
  ObtenerNombre_SiComandoEsValido_DevuelveNombre();
  pa2m_nuevo_grupo("Obtener Descripcion");
  ObtenerDescripcion_SiComandoEsNull_NoDevuelveDescripcion();
  ObtenerDescripcion_SiComandoEsValido_DevuelveDescripcion();
  return pa2m_mostrar_reporte();
}
