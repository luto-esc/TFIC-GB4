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
        
        if (fin == linea) {
            printf("Error: no se ingreso un numero.\n");
            continue;
        }

        if (*fin !='\n' && *fin != '\0') {
            printf("Error: se ingreso un valor no numerico.\n");
            continue;
        }

        if (valor < minimo || valor > maximo) {
            printf("Error: fuera de rango (%d a %d). \n", minimo, maximo);
            continue;
        }

        return (int)valor;
    }
}