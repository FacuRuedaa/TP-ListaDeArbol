#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idPaciente;
    char nombrePaciente[30];
    char apellidoPaciente[30];
    char diagnostico[100];
    char fechaAtencion[11];
    char nombreDoctor[30];
} stPaciente;

typedef struct nodoArbol{
    stPaciente dato;
    struct nodoArbol *izq;
    struct nodoArbol *der;
}nodoArbol;

nodoArbol* inicArbol ();
nodoArbol* crearNodoArbol (stPaciente dato);
nodoArbol* agregaArbol (nodoArbol* arbol, stPaciente dato);
void preorder (nodoArbol* arbol);
///void inorder (nodoArbol* arbol);
///void postorder (nodoArbol* arbol);
nodoArbol* buscarDatoArbol (nodoArbol* arbol, stPaciente dato);
int cuentaNodosTerminales (nodoArbol* arbol);
int nodoHoja (nodoArbol* arbol);
int cuentaNodos (nodoArbol* arbol);
int ramaMayor (int izquierda, int derecha);
int alturaArbol (nodoArbol* arbol);
nodoArbol* nodoMasDerecha(nodoArbol *arbol);
nodoArbol* nodoMasIzquierda(nodoArbol *arbol);

#endif // ARBOL_H_INCLUDED
