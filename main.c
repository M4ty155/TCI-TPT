#include "TAD_tpt.h"
int main(){
	int i;
	str B;
	TArbol A, C;
	B = NULL;
	carga_arbol(&A);
	show_arbol(A);
	C = append_arbol(2);
	show_arbol(C);
	i = compSet(A->dato, C);
	printf("%d", i);
	fflush(stdin);
	unionArbol(&A, C);
	show_arbol(A);
	B = load();
	print(B);
	i = pertenece(A, B);
	printf("%d", i);
	i = cardinal(A, 0);
	printf("%d", i);
	i = compArbol(A, C);
	printf("%d", i);
	return 0;
}
