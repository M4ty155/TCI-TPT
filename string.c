
#include "string.h"

str create(char c){
	str nvo;
	nvo = (str)malloc(sizeof(char));
	nvo->Dato = c;
	nvo->Sig = NULL;
	return nvo;
}
	
void AgregaAlFinal(str *Cab, str nvo){
	str act;
	if(*Cab!=NULL){
		act = *Cab;
		while(act->Sig != NULL)
			act = act->Sig;
		act->Sig = nvo;
	}
	else
	   *Cab = nvo;
}
	
str load(){
	str Nvo, Cab;
	char c;
	Cab = NULL;
	printf("\n====Ingrese un String: ");
	fflush(stdin);
	c = getchar();
	while(c!=EOF && c != '\n'){
		Nvo = create(c);
		AgregaAlFinal(&Cab, Nvo);
		c = getchar();
	}
	while (c != EOF && c != '\n')  
		c = getchar();
	return Cab;
}
	
str load2(const char *cad){
	str S, Nvo;
	int i;
	S = NULL;
	i=0;
	while(cad[i] != '\0'){
		Nvo = create(cad[i]);
		AgregaAlFinal(&S, Nvo);
		i++;
	}
	return S;
}
	
str loadcpy(str S){
	str Nvo, Cab;
	Cab = NULL;
	while(S!=NULL){
		Nvo = create(S->Dato);
		AgregaAlFinal(&Cab, Nvo);
		S = S->Sig;
	}
	return Cab;
}

void print(str S){
	str act;
	act = S;
	while(act != NULL){
		printf("%c",act->Dato);
		act = act->Sig; 
	}
}

str concat(str S1, str S2){
	str aux, act, nvo;
	aux = NULL;
	act = S1;
	while(act != NULL){
		nvo = create(act->Dato);
		AgregaAlFinal(&aux, nvo);
		act = act->Sig;
	}
	act = S2;
	while(act != NULL){
		nvo = create(act->Dato);
		AgregaAlFinal(&aux, nvo);
		act = act->Sig;
	}
	return aux;
}

str beforeToken(str S, char c){
	int b;
	str aux, act, Nvo;
	aux = Nvo = NULL;
	act = S;
	b=0;
	while(act != NULL && b==0){
		if(act->Dato != c){
			Nvo = create(act->Dato);
			AgregaAlFinal(&aux, Nvo);
			act = act->Sig;
		}
		else
		   b=1;
	}
	return aux;
}
	
str afterToken(str S, char c){
	str aux, act, Nvo;
	aux = Nvo = NULL;
	act = S;
	while(act != NULL && act->Dato != c)
		act = act->Sig;
	if(act!=NULL){
		act = act->Sig;
		while(act != NULL){
			Nvo = create(act->Dato);
			AgregaAlFinal(&aux, Nvo);
			act = act->Sig;
		}
	}
	else
	   aux=loadcpy(S);
	return aux;
}

char retCaracter(str act){
	return act->Dato;
}
	
void recorrerStr(str *act){
	*act = (*act)->Sig;
}
	
void liberarStr(str *S){
	str act;
	if(*S != NULL){
		act = *S;
		while(act!=NULL){
			*S = act->Sig;
			act->Sig = NULL;
			free(act);
			act = *S;
		}
	}
}

int cmpstr(str S1, str S2){
	while(S1!=NULL && S2!=NULL){
		if(S1->Dato != S2->Dato){
			if(S1->Dato < S2->Dato)
				return -1;
			else
				return 1;
		}
		S1 = S1->Sig;
		S2 = S2->Sig;
	}
	if(S1==NULL && S2!=NULL)
		return -1;
	if(S1!=NULL && S2==NULL)
		return 1;
	return 0;
}
