
#include "tArbol.h"


tArbol crearNodoSTR(str s) {
	tArbol nvo;
	nvo = (tArbol)malloc(sizeof(tData));
	if (nvo != NULL) {
		nvo->nodeType = STR;
		nvo->st = loadcpy(s);
	}
	else
		printf("Error de memoria\n");
	return nvo;
}

tArbol crearNodoStruct(int tipo, tArbol ele) {
	tArbol nvo;
	nvo = (tArbol)malloc(sizeof(tData));
	if (nvo != NULL) {
		nvo->nodeType = tipo; 
		nvo->data = ele;
		nvo->next = NULL;
	}
	else
		printf("Error de memoria\n");
	return nvo;
}

tArbol crearNodoVacio(int tipo) {
	return crearNodoStruct(tipo, NULL);
}

tArbol inicializarLista() {
	return crearNodoVacio(LIST); 
}

void AgregaPorColaArb(tArbol *Cab, tArbol nvo){
	tArbol act;
	if(*Cab!=NULL){
		act = *Cab;
		while(act->next != NULL)
			act = act->next;
		act->next = nvo;
	}
	else
	   *Cab = nvo;
}

int menuElement(){
	int opc;
	printf("\nTipo de elemento a cargar:\n");
	printf("[1] STR (cadena)\n");
	printf("[2] SET (conjunto)\n");
	printf("[3] LIST (lista)\n");
	printf("Opcion: ");
	scanf("%d", &opc);
	return opc;
}
	
void Aniadir(tArbol *aux, int tipo, int op){
	tArbol Nvo, ele;
	str cad;
	int b;
	b=1;
	switch (tipo) {
	case STR:
		cad = load();
		if(cad!=NULL)
			ele = crearNodoSTR(cad);
		else
			b=0;
		break;
	case SETT:
		printf("\n====Ingrese un CONJUNTO:\n");
		ele = cargarSet(); 
		break;
	case LIST:
		printf("\n====Ingrese una LISTA:\n");
		ele = cargarLista();
		break;
	default:
		printf("\n====Tipo no valido, se cargara como STR por defecto\n");
		cad = load();
		if(cad!=NULL)
			ele = crearNodoSTR(cad);
		else
			b=0;
	}
	if(b==1){
		if((*aux)->data!=NULL){
			if((op==SETT && pertenece(ele,*aux)==0)|| op==LIST){
				Nvo = crearNodoStruct(op, ele);
				AgregaPorColaArb(aux, Nvo);
			}
			else
				printf("\n-ERROR: El Elemento ingresado ya pertenece.\n");
		}
		else
			(*aux)->data=ele;
		
	}
}

tArbol cargarLista() {
	tArbol L;
	int opc, tipo;
	L = inicializarLista();
	do {
		printf("\n¿Desea agregar un elemento a la LISTA? ([1] Si / [0] No): ");
		scanf("%d", &opc);
		if(opc!=0){
			tipo=menuElement();
			Aniadir(&L,tipo,LIST);
		}
	} while (opc != 0);
	return L;
}

tArbol CreateSetVacio(){
	return crearNodoVacio(SETT);
}

tArbol cargarSet() {
	tArbol C;
	int opc, tipo;
	C = CreateSetVacio();
	do {
		printf("\n¿Desea agregar un elemento al CONJUNTO? ([1] Si / [0] No): ");
		scanf("%d", &opc);
		if(opc!=0){
			tipo=menuElement();
			Aniadir(&C,tipo,SETT);
		}
	} while (opc != 0);
	return C;
}

void mostrarElement(tArbol A, int tipo) {
	if (A != NULL){
		switch (A->nodeType) {
			case STR:
				print(A->st);
				break;
			case LIST:
				mostrarLista(A);  
				break;
			case SETT:
				mostrarSet(A);
				break;
		}
	}
}
void mostrarSet(tArbol C) {
	printf("{");
	while (C != NULL) {
		mostrarElement(C->data,C->nodeType);
		if (C->next != NULL)
			printf(" , ");
		C = C->next;
	}
	printf("}");
}
void mostrarLista(tArbol L) {
	printf("[");
	while (L != NULL) {
		mostrarElement(L->data,L->nodeType);
		if (L->next != NULL)
			printf(" , ");
		L = L->next;
	}
	printf("]");
}

tArbol cargarSetCadHC(SET A) {
	tArbol C, ele, Nvo;
	C = CreateSetVacio();
	while(A!=NULL){
		ele = crearNodoSTR(retElemetSet(A));
		if(C->data!=NULL){
			Nvo = crearNodoStruct(SETT,ele);
			AgregaPorColaArb(&C,Nvo);
		}
		else
		   C->data=ele;
		recorrerSET(&A);
	}
	return C;
}

int contieneEnSet(tArbol elem, tArbol conjunto) {
	while (conjunto != NULL) {
		if (cmpArbol(elem, conjunto->data))
			return 1;
		conjunto = conjunto->next;
	}
	return 0;
}


int cmpArbol(tArbol A, tArbol B) {
	tArbol aux;
	if (A == NULL && B == NULL) return 1;
	if (A == NULL || B == NULL) return 0;
	if (A->nodeType != B->nodeType) return 0;
	switch (A->nodeType) {
		case STR:
			return cmpstr(A->st, B->st) == 0;
		case LIST:
			if (cmpArbol(A->data, B->data) == 1 && cmpArbol(A->next, B->next) == 1)
				return 1;
			else
				return 0;
		case SETT: {
			aux = A;
			while (aux != NULL) {
				if (contieneEnSet(aux->data, B)==0)
					return 0;
				aux = aux->next;
			}
			aux = B;
			while (aux != NULL) {
				if (contieneEnSet(aux->data, A)==0)
					return 0;
				aux = aux->next;
			}
			return 1;
		}
	}
	return 0;
}


int pertenece(tArbol A, tArbol B) {
	tArbol act;
	if (A->data == NULL && B->data == NULL)
		return 0;
	act = B;
	while (act != NULL) {
		if (act->data != NULL) {
			if (A->nodeType == STR && act->data->nodeType == STR) {
				if (cmpstr(A->st, act->data->st) == 0)
					return 1;
			}
			else {
				if (A->nodeType != STR) {
					if (cmpArbol(A, act->data))
						return 1;
				}
			}
		}
		act = act->next;
	}
	return 0;
}

tArbol cpyArbol(tArbol A) {
	tArbol copia;
	if (A == NULL) return NULL;
	copia = (tArbol)malloc(sizeof(tData));
	if(copia!=NULL){
		copia->nodeType = A->nodeType;
		copia->next = NULL;
		switch (A->nodeType) {
		case STR:
			copia->st = loadcpy(A->st); 
			break;
		case LIST:
		case SETT:
			copia->data = cpyArbol(A->data);
			copia->next = cpyArbol(A->next); 
			break;
		}
	}
	else
		printf("Error de memoria\n");
	return copia;
}

tArbol UNION(tArbol A, tArbol B){
	tArbol AuB,nvo,aux;
	AuB = CreateSetVacio();
	while(A!=NULL){
		aux = cpyArbol(A->data);
		if(AuB->data!=NULL){
			nvo = crearNodoStruct(SETT,aux);
			AgregaPorColaArb(&AuB,nvo);
		}
		else
		   AuB->data=aux;
		A = A->next;
	}
	if(B->data != NULL){
		while(B!=NULL){
			if(pertenece(B->data,AuB)==0){
				aux = cpyArbol(B->data);
				if(AuB->data!=NULL){
					nvo = crearNodoStruct(SETT,aux);
					AgregaPorColaArb(&AuB,nvo);
				}
				else
				   AuB->data=aux;
			}
			B = B->next;
		}
	}
	return AuB;
}
	
tArbol INTERSECCION(tArbol A, tArbol B){
	tArbol AnB,nvo,aux;
	AnB = CreateSetVacio();
	if(A->data!=NULL && B->data!=NULL){
		while(A!=NULL){
			if(pertenece(A->data,B)==1){
				aux = cpyArbol(A->data);
				if(AnB->data!=NULL){
					nvo = crearNodoStruct(SETT,aux);
					AgregaPorColaArb(&AnB,nvo);
				}
				else
				   AnB->data=aux;
			}
			A = A->next;
		}
	}
	return AnB;
}

tArbol DIFERENCIA(tArbol A, tArbol B){
	tArbol A_B,nvo,aux;
	A_B = CreateSetVacio();
	while(A!=NULL){
		if(pertenece(A->data,B)==0){
			aux = cpyArbol(A->data);
			if(A_B->data!=NULL){
				nvo = crearNodoStruct(SETT,aux);
				AgregaPorColaArb(&A_B,nvo);
			}
			else
			   A_B->data=aux;
		}
		A = A->next;
	}
	return A_B;
}
	
int cardinalidad(tArbol A){
	int c;
	c=0;
	while(A!=NULL){
		if(A->data!=NULL)
			c++;
		A=A->next;
	}
	return c;
}
int includeSET(tArbol A, tArbol B){
	int b;
	b=1;
	if(A->data!=NULL){
		while(A!=NULL && b==1){
			if(pertenece(A->data,B)==0){
				b=0;
			}
			A = A->next;
		}
	}
	return b;
}
	
void inclusion(tArbol A, tArbol B){
	if(includeSET(A,B)==1)
		printf("\n-A esta incluido en B\n");
	else
		printf("\n-A NO esta incluido en B\n");
}
	
void eliminarSet(tArbol *A, tArbol ele){
	tArbol act,ant;
	if((*A)->data != NULL){
		act=*A;
		ant=NULL;
		while(act!=NULL && cmpArbol(ele,act->data)!=1){
			ant = act;
			act = act->next;
		}
		if(act!=NULL){
			if(ant==NULL)
				*A = act->next;
			else
				ant->next = act->next;
			act->next = NULL;
			free(act);
			printf("\n-Se elimino exitosamente.\n");
		}
		else
		   printf("\n-ERROR: El conjunto ingresado NO se encuentra en el conjunto A.\n");
	}
	else
		printf("\n-ERROR: El conjunto A esta vacio.\n");
}
	
tArbol strToTree(str A){
	tArbol b;
	b = CreateSetVacio();
	b->data = cargarSetCadHC(strToSet(A));
	return b;	
}

str retSTR(tArbol aux){
	return aux->st;
}

tArbol retNext(tArbol aux){
	return aux->next;
}
	
tArbol retData(tArbol aux){
	return aux->data;
}

int retNodeType(tArbol aux){
	return aux->nodeType;
}

void saveData(tArbol *A, tArbol aux){
	(*A)->data = aux;
}

tArbol setToTree(SET A){
	tArbol B;
	B = CreateSetVacio();
	B->data = cargarSetCadHC(strToSet(retElemetSet(A)));
	A = A->sig;
	while(A != NULL){
		AgregaPorColaArb(&B, cargarSetCadHC(strToSet(retElemetSet(A))));
		A = A->sig;
	}
	return B;
}
