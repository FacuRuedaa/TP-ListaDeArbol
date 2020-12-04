#include <stdio.h>
#include <stdlib.h>
#include "registroArchivo.h"
#include "Arbol.h"

typedef struct{
    int idEspecialidad;
    char especialidadMedica[30];
    nodoArbol* listaDePacientes;
    struct nodoLista* siguiente;
} nodoLista;

nodoLista* inicListaEspecialidad();
nodoLista* crearNodoEspecialidad(int nroEspecialidad, char especialidad[]);
nodoLista* agregarAlPrincipioEspecialidad(nodoLista* lista, nodoLista* nuevo);
nodoLista * BuscarEspecialidad(nodoLista * lista, int nroEsp);
nodoLista * alta (nodoLista *lista, nodoArbol* nuevoPac, int nroEsp, char especialidad[]);
void muestraListaEspecialidad(nodoLista* lista);
nodoLista* pasarArchToLista (nodoLista* lista, char archivo[]);
void muestraEspecialidad(nodoLista *lista);
void muestraUnaEspecialidad (nodoLista* a);

int main()
{
    nodoLista* listaEspecialidades = inicListaEspecialidad();

    listaEspecialidades = pasarArchToLista(listaEspecialidades, arRegistro);

    muestraListaEspecialidad(listaEspecialidades);

    return 0;
}


nodoLista* inicListaEspecialidad(){
    return NULL;
}

nodoLista* crearNodoEspecialidad(int nroEspecialidad, char especialidad[]){
    nodoLista* nuevo = (nodoLista*) malloc(sizeof(nodoArbol));
    nuevo->idEspecialidad = nroEspecialidad;
    strcpy(nuevo->especialidadMedica, especialidad);
    nuevo->listaDePacientes = inicArbol();
    nuevo->siguiente = NULL;
    return nuevo;
}

nodoLista* agregarAlPrincipioEspecialidad(nodoLista* lista, nodoLista* nuevo){
    if(lista==NULL){
        lista = nuevo;
    }else{
        nuevo->siguiente = lista;
        lista = nuevo;
    }
    return lista;
}

nodoLista * BuscarEspecialidad(nodoLista * lista, int nroEsp)
{
    nodoLista * seg = lista;
    nodoLista *espEncontrada = NULL;
    int flag = 0;
        while(seg!= NULL && flag == 0)
        {
            if(seg->idEspecialidad == nroEsp)
            {
                espEncontrada = seg;
                flag=1;
            }
            seg = seg->siguiente;
        }
    return espEncontrada;
}

nodoLista * alta (nodoLista *lista, nodoArbol* nuevoPac, int nroEsp, char especialidad[])
{
    nodoLista *espEncontrada = BuscarEspecialidad(lista, nroEsp);
    if(espEncontrada==NULL)
    {
        nodoLista *aux = crearNodoEspecialidad(nroEsp, especialidad);
        lista = agregarAlPrincipioEspecialidad(lista, aux);
        lista->listaDePacientes = agregaArbol(lista->listaDePacientes, nuevoPac->dato);
    } else{
        espEncontrada->listaDePacientes = agregaArbol(espEncontrada->listaDePacientes, nuevoPac->dato);
    }
    return lista;
}

nodoLista* pasarArchToLista (nodoLista* lista, char archivo[]){
    FILE * pArchRegistro = fopen(archivo, "rb");
    stRegistroMedico r;
    stPaciente p;

    if (pArchRegistro){
        while (fread(&r, sizeof(stRegistroMedico), 1, pArchRegistro)>0){
            p.idPaciente = r.idPaciente;
            strcpy(p.apellidoPaciente, r.apellidoPaciente);
            strcpy(p.diagnostico, r.diagnostico);
            strcpy(p.fechaAtencion, r.fechaAtencion);
            strcpy(p.nombreDoctor, r.nombreDoctor);
            strcpy(p.nombrePaciente, r.nombrePaciente);
            nodoArbol* paciente = crearNodoArbol(p);
            lista = alta(lista, paciente, r.idEspecialidad, r.especialidadMedica);
        }
        fclose(pArchRegistro);
    }
    return lista;
}

void muestraListaEspecialidad(nodoLista* lista){
    nodoLista* seg = lista;
    while(seg){  /// while(lista!=NULL)
        muestraEspecialidad(seg);
        seg = seg->siguiente;
    }
}

void muestraEspecialidad(nodoLista *lista){
    ///printf("\n nodoPaciente: %p - nodoPaciente->siguiente: %p\n",  lista, lista->siguiente);
    muestraUnaEspecialidad(lista);
}

void muestraUnaEspecialidad (nodoLista* a)
{
    printf("-----------------------------\n");
    printf("\nID DE LA ESPECIALIDAD...: %d", a->idEspecialidad);
    printf("\nESPECIALIDAD............: %s", a->especialidadMedica);
    printf("\n-----------------------------\n");
    printf("\nPACIENTES: \n");
    preorder(a->listaDePacientes);
}
