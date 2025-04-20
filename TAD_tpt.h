#ifndef TAD_TPT_H
#define TAD_TPT_H
#include "TAD_string.h"
#define STR 1
#define SET 2
#define LIST 3
struct dataType{
	int tipo;
	union{
		str cad;
		struct{
			struct dataType* dato;
			struct dataType* sig;
		};
	};
};
typedef struct dataType* TArbol;
TArbol create_arbol(int);
void carga_arbol(TArbol*);
TArbol append_arbol(int);
void show_arbol(TArbol);
void show_arbol2(TArbol);
int pertenece(TArbol, str);
int cardinal(TArbol, int);
int cardinalLvl1(TArbol);
int compArbol(TArbol, TArbol);
void unionArbol(TArbol*, TArbol);
str retStr(TArbol);
int compSet(TArbol, TArbol);
#endif
