/*
 * Diagrame cómo queda el Stack y el Heap al 
 * finalizar la ejecución.
 */
int* un_entero_en_el_heap(int numero){
	int* aux = malloc(sizeof(int));
	*aux = 8;
	return aux;
}

int main(){
	int* un_entero = un_entero_en_el_heap(8);

	int a = *un_entero;

	/*
	 * ...
	 */
}