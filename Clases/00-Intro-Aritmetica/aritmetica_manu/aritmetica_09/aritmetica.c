/*
 * Diagrame cómo queda el Stack y el Heap al 
 * finalizar la ejecución.
 */
#define MAX_CAJONES 5
#define MAX_COSAS 50
#define MAX_DESCRIPCION 500

typedef struct cosa {
	char descripcion[MAX_DESCRIPCION];
} cosa_t;

typedef struct cajon {
	int ancho;
	int largo;
	cosa_t* cosas;
	int cantidad_cosas;
} cajon_t;

int main(){
	cajon_t* cajones = malloc(MAX_CAJONES*sizeof(cajon_t));
	for (int i = 0; i < MAX_CAJONES; i++){
		cajones[i] = malloc(sizeof(MAX_COSAS*cosa_t));
	}

	/* La cosa 35 del 35 cajon es un cargador */

	/* Como liberamos esa memoria? */

}