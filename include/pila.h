#ifndef __PILA_H__
#define __PILA_H__

#include <stddef.h>

typedef struct NodoPila {
    void *dato;
    struct NodoPila* siguiente;
} NodoPila;

typedef struct {
    NodoPila* tope;
} Pila;

Pila* crearPila();

void push(Pila* p, void *dato, size_t size);
void* pop(Pila* p);
void* peek(Pila* p);

int pilaVacia(Pila* p);

void destruirPila(Pila* p);

#endif
