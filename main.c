
#include "tadAF.h"

int Menu();

int main() {
	T_AF A;
	str S;
	int op;
	do{
		system("cls");
		op=Menu();
		switch(op){
		case 0: printf("\n- Saliendo del Programa.\n"); break;
		case 1:	
			A=cargarAFhardcodeada(load2("{q0,q1,q2}*{x,y}*[q0,x,{q0;q1}]#[q0,y,{q2}]#[q1,x,{q0}]#[q1,y,{q1;q2}]#[q2,x,{}]#[q2,y,{q0;q2}]*q0*{q1}")); 
			printf("\n-Se cargo correctamente el AF\n");
			break;
		//{q0,q1}*{0,1}*[q0,0,q1]#[q0,1,q0]#[q1,0,q0]#[q1,1,q1]*q0*{q1}
		case 2: A=cargarAF(); break;
		case 3: consulta(A); break;
		case 4: 
			if(esAFD(A))
				printf("\n- El AF es Determinista.\n");
			else
				printf("\n- El AF es NO Determinista.\n");
			break;
		case 5:
			S=load2("xxyxyyx");
			printf("\nw = "); print(S);
			if(AceptacionDeCad(A,S))
				printf("\n- Cadena aceptada.\n");
			else
				printf("\n- Cadena NO aceptada.\n");
			break;
		case 6: 
			S=load();
			if(AceptacionDeCad(A,S))
				printf("\n- Cadena aceptada.\n");
			else
				printf("\n- Cadena NO aceptada.\n");
			break;
		default: printf("\n-Opcion Invalida.\n");
		}
		printf("\n");	
		system("pause");
	} while(op!=0);
	return 0;
}

int Menu(){
	int opc;
	printf("\nMENU:\n");
	printf("\n[0] Salir del Programa.");
	printf("\n[1] Cargar AF hardcodeado.");
	printf("\n[2] Cargar AF.");
	printf("\n[3] Consultar elemento de la 5-upla.");
	printf("\n[4] Determinar si el AF es Determinista o NO Determinista.");
	printf("\n[5] Determinar si una cadena harcodeada es aceptada.");
	printf("\n[6] Determinar si una cadena es aceptada.");
	printf("\nIngrese opcion a realizar: ");
	scanf("%d",&opc);
	return opc;
}
	
/*tArbol A, B, D, L;
	SET C;
	str S1;
	int op,tipo;
	A = B = D = CreateSetVacio();
	L = inicializarLista();
	S1 = NULL;
	do{
	system("cls");
	op=Menu();
	switch(op){
	case 0: printf("\n- Saliendo del Programa.\n"); break;
	case 1:	L=cargarLista(); break;
	case 2: printf("\n- L ="); mostrarLista(L); break;
	case 3: A=cargarSet(); break;
	case 4: printf("\n- A = "); mostrarSet(A); break;
	case 5: 
	tipo = menuElement();
	switch(tipo){
	case STR: S1 = load(); B = crearNodoSTR(S1); break;
	case SETT: B = cargarSet(); mostrarSet(B); break;
	case LIST: B = cargarLista(); mostrarLista(B); break;
	default:
	printf("\n====Tipo no valido, se cargara como STR por defecto\n");
	S1 = load();
	B = crearNodoSTR(S1);
	}
	if(pertenece(B,A))
	printf("\n-SI pertenece\n");
	else
	printf("\n-NO pertenece\n");
	break;
	case 6: S1 = load2("a,b,cd,efg"); C=strToSetToken(S1,','); B=cargarSetCadHC(C); printf("\n- B = "); mostrarSet(B); break;
	case 7: D = UNION(A,B); printf("\n- AuB = "); mostrarSet(D); break;
	case 8: D = INTERSECCION(A,B); printf("\n- AnB = "); mostrarSet(D); break;
	case 9: D = DIFERENCIA(A,B); printf("\n- A-B = "); mostrarSet(D); break;
	case 10:  printf("\n- |A| = %d",cardinalidad(A)); break;
	case 11: inclusion(A,B); break;
	case 12:printf("\n==== Ingrese el CONJUNTO a eliminar ===="); B = cargarSet(); mostrarSet(B); eliminarSet(&A,B); break;
	default: printf("\n-Opcion Invalida.\n");
	}
	printf("\n");	
	system("pause");
	} while(op!=0);*/
