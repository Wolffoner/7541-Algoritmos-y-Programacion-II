/*
 * Diagrame cómo queda el Stack y el Heap al 
 * finalizar la ejecución.
 */
void sumar_uno(int* numero){
	(*numero)++; 
}

int main(){
	int a = 8;
	sumar_uno(&a);

	/*
	 * ...
	 */
}