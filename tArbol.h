
#include "set.h"
#define STR 1
#define SETT 2
#define LIST 3

typedef struct dataType{
	int nodeType;
	union {
		str st;
		struct {
			struct dataType* data;
			struct dataType* next;
		};
	};
}tData;

typedef tData*tArbol;

void AgregaPorColaArb(tArbol*,tArbol);
tArbol crearNodoSTR(str);
tArbol crearNodoStruct(int, tArbol);
int menuElement();
tArbol cargarLista();
tArbol inicializarLista();
tArbol CreateSetVacio();
tArbol cargarSet();
void mostrarSet(tArbol);
void mostrarLista(tArbol);
tArbol setToTree(SET);
tArbol cargarSetCadHC(SET);
int pertenece(tArbol, tArbol);
int cmpArbol(tArbol, tArbol);
tArbol UNION(tArbol, tArbol);
tArbol INTERSECCION(tArbol, tArbol);
tArbol DIFERENCIA(tArbol, tArbol);
int cardinalidad(tArbol);
void inclusion(tArbol, tArbol);
void eliminarSet(tArbol*,tArbol);
str retSTR(tArbol);
tArbol retNext(tArbol);
tArbol retData(tArbol);
int retNodeType(tArbol);
void saveData(tArbol*,tArbol);
tArbol cpyArbol(tArbol);
tArbol strToTree(str);
tArbol retSigma(str);
