#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "validaciones.h"

void limpiarPantalla(void)
{
    system("cls");
}
void pausar(void)
{
    printf("\nPresione una tecla para continuar...");
    _getch();
    limpiarPantalla();
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

char leer_caracter(const char *mensaje, const char *validos) {
    char linea[100];

    while (1) {
        printf("%s", mensaje);
        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            exit(1);
        }
        
                if (linea[0] == '\n') {
            printf("Error: no se escribio ningun caracter.\n");
            continue;
        }
        if (linea[1] != '\n' && linea[1] != '\0') {
            printf("Error: ingrese solo un caracter.\n");
            continue;
        }
        if (strchr(validos, linea[0]) == NULL) {
            printf("Error: caracter no permitido.\n");
            continue;
        }
        return linea[0];
    }
}