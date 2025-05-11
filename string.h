#ifndef STRING_H
#define STRING_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
	char Dato;
	struct Nodo*Sig;
}TNodo;

typedef TNodo*str;

str create(char c);
str load();
str load2(const char*);
str loadcpy(str);
void print(str);
str concat(str, str);
str beforeToken(str, char);
str afterToken(str, char);
char retCaracter(str);
void recorrerStr(str*);
void liberarStr(str *);
int cmpstr(str,str);

#endif
