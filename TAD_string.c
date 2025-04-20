#include "TAD_string.h"
str create_string(){
	str nodo;
	nodo=(str)malloc(sizeof(TNodo));
	nodo->sig=NULL;
	return nodo;
}
str load(){
	str nodo,nvo,aux;
	char c;
	nodo=NULL;
	printf("\nIngrese una palabra: ");
	c=getchar();
	while(c!='\n'&&c!=EOF){
		nvo=create_string();
		nvo->dato=c;
		if(nodo!=NULL){
			aux=nodo;
			while(aux->sig!=NULL)
				aux=aux->sig;
			aux->sig=nvo;
		}
		else
		   nodo=nvo;
		c=getchar();
	}
	return nodo;
}
str load2(const char *c){
	str nodo,nvo,aux;
	nvo=NULL;
	nodo=NULL;
	aux=NULL;
	while(*c!='\0'){
		nodo=create_string();
		if(nodo==NULL){
			printf("\nError: No se pudo asignar memoria");
			return NULL;
		}
		nodo->dato=*c;
		nodo->sig=NULL;
		if(nvo==NULL)
			nvo=nodo;
		else{
			aux=nvo;
			while(aux->sig!=NULL) 
				aux=aux->sig;
			aux->sig=nodo;
		}
		c++; 
	}
	return nvo;
}
void print(str nodo){
	while(nodo!=NULL){
		printf("%c",nodo->dato);
		nodo=nodo->sig;
	}
}
void append_string(str s1,str *s2){
	str aux,aux2;
	if((*s2)==NULL){
		if(s1!=NULL){
			aux=create_string();
			aux->dato=s1->dato;
			(*s2)=aux;
			aux2=aux;
			s1=s1->sig;
		}
	}
	else{
		aux2=(*s2);
		while(aux2->sig!=NULL)
			aux2=aux2->sig;
	}
	while(s1!=NULL){
		aux=create_string();
		aux->dato=s1->dato;
		aux2->sig=aux;
		aux2=aux2->sig;
		s1=s1->sig;
	}
}
str concat(str s1,str s2){
	str aux;
	aux=NULL;
	append_string(s1,&aux);
	append_string(s2,&aux);
	return aux;
}
str beforeToken(str nodo,char token){
	str nvo,aux,last;
	nvo=NULL;
	last=NULL;
	if(nodo==NULL){
		return NULL; 
	}
	while(nodo!=NULL&&nodo->dato!=token){
		aux=create_string();
		aux->dato=nodo->dato;
		if(nvo==NULL) 
			nvo=aux;
		else 
			last->sig=aux;
		last=aux; 
		nodo=nodo->sig; 
	}
	return nvo;
}
