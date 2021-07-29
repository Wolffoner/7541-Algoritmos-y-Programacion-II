#include "../pa2mm.h"
#include "../src/pokemon.h"
#include <string.h>

void CreaPokemon_SiNombreEsNuLL_NoCreaPokemon(){
  pokemon_t* pokemon = crea_pokemon(NULL);
  pa2m_afirmar(!pokemon, "Pokemon no fue creado.");
  destruye_pokemon(pokemon);
}

void CreaPokemon_SiNombreEsDistintoNuLL_CreaPokemon(){
  pokemon_t* pokemon = crea_pokemon("Moltres");
  pa2m_afirmar(pokemon, "Pokemon fue creado con exito.");
  destruye_pokemon(pokemon);
}

void CargaPokemon_SiNombreEsNull_NoCargaPokemon(){
  pokemon_t* pokemon = cargar_pokemon(NULL, 1, 1, 1, 1, 1);
  pa2m_afirmar(!pokemon, "Pokemon no se pudo cargar.");
  destruye_pokemon(pokemon);
}

void CargaPokemon_SiNombreEsDistintoNull_CargaPokemon(){
  pokemon_t* pokemon = cargar_pokemon("Moltres", 1, 1, 1, 1, 1);
  pa2m_afirmar(pokemon, "Pokemon se pudo cargar con exito.");
  destruye_pokemon(pokemon);
}

void ObtenerNombre_DePokemon_ObtieneElNombre(){
  pokemon_t* pokemon = cargar_pokemon("Moltres", 1, 1, 1, 1, 1);
  char* test = obtener_nombre(pokemon);
  pa2m_afirmar(strcmp(test, "Moltres") == 0, "Se obtuvo el nombre del pokemon con exito.");
  destruye_pokemon(pokemon);
}

void ObtenerNombre_DeNull_RetornaNull(){
  pokemon_t* pokemon = cargar_pokemon(NULL, 1, 1, 1, 1, 1);
  char* test = obtener_nombre(pokemon);
  pa2m_afirmar(!test, "El pokemon es nulo.");
  destruye_pokemon(pokemon);
}

void CambiarNivel_Pokemon_CambiaNivel(){
  pokemon_t* pokemon = cargar_pokemon("Moltres", 1, 1, 1, 1, 1);
  int test = obtener_nivel(pokemon);
  pa2m_afirmar(test == 1, "El pokemon es inicialmente nivel 1.")
  modificar_nivel(pokemon, 12);
  test = obtener_nivel(pokemon);
  pa2m_afirmar(test == 12, "Ahora el pokemon es nivel 12.");
  destruye_pokemon(pokemon);
}

void SiPokemonNulo_ObtieneNivel_DaError(){
  pokemon_t* pokemon = NULL;
  int test = obtener_nivel(pokemon);
  pa2m_afirmar(test == -1, "No se puede obtener el nivel de un pokemon nulo.")
  destruye_pokemon(pokemon);
}

void CambiarFuerza_Pokemon_CambiaFuerza(){
  pokemon_t* pokemon = cargar_pokemon("Moltres", 1, 1, 1, 1, 1);
  int test = obtener_fuerza(pokemon);
  pa2m_afirmar(test == 1, "El pokemon tiene inicialmente fuerza 1.")
  modificar_fuerza(pokemon, 40);
  test = obtener_fuerza(pokemon);
  pa2m_afirmar(test == 40, "Ahora el pokemon tiene fuerza 40.");
  destruye_pokemon(pokemon);
}

void SiPokemonNulo_ObtieneFuerza_DaError(){
  pokemon_t* pokemon = NULL;
  int test = obtener_fuerza(pokemon);
  pa2m_afirmar(test == -1, "No se puede obtener la fuerza de un pokemon nulo.")
  destruye_pokemon(pokemon);
}

void CambiarInteligencia_Pokemon_CambiaInteligencia(){
  pokemon_t* pokemon = cargar_pokemon("Moltres", 1, 1, 1, 1, 1);
  int test = obtener_inteligencia(pokemon);
  pa2m_afirmar(test == 1, "El pokemon tiene inicialmente inteligencia 1.")
  modificar_inteligencia(pokemon, 20);
  test = obtener_inteligencia(pokemon);
  pa2m_afirmar(test == 20, "Ahora el pokemon tiene inteligencia 20.");
  destruye_pokemon(pokemon);
}

void SiPokemonNulo_ObtieneInteligencia_DaError(){
  pokemon_t* pokemon = NULL;
  int test = obtener_inteligencia(pokemon);
  pa2m_afirmar(test == -1, "No se puede obtener la inteligencia de un pokemon nulo.")
  destruye_pokemon(pokemon);
}

void CambiarVelocidad_Pokemon_CambiaVelocidad(){
  pokemon_t* pokemon = cargar_pokemon("Moltres", 1, 1, 1, 1, 1);
  int test = obtener_velocidad(pokemon);
  pa2m_afirmar(test == 1, "El pokemon tiene inicialmente velocidad 1.")
  modificar_velocidad(pokemon, 200);
  test = obtener_velocidad(pokemon);
  pa2m_afirmar(test == 200, "Ahora el pokemon tiene velocidad 200.");
  destruye_pokemon(pokemon);
}

void SiPokemonNulo_ObtieneVelocidad_DaError(){
  pokemon_t* pokemon = NULL;
  int test = obtener_velocidad(pokemon);
  pa2m_afirmar(test == -1, "No se puede obtener la velocidad de un pokemon nulo.")
  destruye_pokemon(pokemon);
}

void CambiarDefensa_Pokemon_CambiaDefensa(){
  pokemon_t* pokemon = cargar_pokemon("Moltres", 1, 1, 1, 1, 1);
  int test = obtener_defensa(pokemon);
  pa2m_afirmar(test == 1, "El pokemon tiene inicialmente defensa 1.")
  modificar_defensa(pokemon, 3000);
  test = obtener_defensa(pokemon);
  pa2m_afirmar(test == 3000, "Ahora el pokemon tiene defensa 3000.");
  destruye_pokemon(pokemon);
}

void SiPokemonNulo_ObtieneDefensa_DaError(){
  pokemon_t* pokemon = NULL;
  int test = obtener_defensa(pokemon);
  pa2m_afirmar(test == -1, "No se puede obtener la defensa de un pokemon nulo.")
  destruye_pokemon(pokemon);
}


int main(){
    pa2m_nuevo_grupo("Test Pokemones");
    pa2m_nuevo_grupo("Crea Pokemon");
    CreaPokemon_SiNombreEsNuLL_NoCreaPokemon();
    CreaPokemon_SiNombreEsDistintoNuLL_CreaPokemon();
    pa2m_nuevo_grupo("Carga Pokemon");
    CargaPokemon_SiNombreEsNull_NoCargaPokemon();
    CargaPokemon_SiNombreEsDistintoNull_CargaPokemon();
    pa2m_nuevo_grupo("Obtener Nombre Pokemon");
    ObtenerNombre_DePokemon_ObtieneElNombre();
    ObtenerNombre_DeNull_RetornaNull();
    pa2m_nuevo_grupo("Obtener/Modificar Nivel Pokemon");
    CambiarNivel_Pokemon_CambiaNivel();
    SiPokemonNulo_ObtieneNivel_DaError();
    pa2m_nuevo_grupo("Obtener/Modificar Fuerza Pokemon");
    CambiarFuerza_Pokemon_CambiaFuerza();
    SiPokemonNulo_ObtieneFuerza_DaError();
    pa2m_nuevo_grupo("Obtener/Modificar Inteligencia Pokemon");
    CambiarInteligencia_Pokemon_CambiaInteligencia();
    SiPokemonNulo_ObtieneInteligencia_DaError();
    pa2m_nuevo_grupo("Obtener/Modificar Velocidad Pokemon");
    CambiarVelocidad_Pokemon_CambiaVelocidad();
    SiPokemonNulo_ObtieneVelocidad_DaError();
    pa2m_nuevo_grupo("Obtener/Modificar Defensa Pokemon");
    CambiarDefensa_Pokemon_CambiaDefensa();
    SiPokemonNulo_ObtieneDefensa_DaError();
    return pa2m_mostrar_reporte();
}
