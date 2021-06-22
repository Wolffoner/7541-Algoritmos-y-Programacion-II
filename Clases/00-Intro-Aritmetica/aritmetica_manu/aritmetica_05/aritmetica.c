/*
 * Diagrame cómo queda el Stack y el Heap al 
 * finalizar la ejecución.
 */

int main(){
	int a;
	int* p_numero = malloc(sizeof(int));
	*p_numero = 8;

	/*
	 * ...
	 */
	free(p_numero);
}