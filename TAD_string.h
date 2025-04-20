#ifndef TAD_STRING_H
#define TAD_STRING_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct nodo{
	char dato;
	struct nodo *sig;
}TNodo;
typedef TNodo *str;
str create_string();
str load();
str load2(const char*);
void print(str);
str concat(str,str);
str beforeToken(str,char);
#endif
