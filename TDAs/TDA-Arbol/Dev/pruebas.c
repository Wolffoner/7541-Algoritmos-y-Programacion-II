#include "abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

int compara_numeros(void* _elemento1, void* _elemento2){
  int* elemento1 = (int*) _elemento1;
  int* elemento2 = (int*) _elemento2;
  return (*elemento1-*elemento2);
}

void dadaUnaCreacionDeABB_SiSeLePasaUnComparadorNulo_NoEsPosibleCrearUnABB(){
  abb_comparador comparador = NULL;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  pa2m_afirmar(nuevo_arbol == NULL, "El Arbol no se puede crear porque su comparador es nulo.");
  arbol_destruir(nuevo_arbol);
}

void dadaUnaCreacionDeABB_SiSeLePasaUnComparadorNoNulo_SeCreaUnABB(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  pa2m_afirmar(nuevo_arbol != NULL, "El Arbol se puede crear ya que tiene un comparador distinto de nulo.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiElABBEsNulo_NoPuedeInsertarElementos(){
  abb_t* nuevo_arbol = NULL;
  void* elemento = (void*)0xBEBECAF1;
  int test = arbol_insertar(nuevo_arbol, elemento);
  pa2m_afirmar( test != 0, "No se puede insertar ningun elemento a un arbol nulo.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiElABBEstaVacio_SeInsertaElNodoConElElementoComoRaiz(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero = 3;
  void* numeroptr = (void*)&numero;
  int test = arbol_insertar(nuevo_arbol, numeroptr);
  pa2m_afirmar(test == 0 && nuevo_arbol->nodo_raiz->elemento == numeroptr, "El arbol distinto de nulo esta vacio por lo que inserta el elemento en el nodo raiz.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SeInsertanVariosElementos_DependiendoDelComparadorLosOrdenaEnElArbol(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 3;
  int numero2 = 1;
  int numero3 = 6;
  int numero4 = 2;
  void* numeroptr1 = (void*)&numero1;
  void* numeroptr2 = (void*)&numero2;
  void* numeroptr3 = (void*)&numero3;
  void* numeroptr4 = (void*)&numero4;
  int test1 = arbol_insertar(nuevo_arbol, numeroptr1);
  int test2 = arbol_insertar(nuevo_arbol, numeroptr2);
  int test3 = arbol_insertar(nuevo_arbol, numeroptr3);
  int test4 = arbol_insertar(nuevo_arbol, numeroptr4);
  pa2m_afirmar(test1 == 0 && nuevo_arbol->nodo_raiz->elemento == numeroptr1, "El primer elemento es insertado en el nodo_raiz.");
  pa2m_afirmar(test2 == 0 && nuevo_arbol->nodo_raiz->izquierda->elemento == numeroptr2, "El segundo elemento es insertado en el nodo izquierdo del raiz.");
  pa2m_afirmar(test3 == 0 && nuevo_arbol->nodo_raiz->derecha->elemento == numeroptr3, "El tercer elemento es insertado en el nodo derecho del raiz.");
  pa2m_afirmar(test4 == 0 && nuevo_arbol->nodo_raiz->izquierda->derecha->elemento == numeroptr4, "El cuarto elemento es insertado en el nodo izquierdo y luego derecho del raiz.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiABBEsNulo_NoPuedeBorrar(){
  abb_t* nuevo_arbol = NULL;
  int numero = 1;
  void* elemento = (void*)&numero;
  int test = arbol_borrar(nuevo_arbol, elemento);
  pa2m_afirmar( test != 0, "No se puede borrar ningun elemento a un arbol nulo.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiABBEsVacio_NoPuedeBorrar(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero = 1;
  void* elemento = (void*)&numero;
  int test = arbol_borrar(nuevo_arbol, elemento);
  pa2m_afirmar( test != 0, "No se puede borrar ningun elemento a un arbol vacio.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABBConUnElemento_SiSeBorra_ElArbolQuedaVacio(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero = 1;
  void* elemento = (void*)&numero;
  arbol_insertar(nuevo_arbol, elemento);
  int test = arbol_borrar(nuevo_arbol, elemento);
  pa2m_afirmar( test == 0 && arbol_vacio(nuevo_arbol) , "El elemento es borrado y el arbol queda vacio.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiSeEliminaLaRaizQueTieneSolo1HijoIzquierdo_ElHijoSeVuelveRaiz(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 2;
  int numero2 = 1;
  void* elemento1 = (void*)&numero1;
  void* elemento2 = (void*)&numero2;
  arbol_insertar(nuevo_arbol, elemento1);
  arbol_insertar(nuevo_arbol, elemento2);
  int test = arbol_borrar(nuevo_arbol, elemento1);
  pa2m_afirmar( test == 0 && nuevo_arbol->nodo_raiz->elemento == elemento2 , "El elemento es borrado y el hijo izquierdo queda como raiz.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiSeEliminaLaRaizQueTieneSolo1HijoDerecho_ElHijoSeVuelveRaiz(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 2;
  int numero2 = 3;
  void* elemento1 = (void*)&numero1;
  void* elemento2 = (void*)&numero2;
  arbol_insertar(nuevo_arbol, elemento1);
  arbol_insertar(nuevo_arbol, elemento2);
  int test = arbol_borrar(nuevo_arbol, elemento1);
  pa2m_afirmar( test == 0 && nuevo_arbol->nodo_raiz->elemento == elemento2 , "El elemento es borrado y el hijo derecho queda como raiz.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABBCon3Elementos_SiSeBorraLaRaiz_SustituyeElPredecesor(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 0;
  int numero2 = 1;
  int numero3 = 0;
  void* elemento1 = (void*)&numero1;
  void* elemento2 = (void*)&numero2;
  void* elemento3 = (void*)&numero3;
  arbol_insertar(nuevo_arbol, elemento1);
  arbol_insertar(nuevo_arbol, elemento2);
  arbol_insertar(nuevo_arbol, elemento3);
  int test = arbol_borrar(nuevo_arbol, elemento1);
  pa2m_afirmar( test == 0 && nuevo_arbol->nodo_raiz->elemento == elemento3, "Se Borro la Raiz entonces el elemento izquierdo es su predecesor.");
  arbol_destruir(nuevo_arbol);
}


void dadoUnABBConElementos_SiSeBorraElemento_PunterosQuedanAcomodados(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 10;
  int numero2 = 5;
  int numero3 = 15;
  int numero4 = 8;
  int numero5 = 9;
  int numero6 = 12;
  int numero7 = 16;
  void* elemento1 = (void*)&numero1;
  void* elemento2 = (void*)&numero2;
  void* elemento3 = (void*)&numero3;
  void* elemento4 = (void*)&numero4;
  void* elemento5 = (void*)&numero5;
  void* elemento6 = (void*)&numero6;
  void* elemento7 = (void*)&numero7;
  arbol_insertar(nuevo_arbol, elemento1);
  arbol_insertar(nuevo_arbol, elemento2);
  arbol_insertar(nuevo_arbol, elemento3);
  arbol_insertar(nuevo_arbol, elemento4);
  arbol_insertar(nuevo_arbol, elemento5);
  arbol_insertar(nuevo_arbol, elemento6);
  arbol_insertar(nuevo_arbol, elemento7);
  int test = arbol_borrar(nuevo_arbol, elemento2);
  pa2m_afirmar( test == 0 && nuevo_arbol->nodo_raiz->izquierda->elemento == elemento4, "Se elimino el elemento izquierdo de la raiz y se sustituyo por sus hijos.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABBVacio_SiSeBuscaUnElemento_NoEncuentraElElemento(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 2;
  void* elemento1 = (void*)&numero1;
  void* test = arbol_buscar(nuevo_arbol, elemento1);
  pa2m_afirmar( test == NULL, "No se encontro ningun elemento porque el arbol es nulo.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiSeBuscaUnElementoYNoEstaDentroDelABB_NoEncuentraElElemento(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 2;
  void* elemento1 = (void*)&numero1;
  void* test = arbol_buscar(nuevo_arbol, elemento1);
  pa2m_afirmar( test == NULL, "No se encontro el elemento buscado dentro del arbol.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiSeBuscaUnElementoYEstaDentroDelABB_EncuentraElElemento(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 2;
  void* elemento1 = (void*)&numero1;
  arbol_insertar(nuevo_arbol, elemento1);
  void* test = arbol_buscar(nuevo_arbol, elemento1);
  pa2m_afirmar( test == elemento1, "Se encontro el elemento buscado dentro del arbol.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABBVacio_SiBuscoElElementoDeLaRaiz_NoEncuentra(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  void* test = arbol_raiz(nuevo_arbol);
  pa2m_afirmar( test == NULL, "No se encontro ningun elemento en la raiz porque el arbol es nulo.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiBuscoElElementoDeLaRaiz_EncuentraElemento(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 2;
  void* elemento1 = (void*)&numero1;
  arbol_insertar(nuevo_arbol, elemento1);
  void* test = arbol_raiz(nuevo_arbol);
  pa2m_afirmar( test == elemento1, "Se encontro un elemento en la raiz.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiABBVacio_ConfirmaABBSinElementos(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  pa2m_afirmar( arbol_vacio(nuevo_arbol), "Arbol esta vacio.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiABBNoEstaVacio_ConfirmaABBConElementos(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 2;
  void* elemento1 = (void*)&numero1;
  arbol_insertar(nuevo_arbol, elemento1);
  pa2m_afirmar( !arbol_vacio(nuevo_arbol), "Arbol no esta vacio.");
  arbol_destruir(nuevo_arbol);
}



void dadoUnABB_SiABBEstaVacio_NoTieneElementosElArrayParaRecorrerInOrder(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  size_t tamanio = 10;
  void* arreglo[tamanio];
  size_t test = arbol_recorrido_inorden(nuevo_arbol, arreglo, tamanio);
  pa2m_afirmar( test == 0, "El arbol esta vacio por lo que no tiene elementos el array.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiABBTieneMasElementosQueTamanioDelArreglo_SoloGuardaElMaximoDelArreglo(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 10;
  int numero2 = 5;
  void* elemento1 = (void*)&numero1;
  void* elemento2 = (void*)&numero2;
  arbol_insertar(nuevo_arbol, elemento1);
  arbol_insertar(nuevo_arbol, elemento2);
  size_t tamanio = 1;
  void* arreglo[tamanio];
  size_t test = arbol_recorrido_inorden(nuevo_arbol, arreglo, tamanio);
  pa2m_afirmar( test == 1, "El array solo guarda un elemento porque su tamano es 1.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiSeRecorreInOrder_AgregaAlVectorOrdenandoDeMenorAMayor(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 10;
  int numero2 = 5;
  int numero3 = 15;
  int numero4 = 8;
  int numero5 = 9;
  int numero6 = 12;
  int numero7 = 16;
  void* elemento1 = (void*)&numero1;
  void* elemento2 = (void*)&numero2;
  void* elemento3 = (void*)&numero3;
  void* elemento4 = (void*)&numero4;
  void* elemento5 = (void*)&numero5;
  void* elemento6 = (void*)&numero6;
  void* elemento7 = (void*)&numero7;
  arbol_insertar(nuevo_arbol, elemento1);
  arbol_insertar(nuevo_arbol, elemento2);
  arbol_insertar(nuevo_arbol, elemento3);
  arbol_insertar(nuevo_arbol, elemento4);
  arbol_insertar(nuevo_arbol, elemento5);
  arbol_insertar(nuevo_arbol, elemento6);
  arbol_insertar(nuevo_arbol, elemento7);
  size_t tamanio = 10;
  void* arreglo[tamanio];
  size_t test = arbol_recorrido_inorden(nuevo_arbol, arreglo, tamanio);
  pa2m_afirmar( test == 7, "El arbol tiene 7 elementos.");
  pa2m_afirmar( arreglo[0] == elemento2, "El primer elemento es el mas izquierdo.");
  pa2m_afirmar( arreglo[6] == elemento7, "El ultimo elemento es el mas derecho.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiABBEstaVacio_NoTieneElementosElArrayParaRecorrerPreOrder(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  size_t tamanio = 10;
  void* arreglo[tamanio];
  size_t test = arbol_recorrido_preorden(nuevo_arbol, arreglo, tamanio);
  pa2m_afirmar( test == 0, "El arbol esta vacio por lo que no tiene elementos el array.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiSeRecorrePreOrder_AgregaAlVectorElementosDesdeLaRaiz(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 10;
  int numero2 = 5;
  int numero3 = 15;
  int numero4 = 8;
  int numero5 = 9;
  int numero6 = 12;
  int numero7 = 16;
  void* elemento1 = (void*)&numero1;
  void* elemento2 = (void*)&numero2;
  void* elemento3 = (void*)&numero3;
  void* elemento4 = (void*)&numero4;
  void* elemento5 = (void*)&numero5;
  void* elemento6 = (void*)&numero6;
  void* elemento7 = (void*)&numero7;
  arbol_insertar(nuevo_arbol, elemento1);
  arbol_insertar(nuevo_arbol, elemento2);
  arbol_insertar(nuevo_arbol, elemento3);
  arbol_insertar(nuevo_arbol, elemento4);
  arbol_insertar(nuevo_arbol, elemento5);
  arbol_insertar(nuevo_arbol, elemento6);
  arbol_insertar(nuevo_arbol, elemento7);
  size_t tamanio = 10;
  void* arreglo[tamanio];
  size_t test = arbol_recorrido_preorden(nuevo_arbol, arreglo, tamanio);
  pa2m_afirmar( test == 7, "El arbol tiene 7 elementos.");
  pa2m_afirmar( arreglo[0] == elemento1, "El primer elemento es la raiz del arbol.");
  pa2m_afirmar( arreglo[6] == elemento7, "El ultimo elemento es el mas derecho.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiABBEstaVacio_NoTieneElementosElArrayParaRecorrerPostOrder(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  size_t tamanio = 10;
  void* arreglo[tamanio];
  size_t test = arbol_recorrido_postorden(nuevo_arbol, arreglo, tamanio);
  pa2m_afirmar( test == 0, "El arbol esta vacio por lo que no tiene elementos el array.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiSeRecorrePostOrder_AgregaAlVectorElementosDesdeLasHojas(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 10;
  int numero2 = 5;
  int numero3 = 15;
  int numero4 = 8;
  int numero5 = 9;
  int numero6 = 12;
  int numero7 = 16;
  void* elemento1 = (void*)&numero1;
  void* elemento2 = (void*)&numero2;
  void* elemento3 = (void*)&numero3;
  void* elemento4 = (void*)&numero4;
  void* elemento5 = (void*)&numero5;
  void* elemento6 = (void*)&numero6;
  void* elemento7 = (void*)&numero7;
  arbol_insertar(nuevo_arbol, elemento1);
  arbol_insertar(nuevo_arbol, elemento2);
  arbol_insertar(nuevo_arbol, elemento3);
  arbol_insertar(nuevo_arbol, elemento4);
  arbol_insertar(nuevo_arbol, elemento5);
  arbol_insertar(nuevo_arbol, elemento6);
  arbol_insertar(nuevo_arbol, elemento7);
  size_t tamanio = 10;
  void* arreglo[tamanio];
  size_t test = arbol_recorrido_postorden(nuevo_arbol, arreglo, tamanio);
  pa2m_afirmar( test == 7, "El arbol tiene 7 elementos.");
  pa2m_afirmar( arreglo[0] == elemento5, "El primer elemento es la ultima hoja del arbol.");
  pa2m_afirmar( arreglo[6] == elemento1, "El ultimo elemento es la raiz.");
  arbol_destruir(nuevo_arbol);
}

bool hay_numeros_negativos(void* _elemento1, void* _elemento2){
  bool hay_negativo = false;
  int elemento1 = *(int*) _elemento1;
  if(elemento1 < 0){
    _elemento2 = _elemento1;
    hay_negativo = true;
  }
  return hay_negativo;
}

void dadoUnABB_SiABBVacio_NoPuedeIterarInternamente(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  void* puntero = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  size_t test = abb_con_cada_elemento(nuevo_arbol, 0, hay_numeros_negativos, puntero);
  pa2m_afirmar(test == 0, "El iterador interno hizo 0 iteraciones porque el arbol esta vacio.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABB_SiFuncionInternaIterarEsVacia_NoPuedeIterarInternamente(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  void* puntero = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  size_t test = abb_con_cada_elemento(nuevo_arbol, 0, NULL, puntero);
  pa2m_afirmar(test == 0, "El iterador interno hizo 0 iteraciones porque la funcion es nula.");
  arbol_destruir(nuevo_arbol);
}

void dadoUnABBConUnNumeroNegativo_SiSeIteraInternamete_DevuelveLaCantidadDeElementosQueIteroSegunSuRecorrido(){
  abb_comparador comparador = &compara_numeros;
  abb_liberar_elemento destructor = NULL;
  void* puntero = NULL;
  abb_t* nuevo_arbol = arbol_crear(comparador, destructor);
  int numero1 = 5;
  int numero2 = 3;
  int numero3 = 6;
  int numero4 = -1;
  void* elemento1 = (void*)&numero1;
  void* elemento2 = (void*)&numero2;
  void* elemento3 = (void*)&numero3;
  void* elemento4 = (void*)&numero4;
  arbol_insertar(nuevo_arbol, elemento1);
  arbol_insertar(nuevo_arbol, elemento2);
  arbol_insertar(nuevo_arbol, elemento3);
  arbol_insertar(nuevo_arbol, elemento4);
  size_t test1 = abb_con_cada_elemento(nuevo_arbol, 0, hay_numeros_negativos, puntero);
  pa2m_afirmar(test1 == 1, "Se itero el arbol en orden.");
  size_t test2 = abb_con_cada_elemento(nuevo_arbol, 1, hay_numeros_negativos, puntero);
  pa2m_afirmar(test2 == 3, "Se itero el arbol en pre-orden.");
  size_t test3 = abb_con_cada_elemento(nuevo_arbol, 2, hay_numeros_negativos, puntero);
  pa2m_afirmar(test3 == 1, "Se itero el arbol en post-orden.");
  arbol_destruir(nuevo_arbol);
}

int main(){
  pa2m_nuevo_grupo("TDA - Arbol Binario de Busqueda.");

  pa2m_nuevo_grupo("Crear Arbol");
  dadaUnaCreacionDeABB_SiSeLePasaUnComparadorNulo_NoEsPosibleCrearUnABB();
  dadaUnaCreacionDeABB_SiSeLePasaUnComparadorNoNulo_SeCreaUnABB();

  pa2m_nuevo_grupo("Insertar elemento al Arbol");
  dadoUnABB_SiElABBEsNulo_NoPuedeInsertarElementos();
  dadoUnABB_SiElABBEstaVacio_SeInsertaElNodoConElElementoComoRaiz();

  pa2m_nuevo_grupo("Insertar varios elementos al Arbol");
  dadoUnABB_SeInsertanVariosElementos_DependiendoDelComparadorLosOrdenaEnElArbol();

  pa2m_nuevo_grupo("Borrar elementos de un Arbol");
  dadoUnABB_SiABBEsNulo_NoPuedeBorrar();
  dadoUnABBConUnElemento_SiSeBorra_ElArbolQuedaVacio();
  dadoUnABB_SiSeEliminaLaRaizQueTieneSolo1HijoIzquierdo_ElHijoSeVuelveRaiz();
  dadoUnABB_SiSeEliminaLaRaizQueTieneSolo1HijoDerecho_ElHijoSeVuelveRaiz();
  dadoUnABBCon3Elementos_SiSeBorraLaRaiz_SustituyeElPredecesor();
  dadoUnABBConElementos_SiSeBorraElemento_PunterosQuedanAcomodados();

  pa2m_nuevo_grupo("Borrar elementos de un Arbol");
  dadoUnABBVacio_SiSeBuscaUnElemento_NoEncuentraElElemento();
  dadoUnABB_SiSeBuscaUnElementoYNoEstaDentroDelABB_NoEncuentraElElemento();
  dadoUnABB_SiSeBuscaUnElementoYEstaDentroDelABB_EncuentraElElemento();

  pa2m_nuevo_grupo("Elemento de una raiz");
  dadoUnABBVacio_SiBuscoElElementoDeLaRaiz_NoEncuentra();
  dadoUnABB_SiBuscoElElementoDeLaRaiz_EncuentraElemento();

  pa2m_nuevo_grupo("Arbol Vacio");
  dadoUnABB_SiABBNoEstaVacio_ConfirmaABBConElementos();
  dadoUnABB_SiABBVacio_ConfirmaABBSinElementos();
  
  pa2m_nuevo_grupo("Arbol - Recorrido Inorden");
  dadoUnABB_SiABBEstaVacio_NoTieneElementosElArrayParaRecorrerInOrder();
  dadoUnABB_SiABBTieneMasElementosQueTamanioDelArreglo_SoloGuardaElMaximoDelArreglo();
  dadoUnABB_SiSeRecorreInOrder_AgregaAlVectorOrdenandoDeMenorAMayor();

  pa2m_nuevo_grupo("Arbol - Recorrido Preorden");
  dadoUnABB_SiABBEstaVacio_NoTieneElementosElArrayParaRecorrerPreOrder();
  dadoUnABB_SiSeRecorrePreOrder_AgregaAlVectorElementosDesdeLaRaiz();
  
  pa2m_nuevo_grupo("Arbol - Recorrido Preorden");
  dadoUnABB_SiABBEstaVacio_NoTieneElementosElArrayParaRecorrerPostOrder();
  dadoUnABB_SiSeRecorrePostOrder_AgregaAlVectorElementosDesdeLasHojas();
  
  pa2m_nuevo_grupo("Arbol - Iterador Interno");
  dadoUnABB_SiABBVacio_NoPuedeIterarInternamente();
  dadoUnABB_SiFuncionInternaIterarEsVacia_NoPuedeIterarInternamente();
  dadoUnABBConUnNumeroNegativo_SiSeIteraInternamete_DevuelveLaCantidadDeElementosQueIteroSegunSuRecorrido();
  return pa2m_mostrar_reporte();
}
