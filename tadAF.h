#include "tArbol.h"

typedef struct {
	tArbol Q,Sigma,Delta;
	str q0;
	tArbol estFin;
}T_AF;

T_AF cargarAF();
T_AF cargarAFhardcodeada(str);
void consulta(T_AF);
int esAFD(T_AF);
int AceptacionDeCad(T_AF,str);
