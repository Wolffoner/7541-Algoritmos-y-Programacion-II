#include "../pa2mm.h"
#include "../src/entrenador.h"
#include <string.h>

void CreaEntrenador_SiNombreEsNuLL_NoCreaEntrenador(){
  entrenador_t* entrenador = crea_entrenador(NULL);
  pa2m_afirmar(!entrenador, "Entrenador no fue creado.");
  destruye_entrenador(entrenador);
}

int main(){
  pa2m_nuevo_grupo("Test Entrenador");
  pa2m_nuevo_grupo("Crea Entrenador");
  CreaEntrenador_SiNombreEsNuLL_NoCreaEntrenador();
  return pa2m_mostrar_reporte();
}
