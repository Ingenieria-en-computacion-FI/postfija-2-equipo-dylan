#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "../include/evaluator.h"
#include "../include/pila.h"

float obtenerValorVariable(
    Variable variables[],
    int total,
    char nombre
)  {
    for (int i = 0; i < total; i++) {
        if (variables[i].nombre == nombre) {
            return variables[i].valor;
        }
    }

    return 0;

}

float evaluarPostfija(
    Cola* postfija,
    Variable variables[],
    int totalVariables
)  {
    Pila* pila = crearPila();

    while (!colaVacia(postfija)) {

        char token = dequeue(postfija);

        if (isalnum(token)) {

            float valor;

            if (isalpha(token)) {
                valor = obtenerValorVariable(
                    variables,
                    totalVariables,
                    token
                );
            }
            else {
                valor = token - '0';
            }

            push(pila, &valor, sizeof(float));
        }
         else if (esOperador(token)) {

            float b = *(float*)pop(pila);
            float a = *(float*)pop(pila);
            float resultado;

            switch (token) {
                case '+':
                    resultado = a + b;
                    break;

                case '-':
                    resultado = a - b;
                    break;

                case '*':
                    resultado = a * b;
                    break;

                case '/':
                    resultado = a / b;
                    break;

                case '^':
                    resultado = pow(a, b);
                    break;
                
                 default:
                    resultado = 0;
            }

            push(pila, &resultado, sizeof(float));
        }
    }

    float final = *(float*)pop(pila);

    destruirPila(pila);

    return final;

}