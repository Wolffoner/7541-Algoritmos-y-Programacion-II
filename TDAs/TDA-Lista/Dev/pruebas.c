#include "lista.h"
#include "pa2mm.h"

void dadaUnaCreacionDeLista_SiDevuelveUnPunteroDistintoNull_EntoncesSeCreaCorrectamente(){
  lista_t* lista_creada = lista_crear();
  pa2m_afirmar(lista_creada != NULL, "La lista se creo correctamente.");
  pa2m_afirmar(lista_creada->cantidad == 0 &&
                lista_creada->nodo_fin == NULL &&
                lista_creada->nodo_inicio == NULL, "La lista esta inicializada correctamente.");
  lista_destruir(lista_creada);
}

void dadaUnaLista_SiSeInsertaUnElemento_EntoncesDevuelveCero(){
  lista_t* lista_creada = lista_crear();
  void* elemento = (void*)0xBEBECAFE;
  int pudo_insertar = lista_insertar(lista_creada, elemento);
  pa2m_afirmar(pudo_insertar == 0, "Puede insertar un elemento distinto de Nulo.");
  lista_destruir(lista_creada);
}

void dadaUnaLista_SiSeInsertanVariosElementos_EntoncesNoSeSobreEscriben(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAFE;
  void* elemento2 = (void*)0xBEBECAF1;
  void* elemento3 = NULL;
  int test1 = lista_insertar(lista_creada, elemento1);
  int test2 = lista_insertar(lista_creada, elemento2);
  int test3 = lista_insertar(lista_creada, elemento3);
  pa2m_afirmar(test1 == 0 && lista_creada->nodo_inicio->elemento == elemento1, "El primer elemento agregado esta al inicio de la lista.");
  pa2m_afirmar(test2 == 0 && lista_creada->nodo_inicio->siguiente->elemento == elemento2, "El segundo elemento agregado es el siguiente al inicio de la lista.");
  pa2m_afirmar(test3 == 0 && lista_creada->nodo_fin->elemento == elemento3, "El ultimo elemento agregado esta al final de la lista.");
  pa2m_afirmar(lista_creada->nodo_fin->siguiente == NULL, "El nodo final de la lista su siguiente puntero es NULL.");
  pa2m_afirmar(lista_creada->cantidad == 3, "La lista tiene 3 nodos de elementos.");
  lista_destruir(lista_creada);
}

void dadaUnaLista_SiSeInsertanElementosEnPosicionesEspecificas_EntoncesSeAgregaEnLista(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = NULL;
  void* elemento2 = (void*)0xBEBECAF1;
  void* elemento3 = (void*)0xBEBECAF2;
  void* elemento4 = (void*)0xBEBECAF3;
  int test1 = lista_insertar_en_posicion(lista_creada, elemento1, 1);
  pa2m_afirmar(test1 == 0, "El elemento1 puede ser agregado a la lista");
  int test2 = lista_insertar_en_posicion(lista_creada, elemento2, 20);
  pa2m_afirmar(test2 == 0 && lista_creada->nodo_fin->elemento == elemento2, "La Posicion a la que quiere insertar el elemento2 es mayor a la cantidad de elementos que hay en la lista, Se agregara al final de la lista.");
  int test3 = lista_insertar_en_posicion(lista_creada, elemento3, 1);
  pa2m_afirmar(test3 == 0 && lista_creada->nodo_inicio->siguiente->elemento == elemento3, "El elemento3 se añadio a la lista en la posicion 1.");
  int test4 = lista_insertar_en_posicion(lista_creada, elemento4, 0);
  pa2m_afirmar(test4 == 0 && lista_creada->nodo_inicio->elemento == elemento4, "El elemento4 se añadio a la lista en la posicion 0.");
  pa2m_afirmar(lista_creada->nodo_fin->elemento == elemento2, "El elemento final es el elemento3.");
  pa2m_afirmar(lista_creada->cantidad == 4, "La lista tiene 3 elementos.");
  lista_destruir(lista_creada);
}

void dadaUnaLista_SiseBorranElementos_EntoncesSeBorranElementos(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  void* elemento2 = (void*)0xBEBECAF2;
  void* elemento3 = (void*)0xBEBECAF3;
  
  lista_insertar(lista_creada, elemento1);
  lista_insertar(lista_creada, elemento2);
  lista_insertar(lista_creada, elemento3);
  int test1 = lista_borrar(lista_creada);
  pa2m_afirmar(test1 == 0 && lista_creada->nodo_fin->elemento == elemento2, "Se elimino el ultimo elemento, y ahora el elemento2 es el final de la lista.");
  int test2 = lista_borrar(lista_creada);
  pa2m_afirmar(test2 == 0 && lista_creada->nodo_inicio->elemento == elemento1 && lista_creada->nodo_fin->elemento == elemento1, "Se elimino el ultimo elemento, y ahora el elemento1 es el incio y el final de la lista.");
  int test3 = lista_borrar(lista_creada);
  pa2m_afirmar(test3 == 0, "Se elimino el ultimo elemento de la lista, y ahora la lista esta vacia.");
  int test4 = lista_borrar(lista_creada);
  pa2m_afirmar(test4 != 0, "No se elimino ningun elemento porque la lista esta vacia.");
  lista_destruir(lista_creada);
}

void dadaUnaLista_SiseBorranElementosEnPosicionesEspecificas_EntoncesSeBorranElementosEnPosicionesEspecificas(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  void* elemento2 = (void*)0xBEBECAF2;
  void* elemento3 = (void*)0xBEBECAF3;
  void* elemento4 = (void*)0xBEBECAF4;
  void* elemento5 = (void*)0xBEBECAF5;
  void* elemento6 = (void*)0xBEBECAF6;
  
  lista_insertar(lista_creada, elemento1);
  lista_insertar(lista_creada, elemento2);
  lista_insertar(lista_creada, elemento3);
  lista_insertar(lista_creada, elemento4);
  lista_insertar(lista_creada, elemento5);
  lista_insertar(lista_creada, elemento6);
  int test1 = lista_borrar_de_posicion(lista_creada, 3);
  pa2m_afirmar(test1 == 0 && lista_creada->nodo_inicio->siguiente->siguiente->siguiente->elemento == elemento5, "Se elimino el elemento4 que estaba en la posicion 3 y ahora el elemento5 esta en la posicion 3.");
  int test2 = lista_borrar_de_posicion(lista_creada, 0);
  pa2m_afirmar(test2 == 0 && lista_creada->nodo_inicio->elemento == elemento2, "Se elimino el nodo inicial y ahora el elemento2 esta en la posicion del nodo inicial.");
  int test3 = lista_borrar_de_posicion(lista_creada, 3);
  pa2m_afirmar(test3 == 0 && lista_creada->nodo_fin->elemento == elemento5, "Se elimino el nodo final y ahora el elemento5 esta en la posicion del nodo final.");
  pa2m_afirmar(lista_creada->cantidad == 3, "Se eliminaron 3 elementos de la lista, ahora la lista tiene 3 elementos.");
  lista_destruir(lista_creada);
}

void dadaUnaLista_SiSeBuscaUnElementoPorPosicion_EntoncesSeEncuentraElElemento(){
  lista_t* lista_creada = lista_crear();
  void* test1 = lista_elemento_en_posicion(lista_creada, 0);
  pa2m_afirmar(test1 == NULL, "La lista no encuentra la posicion indicada.");

  void* elemento1 = (void*)0xBEBECAF1;
  void* elemento2 = (void*)0xBEBECAF2;
  void* elemento3 = (void*)0xBEBECAF3;
 
  lista_insertar(lista_creada, elemento1);
  lista_insertar(lista_creada, elemento2);
  lista_insertar(lista_creada, elemento3);
  
  void* test2 = lista_elemento_en_posicion(lista_creada, 0);
  pa2m_afirmar(test2 != NULL, "La lista encuentra la posicion y retorna el elemento.");

  void* test3 = lista_elemento_en_posicion(lista_creada, 3);
  pa2m_afirmar(test3 == NULL, "La posicion indicada es mayor a las posiciones de los nodos donde estan los elementos.");
  lista_destruir(lista_creada);
}

void dadaUnaLista_SiSeBuscaElUltimoElementodeLaLista_RetornaElUltimoElemento(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  void* ultimo = lista_ultimo(lista_creada);
  pa2m_afirmar( ultimo == NULL, "La lista esta vacia por lo que no tiene un ultimo elemento.");
  lista_insertar(lista_creada, elemento1);
  ultimo = lista_ultimo(lista_creada);
  pa2m_afirmar(ultimo == lista_creada->nodo_fin->elemento, "El ultimo elemento de la lista es un elemento.");
  lista_destruir(lista_creada);
}

void dadaUnaLista_NoEstaVacia_SitieneUnUltimoElemento(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  pa2m_afirmar(lista_vacia(lista_creada), "La lista esta vacia.");
  lista_insertar(lista_creada, elemento1);
  pa2m_afirmar(!lista_vacia(lista_creada), "La lista no esta vacia.");
  lista_destruir(lista_creada);
}

void dadaUnaLista_SiTieneElementos_TieneUnaCantidadDeElementos(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  void* elemento2 = (void*)0xBEBECAF2;
  void* elemento3 = (void*)0xBEBECAF3;
  void* elemento4 = (void*)0xBEBECAF4;
  size_t test = lista_elementos(lista_creada);
  pa2m_afirmar(test == 0 , "La lista tiene 0 elementos.");
  lista_insertar(lista_creada, elemento1);
  lista_insertar(lista_creada, elemento2);
  lista_insertar(lista_creada, elemento3);
  lista_insertar(lista_creada, elemento4);
  size_t test2 = lista_elementos(lista_creada);
  pa2m_afirmar(test2 == 4, "La lista ahora tiene 4 elementos.");
  lista_destruir(lista_creada);
}

void dadaUnaListaVacia_SiSeApilaUnElemento_EsElNodoFinalEInicioDelElemento(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  int test1 = lista_apilar(lista_creada, elemento1);
  pa2m_afirmar( test1 == 0 && lista_creada->nodo_inicio->elemento == elemento1 && lista_creada->nodo_fin->elemento == elemento1, "La lista esta vacia por lo que se apilo al final siendo este elemento el inicio y final de la lista.");
  lista_destruir(lista_creada); 
}


void dadaUnaLista_SiSeApilaUnElemento_ElElementoEstaAlFinalDeLaLista(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  int test1 = lista_apilar(lista_creada, elemento1);
  pa2m_afirmar( test1 == 0 && lista_ultimo(lista_creada) == elemento1, "El ultimo elemento se apilo al final.");
  lista_destruir(lista_creada); 
}

void dadaUnaLista_SiSeApilanVariosElementos_ELUltimoElementoApiladoEsElUltimoEnApilarse(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  void* elemento2 = (void*)0xBEBECAF2;
  void* elemento3 = (void*)0xBEBECAF3;
  lista_apilar(lista_creada, elemento1);
  lista_apilar(lista_creada, elemento2);
  int test3 = lista_apilar(lista_creada, elemento3);
  pa2m_afirmar( test3 == 0 && lista_ultimo(lista_creada) == elemento3, "El ultimo elemento apilado es el elemento3.");
  lista_destruir(lista_creada);
}


void dadaUnaListaVacia_SiSeDesapilaUnElemento_NoDesapilaNada(){
  lista_t* lista_creada = lista_crear();
  int test1 = lista_desapilar(lista_creada);
  pa2m_afirmar( test1 != 0, "La lista esta vacia por lo que no se puede desapilar.");
  lista_destruir(lista_creada); 
}

void dadaUnaListaConUnElemento_SiSeDesapilaUnElemento_LaListaQuedaVacia(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  lista_apilar(lista_creada, elemento1);
  int test1 = lista_desapilar(lista_creada);
  pa2m_afirmar( test1 == 0 && lista_vacia(lista_creada), "Se Desapilo el unico elemento, ahora la lista esta vacia.");
  lista_destruir(lista_creada); 
}

void dadaUnaListaVacia_SiSeEncolaUnElemento_SeAgregaUnElementoALaLista(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  int test1 = lista_encolar(lista_creada, elemento1);
  pa2m_afirmar( test1 == 0 && lista_creada->nodo_inicio->elemento == elemento1 && lista_creada->nodo_fin->elemento == elemento1, "La lista esta vacia por lo que se encolo al final siendo este elemento el inicio y final de la lista.");
  lista_destruir(lista_creada);
}


void dadaUnaLista_SiSeEncolanVariosElementos_ElUltimoElementoEncoladoEstaAlFinalDeLaLista(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  void* elemento2 = (void*)0xBEBECAF2;
  void* elemento3 = (void*)0xBEBECAF3;
  lista_encolar(lista_creada, elemento1);
  lista_encolar(lista_creada, elemento2);
  int test3 = lista_encolar(lista_creada, elemento3);
  pa2m_afirmar( test3 == 0 && lista_ultimo(lista_creada) == elemento3, "El ultimo elemento encolado es el elemento3.");
  lista_destruir(lista_creada);
}

void dadaUnaListaVacia_SiSeDesencolaUnElemento_NoDesencolaNada(){
  lista_t* lista_creada = lista_crear();
  int test1 = lista_desencolar(lista_creada);
  pa2m_afirmar( test1 != 0, "La lista esta vacia por lo que no se puede desencolar.");
  lista_destruir(lista_creada); 
}

void dadaUnaListaConUnElemento_SiSeDesencolaUnElemento_LaListaQuedaVacia(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  lista_encolar(lista_creada, elemento1);
  int test1 = lista_desencolar(lista_creada);
  pa2m_afirmar( test1 == 0 && lista_vacia(lista_creada), "Se Desencolo el unico elemento, ahora la lista esta vacia.");
  lista_destruir(lista_creada); 
}

void dadaUnaLista_SiSeDesencolanVariosElementos_ElUltimoElementoEncoladoEstaMasCercaDeSerDesencolado(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  void* elemento2 = (void*)0xBEBECAF2;
  void* elemento3 = (void*)0xBEBECAF3;
  lista_encolar(lista_creada, elemento1);
  lista_encolar(lista_creada, elemento2);
  lista_encolar(lista_creada, elemento3);

  lista_desencolar(lista_creada);
  int test1 = lista_desencolar(lista_creada);
  pa2m_afirmar( test1 == 0 && lista_primero(lista_creada) == elemento3, "El primer elemento para desencolar es el elemento3.");
  lista_destruir(lista_creada);
}

void dadaUnaListaNula_SiSeIntentaCrearUnIterador_NoSeCreaNingunIterador(){
  lista_t* lista_creada = NULL;
  lista_iterador_t* iterador = lista_iterador_crear(lista_creada);
  pa2m_afirmar(iterador == NULL, "La lista es nula entonces no se crea ningun iterador.");
}

void dadaUnaLista_SiSeIntentaCrearUnIterador_SeCreaUnIterador(){
  lista_t* lista_creada = lista_crear();
  lista_iterador_t* iterador = lista_iterador_crear(lista_creada);
  pa2m_afirmar(iterador != NULL, "Se Creo un iterador correctamente.");
  lista_iterador_destruir(iterador);
  lista_destruir(lista_creada);
}


void dadoUnIterador_SiTieneSiguiente_LaListaTieneNodosAnidados(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  void* elemento2 = (void*)0xBEBECAF2;
  void* elemento3 = (void*)0xBEBECAF3;
  lista_insertar(lista_creada, elemento1);
  lista_insertar(lista_creada, elemento2);
  lista_insertar(lista_creada, elemento3);
  lista_iterador_t* iterador = lista_iterador_crear(lista_creada);
  bool test1 = lista_iterador_tiene_siguiente(iterador);
  pa2m_afirmar(test1, "El iterador tiene siguiente por lo que la lista tiene nodos de elementos anidados.");
  lista_iterador_destruir(iterador);
  lista_destruir(lista_creada);
}

void dadoUnIterador_SiTieneSiguiente_PuedeAvanzarElIterador(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  void* elemento2 = (void*)0xBEBECAF2;
  void* elemento3 = (void*)0xBEBECAF3;
  lista_insertar(lista_creada, elemento1);
  lista_insertar(lista_creada, elemento2);
  lista_insertar(lista_creada, elemento3);
  lista_iterador_t* iterador = lista_iterador_crear(lista_creada);
  bool test1 = lista_iterador_tiene_siguiente(iterador);
  bool test2 = lista_iterador_avanzar(iterador);
  pa2m_afirmar(test1 && test2, "El iterador tiene siguiente por lo que puede avanzar");
  lista_iterador_destruir(iterador);
  lista_destruir(lista_creada);
}

void dadoUnIterador_SiNoTieneSiguiente_NoPuedeAvanzar(){
  lista_t* lista_creada = lista_crear();
  lista_iterador_t* iterador = lista_iterador_crear(lista_creada);
  bool test1 = lista_iterador_avanzar(iterador);
  pa2m_afirmar(!test1, "El iterador no puede avanzar ya que no tiene siguiente");
  lista_iterador_destruir(iterador);
  lista_destruir(lista_creada);
}

void dadoUnIterador_SiEstaEnUnaPosicionDentroDeLaLista_TieneElementoActual(){
  lista_t* lista_creada = lista_crear();
  void* elemento1 = (void*)0xBEBECAF1;
  void* elemento2 = (void*)0xBEBECAF2;
  void* elemento3 = (void*)0xBEBECAF3;
  lista_insertar(lista_creada, elemento1);
  lista_insertar(lista_creada, elemento2);
  lista_insertar(lista_creada, elemento3);
  lista_iterador_t* iterador = lista_iterador_crear(lista_creada);
  void* test1 = lista_iterador_elemento_actual(iterador);
  pa2m_afirmar(test1 != NULL, "El iterador esta sobre un elemento.");
  lista_iterador_destruir(iterador);
  lista_destruir(lista_creada);
}

bool multiplicacion(void* numero, void* total) {
    int* numero1 = numero;
    int* resultado = total;
    if(*resultado == 0)
      *resultado = 1;
    if (numero1)
        *resultado = *resultado * *numero1;
    return true;
}

void DadaUnaLista_SiSeMultiplicanLosElementosConUnIteradorIntero_MultiplicaLosElementos(){
  lista_t* lista_creada = lista_crear();
  int elem1 = 1;
  void* elemento1 = &elem1;
  int elem2 = 2;
  void* elemento2 = &elem2;
  int elem3 = 3;
  void* elemento3 = &elem3;
  lista_insertar(lista_creada, elemento1);
  lista_insertar(lista_creada, elemento2);
  lista_insertar(lista_creada, elemento3);
  size_t cantidad_elementos = lista_elementos(lista_creada);
  int total = 0;
  size_t test = lista_con_cada_elemento(lista_creada, multiplicacion, &total);
  pa2m_afirmar(test == cantidad_elementos, "El iterador recorrio todos los elementos.");
  pa2m_afirmar(total == (elem1*elem2*elem3), "El total coincide con los elementos multiplicados de la lista.");
  lista_destruir(lista_creada);
}

int main() {
  pa2m_nuevo_grupo("Test Lista");

  pa2m_nuevo_grupo("Creacion de Lista");
  dadaUnaCreacionDeLista_SiDevuelveUnPunteroDistintoNull_EntoncesSeCreaCorrectamente();  

  pa2m_nuevo_grupo("Insercion de Elementos");
  dadaUnaLista_SiSeInsertaUnElemento_EntoncesDevuelveCero();
  dadaUnaLista_SiSeInsertanVariosElementos_EntoncesNoSeSobreEscriben();

  pa2m_nuevo_grupo("Insercion de Elementos por Posicion");
  dadaUnaLista_SiSeInsertanElementosEnPosicionesEspecificas_EntoncesSeAgregaEnLista();

  pa2m_nuevo_grupo("Borrado de Elementos");
  dadaUnaLista_SiseBorranElementos_EntoncesSeBorranElementos();

  pa2m_nuevo_grupo("Borrado de elementos por posicion");
  dadaUnaLista_SiseBorranElementosEnPosicionesEspecificas_EntoncesSeBorranElementosEnPosicionesEspecificas();

  pa2m_nuevo_grupo("Elementos por Posicion");
  dadaUnaLista_SiSeBuscaUnElementoPorPosicion_EntoncesSeEncuentraElElemento();

  pa2m_nuevo_grupo("Ultimo Elemento - Lista Vacia - Cantidad de Elementos");
  dadaUnaLista_SiSeBuscaElUltimoElementodeLaLista_RetornaElUltimoElemento();
  printf("=======================================\n");
  dadaUnaLista_NoEstaVacia_SitieneUnUltimoElemento();
  printf("=======================================\n");
  dadaUnaLista_SiTieneElementos_TieneUnaCantidadDeElementos();

  pa2m_nuevo_grupo("Test Pila");

  pa2m_nuevo_grupo("Apila en la Lista");
  dadaUnaListaVacia_SiSeApilaUnElemento_EsElNodoFinalEInicioDelElemento();
  dadaUnaLista_SiSeApilaUnElemento_ElElementoEstaAlFinalDeLaLista();
  dadaUnaLista_SiSeApilanVariosElementos_ELUltimoElementoApiladoEsElUltimoEnApilarse();

  pa2m_nuevo_grupo("Desapila de la Lista");
  dadaUnaListaVacia_SiSeDesapilaUnElemento_NoDesapilaNada();
  dadaUnaListaConUnElemento_SiSeDesapilaUnElemento_LaListaQuedaVacia();

  pa2m_nuevo_grupo("Test Pila");

  pa2m_nuevo_grupo("Encolar en la Lista");
  dadaUnaListaVacia_SiSeEncolaUnElemento_SeAgregaUnElementoALaLista();
  dadaUnaLista_SiSeEncolanVariosElementos_ElUltimoElementoEncoladoEstaAlFinalDeLaLista();

  pa2m_nuevo_grupo("Desencolar en la Lista");
  dadaUnaListaVacia_SiSeDesencolaUnElemento_NoDesencolaNada();
  dadaUnaListaConUnElemento_SiSeDesencolaUnElemento_LaListaQuedaVacia();
  dadaUnaLista_SiSeDesencolanVariosElementos_ElUltimoElementoEncoladoEstaMasCercaDeSerDesencolado();

  pa2m_nuevo_grupo("Test Iterador Externo");

  pa2m_nuevo_grupo("Crear Iterador");
  dadaUnaListaNula_SiSeIntentaCrearUnIterador_NoSeCreaNingunIterador();
  dadaUnaLista_SiSeIntentaCrearUnIterador_SeCreaUnIterador();

  pa2m_nuevo_grupo("Recorrer Iterador");
  dadoUnIterador_SiTieneSiguiente_LaListaTieneNodosAnidados();
  dadoUnIterador_SiTieneSiguiente_PuedeAvanzarElIterador();
  dadoUnIterador_SiNoTieneSiguiente_NoPuedeAvanzar();

  pa2m_nuevo_grupo("Elemento Iterador");
  dadoUnIterador_SiEstaEnUnaPosicionDentroDeLaLista_TieneElementoActual();

  pa2m_nuevo_grupo("Test Iterador Interno");
  DadaUnaLista_SiSeMultiplicanLosElementosConUnIteradorIntero_MultiplicaLosElementos();
  return pa2m_mostrar_reporte();
}


