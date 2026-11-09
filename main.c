#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "artemis.h"
#include "validaciones.h"

int opcion;
double resultado;
char confirmar;

int main(void) 
{
    system("chcp 65001 > nul");
    Mision miMision;
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
        printf("2) Analisis de resultados\n");
        printf("3) Simular misión\n");
        printf("4) Ranking de simulaciones\n");
        printf("5) Guardar/Cargar reporte\n");
        printf("0) Salir\n");
        printf("================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        limpiarPantalla();
        switch (opcion)
        {
        case 1:
            configurarMision(&miMision);
            break;
        case 2:
        {
            printf("Calculando energía cinética...\n");
            double energia = calcularEnergiaCinetica(&miMision);
            printf("Energia cinetica: %.2f J\n", energia);
            break;
        }
        case 3:
            printf("Seleccionó Simular misión\n");
            break;
        case 4:
            printf("Seleccionó Ranking de simulaciones\n");
            break;
        case 5:
            printf("Seleccionó Guardar/Cargar reporte\n");
            break;
        case 0:
            printf("¿Seguro desea cerrar el programa? (y/n): ");
            scanf(" %c", &confirmar);
            if (confirmar == 'y' || confirmar == 'Y')
            {
                opcion = 0;
            }
            else
            {
                opcion = 9;
                limpiarPantalla();
            }
            break;
        default:
            printf("Opción inválida. Por favor, seleccione una opción válida.\n");
            break;
        }
        if (opcion != 0 && opcion != 9)
        {
            _getch();
            limpiarPantalla();
        }       
    }
    return 0;
}