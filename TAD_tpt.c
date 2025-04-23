#include "TAD_tpt.h"

int compStr(str, str);

int inclusion(TArbol A,TArbol B){
	TArbol aux;
	int b;
	b = -1;
	if(A != NULL && B != NULL){
		if(compArbol(A,B) == 1)
			b = 1;
		else if(A->tipo == SET || A->tipo == LIST){
			aux = A->dato;
			while(aux != NULL && b != 1){
				if(inclusion(aux,B) == 1){
					b = 1;
				}
				aux = aux->sig;
			}
		}
	}
	return b;
}

int compSet(TArbol A, TArbol B){
	TArbol aux1, aux2;
	int b;
	if(A != NULL){
		b = 1;
		aux1 = A;
		if(B == NULL){
			b = 1;
		}
		else{
			aux2 = B;
			if(cardinal(aux1, 0) == cardinal(aux2, 0)){
				while(aux1 != NULL && aux2 != NULL && b == 1){
					if(aux1->tipo != aux2->tipo){
						b = -1;
					}
					else{
						if(aux1->tipo != STR){
							b = compSet(aux1->dato, aux2->dato);
						}
						else{
							if(compStr(aux1->cad, aux2->cad) != 1){
								b = -1;
							}
						}
					}
					aux2 = aux2->sig;
					aux1 = aux1->sig;
				}
			}
			else{
				b = -1;
			}
		}
	}
	return b;
}
	
void unionArbol(TArbol *A, TArbol B){
	TArbol aux, C;
	if(A == NULL && B != NULL){
		*A = B;
	}
	else if (A != NULL){
		aux = (*A)->dato;
		if(aux == NULL){
			(*A)->dato = B;
		}
		else{
			if(B->tipo == STR && pertenece(*A, B->cad) != 1){
				while(aux->sig != NULL){
					aux = aux->sig;
				}
				aux->sig = B;
			}
			else{
				switch(B->tipo){
				case 3: case 2:
					C = B;
					if(compSet(*A, C) != 1){
						aux = (*A)->dato;
						while(aux->sig != NULL){
							aux = aux->sig;
						}
						aux->sig = C;
					}
					break;
				}
			}
		}
	}
}

int compArbol(TArbol A, TArbol B){
	TArbol aux1, aux2;
	int b;
	if(A == NULL && B == NULL){
		b = 1;
	}
	else if(A != NULL && B != NULL && A->tipo == B->tipo){
		if(A->tipo == STR){
			b = compStr(A->cad, B->cad);
		}
		else{
				aux1 = A->dato;
				aux2 = B->dato;
				b = 1;
				while(aux1 != NULL && aux2 !=NULL && b == 1){
					if(compArbol(aux1, aux2) != 1){
						b = -1;
					}
					aux1 = aux1->sig;
					aux2 = aux2->sig;
				}
				if(aux1 != NULL || aux2 != NULL){
					b = -1;
				}
			}
		}
	else{
		b = -1;
	}
	return b;
}

int compStr(str a, str b){
	str aux1, aux2;
	int ba, c;
	ba = 0;
	c = 1;
	aux1 = a;
	aux2 = b;
	while(aux1 != NULL && ba != 1){
		if(aux1->dato == aux2->dato){
			aux1 = aux1->sig;
			aux2 = aux2->sig;
		}
		else{
			ba = 1;
		}
	}
	if((aux1 != NULL && aux2 == NULL) || (aux1 == NULL && aux2 != NULL) || ba != 0){
		c = -1;
	}
	return c;
}

TArbol create_arbol(int t){
	TArbol A;
	A=(TArbol)malloc(sizeof(struct dataType));
	A->tipo=t;
	A->cad= NULL;
	A->dato=NULL;
	A->sig=NULL;
	return A;
}

int pertenece(TArbol A, str s){
	int i;
	i = 0;
	TArbol aux;
	if(A != NULL){
		aux = A;
		if(aux->tipo != STR){
			aux = aux->dato;
			while(aux != NULL && i != 1){
				if(pertenece(aux, s) == 1){
					i = 1;
				}
				aux = aux->sig;
			}
		}
		else{
			i = compStr(aux->cad, s);
		}
	}
	return i;
}
	
int cardinalLvl1(TArbol A){
	int i;
	TArbol aux;
	i = 0;
	if(A != NULL){
		aux = A->dato;
		if(aux != NULL){
			while(aux->sig != NULL){
				i++;
				aux = aux->sig;
			}
		}
	}
	return i; 
}
	
int cardinal(TArbol A, int i){
	TArbol aux;
	if(A != NULL){
		aux = A;
		if(aux->tipo != STR){
			aux = aux->dato;
			while(aux != NULL){
				i = cardinal(aux, i);
				aux = aux->sig;
			}
		}
		else{
			i = i+1;
		}
	}
	return i;
}
	
int menuCarga(){
	int t;
	printf("\nIngrese tipo de dato: ");
	printf("\n[1]: Ingresar Str");
	printf("\n[2]:Ingresar Set");
	printf("\n[3]:Ingresar List");
	printf("\nElija una opcion: ");
	scanf("%d",&t);
	return t;
}
	
TArbol append_arbol(int tipo){
	TArbol cab, actual, nvo, aux;
	int t, b;
	cab = NULL;
	actual = NULL;
	b = 1;
	while(b == 1){
		t = menuCarga();
		nvo=create_arbol(t);
		if(t == 1){
			fflush(stdin);
			nvo->cad = load();
		}
		else
			nvo->dato = append_arbol(t);
		if(cab == NULL){
			cab = nvo;
			actual = nvo;
		}else{
			while(actual->sig != NULL){
				actual = actual->sig;
			}
			actual->sig = nvo;
			actual = nvo;
		}
		printf("\nAgregar otro elemento? (1: si, 0: no): ");
		scanf("%d", &b);
	}
	aux=create_arbol(tipo);
	aux->dato=cab;
	return aux;
}

void carga_arbol(TArbol *cab){
	int t;
	t = menuCarga();
	(*cab)=create_arbol(t);
	if(t==1){
		fflush(stdin);
		(*cab)->cad=load();
	}else
		(*cab)->dato=append_arbol(t);
}

void show_arbol(TArbol cab){
	TArbol aux;
	if(cab!=NULL){
		switch(cab->tipo){
		case 1:
			print(cab->cad);
			break;
		case 2:
			printf("[");
			for(aux=cab->dato;aux!=NULL;aux=aux->sig){
				show_arbol(aux);
				if(aux->sig!=NULL)
					printf(",");
			}
			printf("]");
			break;
		case 3:
			printf("{");
			for(aux=cab->dato;aux!=NULL;aux=aux->sig) {
				show_arbol(aux);
				if(aux->sig!= NULL) 
					printf(",");
			}
			printf("}");
			break;
		}
	}
}
TArbol interseccion(TArbol cab,TArbol otra){
	TArbol nvo,aux,aux2;
	nvo=create_arbol(2);
	aux=create_arbol(2);
	while(cab->dato->sig!=NULL){
		aux->dato=otra->dato;
		aux->tipo=otra->tipo;
		while(aux->dato->sig!=NULL){
			if(compArbol(cab,aux->dato)==1){
				if(compArbol(nvo,aux->dato)!=1){
					if(nvo->sig==NULL){
						nvo->dato=cab->dato;
						nvo->tipo=cab->tipo;
					}
					else{
						aux2=nvo->dato;
						while(aux2->sig!=NULL)
							aux2=aux2->sig;
						aux2->sig=cab->dato;
					}
				}
			}
			aux=aux->dato->sig;
		}
		cab=cab->dato->sig;
	}
	return nvo;
}
		
