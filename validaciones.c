#include <stdio.h>
#include <stdlib.h>
#include "validaciones.h"

void limpiarPantalla(void)
{
    system("cls");
}

int leer_entero(const char *mensaje, int minimo, int maximo) 
{
    char linea[100];
    char *fin;
    long valor;

    while (1)
    {
        printf("%s", mensaje);
        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            exit(1);
        }
        valor = strtol(linea, &fin, 10);
        
        if (fin == linea) {
            printf("Error: no ingresaste un numero.\n");
            continue;
        }
        if (*fin != '\n' && *fin != '\0') {
            printf("Error: ingrese solamente numeros.\n");
            continue;
        }
        if (valor < minimo || valor > maximo) {
            printf("Error: fuera de rango (%d a %d).\n", minimo, maximo);
            continue;
        }
        return (int)valor;
    }
}

double leer_flotante(const char *mensaje, double minimo, double maximo) {
    char linea[100];
    char *fin;
    double valor;

    while (1) {
        printf("%s", mensaje);
        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            exit(1);
        }
        valor = strtod(linea, &fin);

        if (fin == linea) {
            printf("Error: no ingresaste un numero.\n");
            continue;
        }
        if (*fin != '\n' && *fin != '\0') {
            printf("Error: ingrese solo un numero (decimales con punto, ej: 10.5).\n");
            continue;
        }
        if (!(valor >= minimo && valor <= maximo)) {
            printf("Error: fuera de rango (%.2f a %.2f).\n", minimo, maximo);
            continue;
        }
        return valor;
    }
}