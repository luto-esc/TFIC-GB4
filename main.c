#include <stdio.h>
#include <stdlib.h>
#include "artemis.h"
#include "validaciones.h"
#include "simulador.h"

int main(void)
{
    #ifdef _WIN32
        system("chcp 65001 > nul");   /* acentos en la consola de Windows (en Linux no hace falta) */
    #endif
    Mision miMision;
    Simulacion *historial = NULL; /* Lista de reportes al empezar esta vacia*/
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
        printf("2) Preguntas para análisis\n");
        printf("3) Guardar/Cargar reporte\n");
        printf("0) Salir\n");
        printf("================================\n");
        opcion = leer_entero("Ingrese una opcion: ", 0, 3);
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
            historial = menu_reportes(historial, &miMision);
            limpiarPantalla();
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
    historial = disponer_reportes(historial); /* devolver memoria*/
    printf("Programa finalizado.\n");
    return 0;
}
