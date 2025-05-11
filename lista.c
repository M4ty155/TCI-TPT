/*Alumno: Romano Fabricio Ezequiel*/

#include "lista.h"

lista createlist(str S){
	lista nvo;
	nvo = (lista)malloc(sizeof(str));
	nvo->dato = S;
	nvo->sig = NULL;
	return nvo;
}

void AgregaPorCola(lista *Cab, lista nvo){
	lista act;
	if(*Cab!=NULL){
		act = *Cab;
		while(act->sig != NULL)
			act = act->sig;
		act->sig = nvo;
	}
	else
	   *Cab = nvo;
}
	
void append(lista *Cab, str S){
	lista nvo;
	str Scpy;
	if(S!=NULL){
		Scpy = loadcpy(S);
		nvo = createlist(Scpy);
		AgregaPorCola(Cab,nvo);
	}
	else
		printf("\n -Lista Vacia.\n");
}
	
void show(lista Cab){
	lista act;
	act = Cab;
	if(Cab!=NULL){
		printf("\n[ ");
		while(act != NULL){
			print(act->dato);
			if(act->sig != NULL)
				printf(" , ");
			act = act->sig;
		}
		printf(" ]");
	}
	else
	   printf("\n -Lista Vacia.\n");
}

str ToStr(lista Cab){
	str S,nvo, ant;
	lista act;
	S = ant = NULL;
	act = Cab;
	if(Cab!=NULL){
		S = loadcpy(act->dato);
		act = act->sig;
		while(act != NULL){
			nvo = loadcpy(act->dato);
			ant = S;
			S = concat(S,nvo);
			liberarStr(&ant);
			liberarStr(&nvo);
			act = act->sig;
		}
	}
	else
	   printf("\n -Lista Vacia.\n");
	return S;
}
	
lista StrToLista(str S){
	lista lis,nvo;
	str dato,act;
	lis = nvo = NULL;
	act = S;
	while(act != NULL){
		dato = create(retCaracter(act));
		nvo = createlist(dato);
		AgregaPorCola(&lis, nvo);
		recorrerStr(&act);
	}
	return lis;
}

void liberarLista(lista *L){
	lista act;
	if(*L != NULL){
		act = *L;
		while(act!=NULL){
			*L = act->sig;
			act->sig = NULL;
			liberarStr(&act->dato);
			free(act);
			act = *L;
		}
	}
}
