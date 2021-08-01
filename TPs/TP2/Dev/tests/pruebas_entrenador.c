#include "../pa2mm.h"
#include "../src/entrenador.h"
#include "../src/pokemon.h"
#include "../src/lista.h"
#include <string.h>

void CreaEntrenador_SiNombreEsNuLL_NoCreaEntrenador(){
  entrenador_t* entrenador = crea_entrenador(NULL);
  pa2m_afirmar(!entrenador, "Entrenador no fue creado.");
  destruye_entrenador(entrenador);
}

void CreaEntrenador_SiNombreEsDistintoNull_CreaEntrenador(){
  entrenador_t* entrenador = crea_entrenador("Leandro");
  pa2m_afirmar(entrenador, "Entrenador fue creado con exito.");
  destruye_entrenador(entrenador);
}

void SiEntrenador_EsNULL_NoAgregaPokemon(){
  pokemon_t* pokemon = crea_pokemon("Moltres");
  entrenador_t* entrenador = crea_entrenador(NULL);
  int test = agregar_pokemon(entrenador, pokemon);
  pa2m_afirmar(test == -1, "No se puede agregar un pokemon a un entrenador nulo.");
  destruye_pokemon(pokemon);
  destruye_entrenador(entrenador);
}

void SiEntrenador_AgregaPokemonNULL_NoAgregaPokemon(){
  entrenador_t* entrenador = crea_entrenador("Leandro");
  int test = agregar_pokemon(entrenador, NULL);
  pa2m_afirmar(test == -1, "No se puede agregar un pokemon nulo.");
  destruye_entrenador(entrenador);
}

void SiEntrenador_AgregaPokemonDistintoNULL_AgregaPokemon(){
  pokemon_t* pokemon = crea_pokemon("Moltres");
  entrenador_t* entrenador = crea_entrenador("Leandro");
  int test = agregar_pokemon(entrenador, pokemon);
  pa2m_afirmar(test == 0, "Se agrego un pokemon con exito.");
  int test_cantidad = cantidad_pokemones(entrenador);
  pa2m_afirmar(test_cantidad == 1, "El entrenador tiene 1 pokemon.");
  destruye_entrenador(entrenador);
}

void SiEntrenador_ObtienePokemonNulo_NoDevuelvePokemon(){
  pokemon_t* pokemon = crea_pokemon("Moltres");
  entrenador_t* entrenador = crea_entrenador("Leandro");
  agregar_pokemon(entrenador, pokemon);
  pokemon_t* pokemon_obtenido = obtener_pokemon(entrenador, NULL);
  pa2m_afirmar(pokemon_obtenido == NULL, "No se puede obtener porque pokemon es nulo");
  destruye_entrenador(entrenador);
}

void SiEntrenador_EsNULL_NoObtienePokemon(){
  pokemon_t* pokemon = crea_pokemon("Moltres");
  entrenador_t* entrenador = NULL;
  agregar_pokemon(entrenador, pokemon);
  pokemon_t* pokemon_obtenido = obtener_pokemon(NULL, obtener_nombre(pokemon));
  pa2m_afirmar(pokemon_obtenido == NULL, "No se puede obtener porque entrenador es nulo.");
  destruye_pokemon(pokemon);
  destruye_entrenador(entrenador);
}

void SiEntrenador_ObtienePokemonDistintoNulo_ObtienePokemon(){
  pokemon_t* pokemon = crea_pokemon("Moltres");
  entrenador_t* entrenador = crea_entrenador("Leandro");
  agregar_pokemon(entrenador, pokemon);
  pokemon_t* pokemon_obtenido = obtener_pokemon(entrenador, obtener_nombre(pokemon));
  pa2m_afirmar(strcmp(obtener_nombre(pokemon), obtener_nombre(pokemon_obtenido)) == 0, "Se obtuvo pokemon con exito.");
  destruye_entrenador(entrenador);
}

void SiEntrenador_LiberaPokemonNulo_NoPuedeLiberar(){
  char* nombre_pokemon_buscado = NULL;
  entrenador_t* entrenador = crea_entrenador("Leandro");
  int test = liberar_pokemon(entrenador, nombre_pokemon_buscado);
  pa2m_afirmar(test == -1, "No se puede liberar un Pokemon nulo.");
  destruye_entrenador(entrenador);
}

void SiEntrenadorEsNulo_LiberaPokemon_NoPuedeLiberar(){
  char* nombre_pokemon_buscado = "Moltres";
  entrenador_t* entrenador = NULL;
  int test = liberar_pokemon(entrenador, nombre_pokemon_buscado);
  pa2m_afirmar(test == -1, "No se puede liberar si el entrenador es nulo.");
}

void SiEntrenador_LiberaPokemon_PuedeLiberarlo(){
  char* nombre_pokemon_buscado = "Moltres";
  pokemon_t* pokemon = crea_pokemon("Moltres");
  entrenador_t* entrenador = crea_entrenador("Leandro");
  agregar_pokemon(entrenador, pokemon);
  int test = liberar_pokemon(entrenador, nombre_pokemon_buscado);
  pa2m_afirmar(test != -1, "Se pudo liberar el pokemon con exito.");
  destruye_entrenador(entrenador);
}

void SiEntrenadorTieneVariosPokemones_LiberaPokemon_PuedeLiberarlo(){
  char* nombre_pokemon_buscado = "Articuno";
  pokemon_t* pokemon1 = crea_pokemon("Moltres");
  pokemon_t* pokemon2 = crea_pokemon("Zapdos");
  pokemon_t* pokemon3 = crea_pokemon("Articuno");
  entrenador_t* entrenador = crea_entrenador("Leandro");
  agregar_pokemon(entrenador, pokemon1);
  agregar_pokemon(entrenador, pokemon2);
  agregar_pokemon(entrenador, pokemon3);
  int test = liberar_pokemon(entrenador, nombre_pokemon_buscado);
  pa2m_afirmar(test == 2, "Se pudo liberar el pokemon con exito.");
  int test_cantidad = cantidad_pokemones(entrenador);
  pa2m_afirmar(test_cantidad == 2, "Quedan 2 pokemones del entrenador.");
  destruye_entrenador(entrenador);
}

void SiEntrenadorNulo_ModificaVictorias_NoPuedeModificar(){
  int test = modificar_victorias(NULL, 10);
  pa2m_afirmar(test == -1, "No se puede modificar las victorias de un entrenador nulo.");
}

void SiEntrenador_ModificaVictorias_PuedeModificar(){
  entrenador_t* entrenador = crea_entrenador("Leandro");
  int test = modificar_victorias(entrenador, 10);
  pa2m_afirmar(test == 10, "Se pudo modificar las victorias con exito.");
  destruye_entrenador(entrenador);
}

void SiEntrenadorNulo_ObtieneVictorias_NoPuedeObtener(){
  int test = cantidad_victorias(NULL);
  pa2m_afirmar(test == -1, "No se puede obtener las victorias de un entrenador nulo.");
}

void SiEntrenador_ObtieneVictorias_PuedeObtener(){
  entrenador_t* entrenador = crea_entrenador("Leandro");
  int test = cantidad_victorias(entrenador);
  pa2m_afirmar(test == 0, "Se pudede obtener las victorias de un entrenador con exito.");
  destruye_entrenador(entrenador);
}

int main(){
  pa2m_nuevo_grupo("Test Entrenador");
  pa2m_nuevo_grupo("Crea Entrenador");
  CreaEntrenador_SiNombreEsNuLL_NoCreaEntrenador();
  CreaEntrenador_SiNombreEsDistintoNull_CreaEntrenador();
  pa2m_nuevo_grupo("Inserta pokemon");
  SiEntrenador_AgregaPokemonNULL_NoAgregaPokemon();
  SiEntrenador_EsNULL_NoAgregaPokemon();
  SiEntrenador_AgregaPokemonDistintoNULL_AgregaPokemon();
  pa2m_nuevo_grupo("Obtiene pokemon");
  SiEntrenador_ObtienePokemonNulo_NoDevuelvePokemon();
  SiEntrenador_EsNULL_NoObtienePokemon();
  SiEntrenador_ObtienePokemonDistintoNulo_ObtienePokemon();
  pa2m_nuevo_grupo("Liberar pokemon");
  SiEntrenador_LiberaPokemonNulo_NoPuedeLiberar();
  SiEntrenadorEsNulo_LiberaPokemon_NoPuedeLiberar();
  SiEntrenador_LiberaPokemon_PuedeLiberarlo();
  SiEntrenadorTieneVariosPokemones_LiberaPokemon_PuedeLiberarlo();
  pa2m_nuevo_grupo("Cantidad victorias entrenador");
  SiEntrenadorNulo_ModificaVictorias_NoPuedeModificar();
  SiEntrenador_ModificaVictorias_PuedeModificar();
  SiEntrenadorNulo_ObtieneVictorias_NoPuedeObtener();
  SiEntrenador_ObtieneVictorias_PuedeObtener();
  return pa2m_mostrar_reporte();
}
