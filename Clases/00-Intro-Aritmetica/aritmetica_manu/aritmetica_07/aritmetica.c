/*
 * Reemplace los ???????? con expresiones 
 * que hagan verdadera la condición.
 * Diagrame cómo queda el Stack y el Heap al 
 * finalizar la ejecución.
 */

int main(){
	int numero;
	numero = 8;

	int* p_numero;
	p_numero = &numero;

	*p_numero = 10;

	int*   *p_p_numero;
	p_p_numero = &p_numero;

	**p_p_numero = 12;

	&p_numero == &numero
	(int**)       int*
	if (p_p_numero   == &p_numero) printf("Son iguales.");

	if (*p_p_numero  == p_numero) printf("Son iguales.");
		int *		 == int*		
	if (*p_p_numero  == &numero) printf("Son iguales.");
		int *		 == int*

	if (**p_p_numero == ????????) printf("Son iguales.");
		int			 == numero == 12 == *p_numero

	return 0;
}