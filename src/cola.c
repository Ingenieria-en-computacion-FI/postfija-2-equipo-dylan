#include "../include/cola.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Cola* crearCola(){
    Cola* nuevo_cola = (Cola*)malloc(sizeof(Cola));
    if(nuevo_cola==NULL){
        return NULL;
    } else {
        nuevo_cola->frente=NULL;
        nuevo_cola->final=NULL;
        return nuevo_cola;
    }
}

void enqueue(Cola* c, void *dato, size_t size){
    NodoCola* nuevo = (NodoCola*)malloc(sizeof(NodoCola));
    nuevo->dato = malloc(size);
    memcpy(nuevo->dato, dato, size);
    nuevo->siguiente = NULL;
    if((c->frente==NULL)&&(c->final==NULL)){
        c->frente=nuevo;
        c->final=nuevo;
    } else {
        c->final->siguiente=nuevo;
        c->final=nuevo;
    }
}

char dequeue(Cola* c){
    if(colaVacia(c)){
        return '\0';
    } else {
        NodoCola* tmp = c->frente;
        char valor = *(char*)(tmp->dato);
        c->frente = c->frente->siguiente;
        if(c->frente==NULL){
            c->final=NULL;
        }
        free(tmp->dato);
        free(tmp);
        return valor;
    }
}

int colaVacia(Cola* c){
    if((c->frente==NULL)&&(c->final==NULL)){
        return 1;
    } else {
        return 0;
    }
}

void imprimirCola(Cola* c){
    NodoCola* tmp = c->frente;
    while(tmp!=NULL){
        char v = *(char*)(tmp->dato);
        printf("%c ", v);
        tmp = tmp->siguiente;
    }
    printf("\n");
}

void destruirCola(Cola* c){
    while(colaVacia(c)==0){
        dequeue(c);
    }
    free(c);
}
