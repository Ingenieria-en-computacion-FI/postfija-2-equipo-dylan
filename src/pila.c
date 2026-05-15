#include "../include/pila.h"
#include <stdlib.h>
#include <string.h>

Pila* crearPila(){
    Pila* nueva_pila = (Pila*)malloc(sizeof(Pila));
    if(nueva_pila==NULL){
        return NULL;
    } else {
        nueva_pila->tope = NULL;
        return nueva_pila;
    }
}

void push(Pila* p, void* dato, size_t size){
    NodoPila* nuevo = (NodoPila*)malloc(sizeof(NodoPila));
    nuevo->dato = malloc(size);
    memcpy(nuevo->dato, dato, size);
    nuevo->siguiente = p->tope;
    p->tope = nuevo;
}

void* pop(Pila* p){
    if(pilaVacia(p)){
        return NULL;
    } else {
        NodoPila* tmp = p->tope;
        void* valor = tmp->dato;
        p->tope = p->tope->siguiente;
        free(tmp);
        return valor;
    }
}

int pilaVacia(Pila* p){
    if(p->tope==NULL){
        return 1;
    } else {
        return 0;
    }
}

void destruirPila(Pila* p){
    while(pilaVacia(p)==0){
        void* d = pop(p);
        free(d);
    }
    free(p);
}
