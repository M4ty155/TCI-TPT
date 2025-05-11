/*Alumno: Romano Fabricio Ezequiel*/

#include "string.h"

typedef struct node{
	str dato;
	struct node*sig;
}tnode;

typedef tnode*lista;

lista createlist(str);
void append(lista*, str);
void show(lista);
str ToStr(lista);
lista StrToLista(str);
void liberarLista(lista *);
