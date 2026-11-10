#include <stdio.h>
#include <stdlib.h>
#include "artemis.h"
#include "validaciones.h"

int main(void)
{
    system("chcp 65001 > nul");
    Mision miMision;
    int opcion;
    char confirmar;

    miMision.masa = MASA_ORION;
    miMision.velocidadInicial = VELOCIDAD_TLI;
    miMision.distanciaTierraLuna = DISTANCIA_LUNA;
    miMision.alturaOrbital = ALTURA_ORBITAL;

    opcion = 9;
    while (opcion != 0)
    {
        printf("================================\n");
        printf("        MENU PRINCIPAL\n");
        printf("================================\n");
        printf("1) Configurar misión (masa, v, D, h)\n");
        printf("2) Preguntas de análisis\n");
        printf("3) Simular misión\n");
        printf("4) Ranking de simulaciones\n");
        printf("5) Guardar/Cargar reporte\n");
        printf("0) Salir\n");
        printf("================================\n");
        opcion = leer_entero("Ingrese una opcion: ", 0, 5);
        limpiarPantalla();

        switch (opcion)
        {
        case 1:
            configurarMision(&miMision);
            limpiarPantalla();
            break;
        case 2:
            preguntasAnalisis(&miMision);
            limpiarPantalla();
            break;
        case 3:
            printf("Aún no disponible\n");
            pausar();
            break;
        case 4:
            printf("Aún no disponible\n");
            pausar();
            break;
        case 5:
            printf("Aún no disponible\n");
            pausar();
            break;
        case 0:
            confirmar = leer_caracter("¿Seguro desea cerrar el programa? (y/n): ", "yYnN");
            if (confirmar == 'n' || confirmar == 'N')
            {
                opcion = 9;
                limpiarPantalla();
            }
            break;
        }
    }
    printf("Programa finalizado.\n");
    return 0;
}
