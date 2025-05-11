#include "tadAF.h"

tArbol cargarDestino() {
	int opcion;
	str estDest;
	printf("\n[1] Un solo estado (AFD)\n[2] Conjunto de destinos (AFND)\nOpción: ");
	scanf("%d", &opcion);
	if (opcion == 1) {
		estDest = load();
		return crearNodoSTR(estDest);
	} else {
		printf("\n====Ingrese el CONJUNTO destino:\n");
		return cargarSet(); 
	}
}


tArbol cargarTransiciones(tArbol Q, tArbol Sigma) {
	tArbol Delta;
	Delta = CreateSetVacio();
	int opc, b;
	
	do {
		printf("\n¿Desea agregar una transición? ([1] Sí / [0] No): ");
		scanf("%d", &opc);
		if (opc != 0) {
			str origen, simbolo;
			tArbol transicion, nodoOrig, nodoSimb, nodoDest, nodoTrans, aux;
			do {
				printf("\n-Ingrese el estado origen: ");
				origen = load();
				nodoOrig = crearNodoSTR(origen);
				if (pertenece(nodoOrig, Q)==0) 
					printf("*** El estado origen no pertenece a Q. Intente nuevamente.\n");
			}while (pertenece(nodoOrig, Q)==0);
			
			do {
				printf("\n-Ingrese el simbolo: ");
				simbolo = load();
				nodoSimb = crearNodoSTR(simbolo);
				if (pertenece(nodoSimb, Sigma)==0) 
					printf("*** El simbolo no pertenece al alfabeto SIGMA. Intente nuevamente.\n");
			}while (pertenece(nodoSimb, Sigma)==0);
			
			
			do {
				printf("\n-Ingrese el estado destino:\n");
				nodoDest = cargarDestino(); 
				
				if (retNodeType(nodoDest) == STR) {
					if (pertenece(nodoDest, Q)==0) 
						printf("*** El estado destino no pertenece a Q. Intente nuevamente.\n");
					else 
						b = 1;
				} 
				else{
					if (retNodeType(nodoDest) == SETT) {
						aux = nodoDest;
						b = 1;
						while (aux != NULL && retData(aux) != NULL) {
							if (pertenece(retData(aux), Q)==0) {
								printf("*** Uno o más estados destino no pertenecen a Q. Intente nuevamente.\n");
								b = 0;
								break;
							}
							aux = retNext(aux);
						}
					}
				}
			} while (b==0);
			
			transicion = inicializarLista();
			saveData(&transicion,nodoOrig);
			AgregaPorColaArb(&transicion, crearNodoStruct(LIST, nodoSimb));
			AgregaPorColaArb(&transicion, crearNodoStruct(LIST, nodoDest));
			
			if (retData(Delta) != NULL) {
				nodoTrans = crearNodoStruct(SETT, transicion);
				AgregaPorColaArb(&Delta, nodoTrans);
			} else {
				saveData(&Delta, transicion);
			}
		}
	} while (opc != 0);
	
	return Delta;
}

T_AF cargarAF() {
	T_AF M;
	tArbol aux;
	int b;
	
	printf("\n==== CARGA DEL AUTOMATA FINITO ====\n");
	
	printf("\nIngrese el conjunto de estados (Q):\n");
	M.Q = cargarSet();
	
	printf("\nIngrese el alfabeto (Sigma):\n");
	M.Sigma = cargarSet();
	
	printf("\nIngrese las transiciones (Delta):\n");
	M.Delta = cargarTransiciones(M.Q,M.Sigma);
	
	do{
		printf("\nIngrese el estado inicial (q0): ");
		M.q0 = load();
		if(pertenece(crearNodoSTR(M.q0),M.Q)==0)
			printf("*** El estado inicial (q0) no pertenece a Q. Intente nuevamente.\n");
	}while(pertenece(crearNodoSTR(M.q0),M.Q)==0);
	
	do{
		printf("\nIngrese el conjunto de estados finales (F):\n");
		M.estFin = cargarSet();
		aux = M.estFin;
		b = 1;
		while (aux != NULL && retData(aux) != NULL) {
			if (pertenece(retData(aux), M.Q)==0) {
				printf("*** Uno o más estados finales (F) no pertenecen a Q. Intente nuevamente.\n");
				b = 0;
				break;
			}
			aux = retNext(aux);
		}
	}while(b==0);
	return M;
}


int esAFD(T_AF A) {
	tArbol delta, act, transicion, dest;
	delta = A.Delta;
	
	if (retData(delta) == NULL) {
		printf("El conjunto de transiciones está vacío.\n");
		return 0;
	}
	
	act = delta;
	
	while (act != NULL) {
		transicion = retData(act);  
		dest = retNext(retNext(transicion));
		
		if (retNodeType(retData(dest)) == SETT) 
			return 0;
		
		act = retNext(act);
	}
	
	return 1; // AFD
}

tArbol cargarDeltaHardcodeada(str S) {
	SET transiciones, aux, partsEst, paux, destSet;
	str sinBrackets, content;
	tArbol Delta, transicion, nodoStr, conjDest, nodoTrans;
	int i;
	char c;
	
	transiciones = strToSetToken(S, '#');
	aux = transiciones;
	
	Delta = CreateSetVacio();
	
	while (aux != NULL) {
		
		sinBrackets = beforeToken(afterToken(retElemetSet(aux), '['), ']');
		
		partsEst = strToSetToken(sinBrackets, ',');
		paux = partsEst;
		
		transicion = inicializarLista();
		i = 0;
		
		while (paux != NULL) {
			if (i < 2) {
				nodoStr = crearNodoSTR(retElemetSet(paux));
				if(i==0)
					saveData(&transicion,nodoStr);
				else
					AgregaPorColaArb(&transicion, crearNodoStruct(LIST, nodoStr));
			} 
			else {
				c = retCaracter(retElemetSet(paux));
				if (c == '{') {
					content = beforeToken(afterToken(retElemetSet(paux), '{'), '}');
					destSet = strToSetToken(content, ';');
					conjDest = cargarSetCadHC(destSet);
					AgregaPorColaArb(&transicion,crearNodoStruct(LIST, conjDest));
				} 
				else {
					nodoStr = crearNodoSTR(retElemetSet(paux));
					AgregaPorColaArb(&transicion, crearNodoStruct(LIST, nodoStr));
				}
			}
			recorrerSET(&paux);
			i++;
		}
		
		if(retData(Delta)!=NULL){
			nodoTrans = crearNodoStruct(SETT, transicion);
			AgregaPorColaArb(&Delta, nodoTrans);
		}
		else
		   saveData(&Delta,transicion);
		
		recorrerSET(&aux);
	}
	
	return Delta;
}


T_AF cargarAFhardcodeada(str S) {
	T_AF M;
	SET partes, aux;
	str q0,sinKeys;
	int pos = 0;
	
	partes = strToSetToken(S, '*'); 
	
	aux = partes;
	while (aux != NULL) {
		switch (pos) {
		case 0:
			sinKeys = beforeToken(afterToken(retElemetSet(aux), '{'), '}'); 
			M.Q = cargarSetCadHC(strToSetToken(sinKeys,','));
			break;
		case 1:
			sinKeys = beforeToken(afterToken(retElemetSet(aux), '{'), '}'); 
			M.Sigma = cargarSetCadHC(strToSetToken(sinKeys,',')); 
			break;
		case 2:
			M.Delta = cargarDeltaHardcodeada(retElemetSet(aux)); 
			break;
		case 3:
			q0 = retElemetSet(aux);
			M.q0 = q0; 
			break;
		case 4:
			sinKeys = beforeToken(afterToken(retElemetSet(aux), '{'), '}'); 
			M.estFin = cargarSetCadHC(strToSetToken(sinKeys,',')); 
			break;
		}
		pos++;
		recorrerSET(&aux);
	}
	
	return M;
}

int MenuConsulta(){
	int o;
	printf("\nCONSULTA:\n");
	printf("\n[1]Conjunto de estados.\n[2]Alfabeto (Sigma) del automata.\n[3]Conjunto de transiciones (Delta). \n[4]Estado inicial \n[5]Estado de aceptacion \n");
	printf("Ingrese elemento de la 5-upla que quiere consultar: ");
	scanf("%d", &o);
	return o;
}

void consulta(T_AF A){
	int o, f;
	do{
		o=MenuConsulta();
		switch(o){
		case 1:
			printf("\nQ = ");
			mostrarSet(A.Q);
			break;
		case 2:
			printf("\nSigma = ");
			mostrarSet(A.Sigma);
			break;
		case 3:
			printf("\nDelta =");
			mostrarSet(A.Delta);
			break;
		case 4:
			printf("\nq0 = ");
			print(A.q0);
			break;
		case 5:
			printf("\nF = ");
			mostrarSet(A.estFin);
			break;
		default:
			printf("\nOpcion invalida.\n");
		}
		printf("\n\n¿Desea consultar algo mas? [1]si [1]no: ");
		scanf("%d", &f);
	} while(f != 0);
}
	
tArbol retSigma(str c){ //TERMINEN Y AGREGUENLO EN EL MODULO DE AceptacionDeCad
	tArbol A;
	A = CreateSetVacio();
	A = strToTree(c);
	return A;
}
	
str deltaAFD(T_AF A, str estAct, str simbAct) {
	tArbol transiciones, transicion, orig, simb, dest;
	
	transiciones = A.Delta;
	
	while (transiciones != NULL) {
		transicion = retData(transiciones); 
		
		orig = retData(transicion);
		simb = retData(retNext(transicion));
		dest = retData(retNext(retNext(transicion)));
		
		if (cmpstr(retSTR(orig), estAct) == 0 && cmpstr(retSTR(simb), simbAct) == 0) 
			return loadcpy(retSTR(dest)); 
		
		transiciones = retNext(transiciones);
	}
	
	return NULL;
}

tArbol deltaAFND(T_AF A, str estAct, str simbAct) {
	tArbol conjDest, transiciones, transicion, orig, simb, dest, aux, copia;
	
	transiciones = A.Delta;
	conjDest = CreateSetVacio();
	
	while (transiciones != NULL) {
		transicion = retData(transiciones);  
		
		orig = retData(transicion);
		simb = retData(retNext(transicion));
		dest = retData(retNext(retNext(transicion)));
		
		if (cmpstr(retSTR(orig), estAct) == 0 && cmpstr(retSTR(simb), simbAct) == 0) {
			aux = dest;
			while (aux != NULL) {
				copia = cpyArbol(retData(aux)); 
				if (retData(conjDest) != NULL)
					AgregaPorColaArb(&conjDest, crearNodoStruct(SETT, copia));
				else
					saveData(&conjDest,copia);
				aux = retNext(aux);
			}
			return conjDest;
		}
		
		transiciones = retNext(transiciones);
	}
	
	return conjDest;
}

	
int AceptacionDeCad(T_AF A, str S) {
	tArbol estFin, estIni, estsActuales, nvoEsts, aux, dest, conj;
	str simb, estAct, sig;
	int b;
	if(esAFD(A)){
		estAct = loadcpy(A.q0); 
		while (S != NULL) {
			simb = create(retCaracter(S));
			sig = deltaAFD(A, estAct, simb);
			
			if (sig == NULL) {
				printf("*** No hay transicion definida para el símbolo '%c' desde el estado actual.\n", retCaracter(S));
				liberarStr(&estAct);
				return 0; 
			}
			
			liberarStr(&estAct);
			estAct = sig;
			recorrerStr(&S); 
		}
		
		estFin = crearNodoSTR(estAct);
		b = pertenece(estFin, A.estFin);
		liberarStr(&estAct);
		
		return b;
	}
	else{
		
		estIni = crearNodoSTR(A.q0);
		estsActuales = CreateSetVacio();
		saveData(&estsActuales, estIni);
		while (S != NULL) {
			simb = create(retCaracter(S));
			
			nvoEsts = CreateSetVacio();
			
			aux = estsActuales;
			while (aux != NULL) {
				if(retData(aux)!=NULL)
					dest = deltaAFND(A, retSTR(retData(aux)), simb); 
				
				if (retData(dest) != NULL) 
					nvoEsts = UNION(nvoEsts, dest);
				
				aux = retNext(aux);
			}
			
			estsActuales = nvoEsts;
			recorrerStr(&S);
		}
		conj = INTERSECCION(estsActuales, A.estFin);
		if (retData(conj)!=NULL) 
			return 1; 
		else
			return 0;
	}
}
