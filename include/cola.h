#ifndef __COLA_H__
#define __COLA_H__

#include <stddef.h>

typedef struct NodoCola {
    void *dato;
    struct NodoCola* siguiente;
} NodoCola;

typedef struct {
    NodoCola* frente;
    NodoCola* final;
} Cola;

Cola* crearCola();

void enqueue(Cola* c, void *dato, size_t size);
char dequeue(Cola* c);

int colaVacia(Cola* c);

void imprimirCola(Cola* c);

void destruirCola(Cola* c);

#endif
