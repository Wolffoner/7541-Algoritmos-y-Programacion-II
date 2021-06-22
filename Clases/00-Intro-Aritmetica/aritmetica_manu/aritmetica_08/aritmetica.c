/*
 * Diagrame cómo queda el Stack y el Heap al 
 * finalizar la ejecución.
 */

typedef struct cajon {
	int ancho;
	int largo;
	bool lleno;
} cajon_t;

int main(){
	cajon_t un_cajon;
	cajon_t* p_cajon = malloc(sizeof(cajon_t));

	/* Poner valor a los cajones */


	/* Que pasa aca? */
	//p_cajon = &un_cajon;

	/* Que pasa aca? */
	//cajon_t* p_otro_cajon = p_cajon;

	/*
	 * ...
	 */
}