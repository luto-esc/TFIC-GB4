#include <stdio.h>
#include <stdlib.h>
#include "validaciones.h"

int leer_entero(const char *mensaje, int minimo, int maximo) {
    char linea[100];
    char *fin;
    long valor;

    while (1) {
        printf("%s", mensaje);
        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            exit(1);
        }
        valor = strtol(linea, &fin, 10);
        
        /* COMPLETAR: tres chequeos*/
    }
}