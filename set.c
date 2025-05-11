
#include "set.h"

SET CreateSetVoid(){
	return NULL;
}
	
void AgregaPorColaSet(SET *Cab, SET nvo){
	SET act;
	if(*Cab!=NULL){
		act = *Cab;
		while(act->sig != NULL)
			act = act->sig;
		act->sig = nvo;
	}
	else
	   *Cab = nvo;
}
	
SET CreaElement(str S){
	SET nvo;
	nvo = (SET)malloc(sizeof(str));
	nvo->dato=S;
	nvo->sig=NULL;
	return nvo;
}

int belongs(SET Cab, str S){
	SET act;
	act=Cab;
	while(act!=NULL && cmpstr(act->dato,S)!=0){
		act=act->sig;
	}
	if(act!=NULL)
		return 1;
	else
		return 0;
}
	
void AddElement(SET *Cab, str S){
	SET nvo;
	if(belongs(*Cab,S)==0){
		nvo=CreaElement(S);
		AgregaPorColaSet(Cab,nvo);
	}
}
	
void ShowSet(SET Cab){
	SET act;
	act = Cab;
	printf(" {");
	while(act != NULL){
		print(act->dato);
		if(act->sig != NULL)
			printf(" , ");
		act = act->sig;
	}
	printf("}");
}
	
SET strToSetToken(str S, char c){
	SET C,nvo;
	str aux;
	C=CreateSetVoid();
	aux=NULL;
	while(S!=NULL){
		aux = beforeToken(S,c);
		nvo=CreaElement(aux);
		AgregaPorColaSet(&C,nvo);
		while(S!=NULL && retCaracter(S)!=c)
			recorrerStr(&S);
		if(S!=NULL)
			recorrerStr(&S);
	}
	return C;
}

SET Union(SET A,SET B){
	SET AuB,nvo;
	str aux;
	AuB = CreateSetVoid();
	while(A!=NULL){
		aux = loadcpy(A->dato);
		nvo = CreaElement(aux);
		AgregaPorColaSet(&AuB,nvo);
		A = A->sig;
	}
	while(B!=NULL){
		if(belongs(AuB,B->dato)==0){
			aux = loadcpy(B->dato);
			nvo = CreaElement(aux);
			AgregaPorColaSet(&AuB,nvo);
		}
		B = B->sig;
	}
	return AuB;
}
	
SET Interseccion(SET A, SET B){
	SET AnB,nvo;
	str aux;
	AnB = CreateSetVoid();
	if(A!=NULL && B!=NULL){
		while(A!=NULL){
			aux = loadcpy(A->dato);
			if(belongs(B,aux)!=0){
				nvo = CreaElement(aux);
				AgregaPorColaSet(&AnB,nvo);
			}
			A = A->sig;
		}
	}
	return AnB;
}
	
SET Difetencia(SET A,SET B){
	SET A_B,nvo;
	str aux;
	A_B = CreateSetVoid();
	while(A!=NULL){
		aux = loadcpy(A->dato);
		if(belongs(B,aux)==0){
			nvo = CreaElement(aux);
			AgregaPorColaSet(&A_B,nvo);
		}
		A = A->sig;
	}
	return A_B;
}
	
void DetermineElementSet(SET C, str S){
	if(belongs(C,S)){
		printf("\n- Pertenece a ");
		ShowSet(C);
	}
	else{
		printf("\n- NO Pertenece a ");
		ShowSet(C);
	}
}

int includeSet(SET A, SET B){
	int b;
	b=0;
	if(A!=NULL && B!=NULL){
		b=1;
		while(A!=NULL && b==1){
			if(belongs(B,A->dato)==0)
				b=0;
			A=A->sig;
		}
	}
	else{
		if(A==NULL && B==NULL)
			b=1;
	}
	return b;
}

void DetermineIncludeSet(SET A, SET B){
	if(includeSet(A,B)==1){
		printf("\n-");
		ShowSet(A);
		printf(" esta incluido en ");
		ShowSet(B);
	}
	else{
		printf("\n-");
		ShowSet(A);
		printf(" NO esta incluido en ");
		ShowSet(B);
	}
}
	
str retElemetSet(SET A){
	return loadcpy(A->dato);
}
	
void recorrerSET(SET *A){
	(*A) = (*A)->sig;
}
	
SET strToSet(str A){
	SET B;
	B = CreateSetVoid();
	while(A != NULL){
		AddElement(&B, create(retCaracter(A)));
		A = A->Sig;
	}
	return B;
}
