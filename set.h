
#include "string.h"

typedef struct nodo{
	str dato;
	struct nodo*sig;
}tnodo;

typedef tnodo*SET;

SET CreateSetVoid();
SET CreaElement(str);
void AddElement(SET *,str);
SET strToSetToken(str, char);
SET Union(SET,SET);
SET Interseccion(SET,SET);
SET Difetencia(SET,SET);
void ShowSet(SET);
void DetermineElementSet(SET,str);
void DetermineIncludeSet(SET,SET);
str retElemetSet(SET);
void recorrerSET(SET*);
int belongs(SET, str);
SET strToSet(str);

