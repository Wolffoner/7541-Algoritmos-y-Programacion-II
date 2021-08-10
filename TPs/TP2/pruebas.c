#include "pa2mm.h"
#include "src/entrenador.h"
#include "src/lista.h"
#include "src/pokemon.h"
#include "src/salon.h"


void salon_leer_archivo_inexistente_devuelve_null(){
  salon_t* salon = NULL;

  pa2m_afirmar((salon = salon_leer_archivo("./archivos_prueba/asdasdasdasdasdasdasd.asd")) == NULL, "Leer un archivo inexistente devuelve un salon nulo.");
}

void salon_leer_archivo_carga_correctamente_un_archivo_con_1e_y_1p(){
  salon_t* salon = NULL;
  salon = salon_leer_archivo("./salones/salon_1e_1p.txt");
  pa2m_afirmar(salon != NULL, "Puedo leer un archivo con 1 entrenador y 1 pokemon.");
  salon_destruir(salon);
}

void salon_leer_archivo_carga_correctamente_un_archivo_con_2e_y_2p(){
  salon_t* salon = NULL;
  salon = salon_leer_archivo("./salones/salon_2e_2p.txt");
  pa2m_afirmar(salon != NULL, "Puedo leer un archivo con 2 entrenadores y 2 pokemon cada uno.");
  salon_destruir(salon);
}

void salon_leer_archivo_existente(){
  salon_t* salon = NULL;

  pa2m_afirmar((salon = salon_leer_archivo("./salones/salon_3e.txt")) == NULL, "No se puede leer un archivo con solo entrenadores.");
  salon_destruir(salon);
}

void salon_leer_archivo_entrenadores_duplicados(){
  salon_t* salon = NULL;
  pa2m_afirmar((salon = salon_leer_archivo("./salones/salon_duplicados.txt")) == NULL, "No se puede leer un archivo con entrenadores duplicados.");
  salon_destruir(salon);
}

void salonGuardar_SiArchivoEsNull_NoPuedeGuardar(){
  salon_t* salon = NULL;
  int test = salon_guardar_archivo(salon, "./salones/prueba.txt");
  pa2m_afirmar(test == -1, "No se puede guardar archivo de un salon nulo.")
}

void salonGuardar_SiNombreArchivoNulo_NoPuedeGuardar(){
  salon_t* salon = salon_leer_archivo("./salones/salon_3e.txt");
  int test = salon_guardar_archivo(salon, NULL);
  pa2m_afirmar(test == -1, "No se puede guardar archivo sin nombre de archivo de destino.");
  salon_destruir(salon);
}

void salonGuardar_Guarda_GuardaCorrectmaente(){
  salon_t* salon = salon_leer_archivo("./salones/salon_1e_1p.txt");
  char* ruta = "./archivos/prueba1.txt";
  int test = salon_guardar_archivo(salon, ruta);
  pa2m_afirmar(test == 0, "Se pudo guardar archivo con exito.");
  salon_destruir(salon);
}

void salonGuardar_Guarda_GuardaCorrectmaente2Entrenadores(){
  salon_t* salon = salon_leer_archivo("./salones/salon_2e_2p.txt");
  char* ruta = "./archivos/prueba2.txt";
  int test = salon_guardar_archivo(salon, ruta);
  pa2m_afirmar(test == 0, "Se pudo guardar archivo con 2 entrenadores con exito.");
  salon_destruir(salon);
}

void salonAgregaEntrenador_SiSalonEsNulo_NoSeAgrega(){
  salon_t* salon = NULL;
  entrenador_t* entrenador = crea_entrenador("Leandro");
  salon_t* salon_agregado = salon_agregar_entrenador(salon, entrenador);
  pa2m_afirmar(!salon_agregado, "No se puede agregar entrenador a un salon nulo.");
  destruye_entrenador(entrenador);
}

void salonAgregaEntrenador_SiEntrenadorEsNulo_NoSeAgrega(){
  salon_t* salon = salon_leer_archivo("./salones/salon_2e_2p.txt");
  salon_t* salon_agregado = salon_agregar_entrenador(salon, NULL);
  pa2m_afirmar(!salon_agregado, "No se puede agregar entrenador nulo a un salon.");
  salon_destruir(salon);
}

void salonAgregaEntrenador_SiNoTienePokemones_NoAgrega(){
  salon_t* salon = salon_leer_archivo("./salones/salon_2e_2p.txt");
  entrenador_t* entrenador = crea_entrenador("Leandro");
  salon_t* salon_agregado = salon_agregar_entrenador(salon, entrenador);
  pa2m_afirmar(!salon_agregado, "No se puede agregar un entrenador sin pokemones.");
  destruye_entrenador(entrenador);
  salon_destruir(salon);
 
}

void salonAgregaEntrenador_Agrega_AgregaCorrectamente(){
  salon_t* salon = salon_leer_archivo("./salones/salon_2e_2p.txt");
  entrenador_t* entrenador = crea_entrenador("Leandro");
  pokemon_t* pokemon = crea_pokemon("Moltres");
  agregar_pokemon(entrenador, pokemon);
  salon_t* salon_agregado = salon_agregar_entrenador(salon, entrenador);
  pa2m_afirmar(salon_agregado == salon, "Se agrego un entrenador con exito.");
  salon_destruir(salon);
}

bool entrenador_tiene_min_2pokemones(entrenador_t* entrenador, void* extra){
  if(!entrenador)
    return false;
  if(cantidad_pokemones(entrenador) >= 2){
    return true;
  }
  return false;
}

void salonFiltrar_SiSalonEsNulo_NoSePuedeFiltrar(){
  salon_t* salon = NULL;
  lista_t* lista = salon_filtrar_entrenadores(salon, entrenador_tiene_min_2pokemones, NULL);
  pa2m_afirmar(!lista, "No se puede filtrar si el salon es nulo.");
}

void salonFiltrar_SalonDistintoNulo_SePuedeFiltrar(){
  salon_t* salon = salon_leer_archivo("./salones/salon_2e_2p.txt");
  lista_t* lista = salon_filtrar_entrenadores(salon, entrenador_tiene_min_2pokemones, NULL);
  pa2m_afirmar(lista, "Se pudo filtrar con exito.");
  pa2m_afirmar(lista_elementos(lista) == 2, "La lista tiene 2 entrenadores.");
  lista_destruir(lista);
  salon_destruir(salon);
}

void salonEjecutar_EjecutaQuitarPokemon_SiTieneUnoSoloRetornaNull(){
  salon_t* salon = salon_leer_archivo("./salones/salon_quitar.txt");
  char* res = salon_ejecutar_comando(salon, "QUITAR:Mariano,Lapras");
  pa2m_afirmar(!res, "No se puede quitar si le queda un solo pokemon.");
  salon_destruir(salon);
}
void salonEjecutar_ComandoInvalido_RetornaNull(){
  salon_t* salon = salon_leer_archivo("./salones/salon_quitar.txt");
  char* res = salon_ejecutar_comando(salon, "EN");
  pa2m_afirmar(!res, "No se puede ejecutar comando Nulo.");
  salon_destruir(salon);
}
int main(){
  pa2m_nuevo_grupo("Pruebas Salon");
  pa2m_nuevo_grupo("Salon Leer Archivo");
  salon_leer_archivo_inexistente_devuelve_null();
  salon_leer_archivo_existente();
  salon_leer_archivo_carga_correctamente_un_archivo_con_1e_y_1p();
  salon_leer_archivo_carga_correctamente_un_archivo_con_2e_y_2p();
  salon_leer_archivo_entrenadores_duplicados();
  pa2m_nuevo_grupo("Salon Guardar Archivo");
  salonGuardar_SiArchivoEsNull_NoPuedeGuardar();
  salonGuardar_SiNombreArchivoNulo_NoPuedeGuardar();
  salonGuardar_Guarda_GuardaCorrectmaente();
  salonGuardar_Guarda_GuardaCorrectmaente2Entrenadores();
  pa2m_nuevo_grupo("Salon Agrega Entrenador");
  salonAgregaEntrenador_SiSalonEsNulo_NoSeAgrega();
  salonAgregaEntrenador_SiEntrenadorEsNulo_NoSeAgrega();
  salonAgregaEntrenador_SiEntrenadorEsNulo_NoSeAgrega();
  salonAgregaEntrenador_Agrega_AgregaCorrectamente();
  pa2m_nuevo_grupo("Salon filtrar entrenadores");
  salonFiltrar_SiSalonEsNulo_NoSePuedeFiltrar();
  salonFiltrar_SalonDistintoNulo_SePuedeFiltrar();
  pa2m_nuevo_grupo("Salon Comandos");
  salonEjecutar_EjecutaQuitarPokemon_SiTieneUnoSoloRetornaNull();
  salonEjecutar_ComandoInvalido_RetornaNull();
  return pa2m_mostrar_reporte();
}
