#include <stdio.h>
#include <ctype.h>

#include "../include/parser.h"
#include "../include/pila.h"

void cargarArchivo(
    const char* nombreArchivo,
    Variable variables[],
    int* totalVariables,
    char expresion[]
) {

   FILE* archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    char linea[256];

    *totalVariables = 0;

    while (fgets(linea, sizeof(linea), archivo)) {

        linea[strcspn(linea, "\n")] = '\0';

        if (strchr(linea, '=')) {

            char* token = strtok(linea, "=");

            variables[*totalVariables].nombre = token[0];

            token = strtok(NULL, "=");

            variables[*totalVariables].valor = atof(token);

            (*totalVariables)++;
        }else{
             strcpy(expresion, linea);
        } 
    }
    fclose(archivo);
}   

int esOperador(char c){

    return c == '+' ||
           c == '-' ||
           c == '*' ||
           c == '/' ||
           c == '^';
}

int precedencia(char op){

    switch(op){

        case '^':
            return 3;

        case '*':
        case '/':
            return 2;

        case '+':
        case '-':
            return 1;

        default:
            return 0;
    }
}

Cola* infijaAPostfija(char* expresion){

    Cola* salida = crearCola();

    Pila* operadores = crearPila();

    int i = 0;

    while(expresion[i] != '\0'){

        char token = expresion[i];

        if(token == ' '){
            i++;
            continue;
        }

        if(isalnum(token)){

            enqueue(salida, &token, sizeof(char));
        }

        else if(token == '('){

            push(operadores, &token, sizeof(char));
        }
        else if(token == ')'){

            while(
                !pilaVacia(operadores) &&
                *(char*)operadores->tope->dato != '('
            ){

                char op = *(char*)pop(operadores);

                enqueue(salida, &op, sizeof(char));
            }

            free(pop(operadores));
        }

        else if(esOperador(token)){
             while(
                !pilaVacia(operadores) &&
                precedencia(*(char*)operadores->tope->dato)
                    >= precedencia(token)
            ){

                char op = *(char*)pop(operadores);

                enqueue(salida, &op, sizeof(char));
            }

            push(operadores, &token, sizeof(char));
        }

        i++;
    }
      while(!pilaVacia(operadores)){

        char op = *(char*)pop(operadores);

        enqueue(salida, &op, sizeof(char));
    }

    destruirPila(operadores);

    return salida;
  
}
