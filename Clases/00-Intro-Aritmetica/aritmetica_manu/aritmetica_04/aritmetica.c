/*
 * ¿Por qué es incorrecto el siguiente código?
 */

int main(){
	int* p_numero = &a;
	int a;
	*p_numero = 8;

	return 0;
}