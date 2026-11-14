#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validaciones.h"

/* conio.h (de donde sale _getch) solo existe en Windows. */
#ifdef _WIN32
    #include <conio.h>
#endif

void limpiarPantalla(void)
{
#ifdef _WIN32
    system("cls");      /* Windows */
#else
    system("clear");    /* Linux y macOS */
#endif
}
void pausar(void)
{
#ifdef _WIN32
    printf("\nPresione una tecla para continuar...");
    _getch();           /* Windows: sigue apenas se aprieta una tecla */
#else
    printf("\nPresione Enter para continuar...");
    getchar();          /* Linux: getchar necesita que se apriete Enter */
#endif
    limpiarPantalla();
}
/*
leer_entero: pide un entero por consola hasta que sea valido.
Parametros: 
    mensaje - texto que se muestra al usuario
    minimo, maximo - limites permitidos
Retorna: el entero ingresado, ya validado.
Nota: rechaza letras, basura despues del numero y valores fuera de rango.
*/

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
/*
leer_flotante: pide un numero decimal por consola hasta que sea valido.
Parametros:
    mensaje - texto que se muestra al usuario
    minimo, maximo - limites permitidos (inclusive)
Retorna: el numero decimal ingresado (double), ya validado.
Nota: los decimales se escriben con punnto (10.5), no con coma. 
Rechaza letras y valores fuera de rango.
*/
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
/*
leer_caracter: pide un unico caracter por consola hasta que sea valido.
Parametros:
   mensaje - texto que se muestra al usuario
   validos - texto con los caracteres permitidos (ej: "sn")
Retorna: el caracter ingresado, que esta dentro de validos.
Nota: rechaza si se ingresa mas de un caracter, si se aprieta solo
Enter, o si el caracter no esta en validos.
*/
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