#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"

/* ================= CALCULOS ================= */

double calcularEnergiaCinetica(const Mision *mision)
{
    double energia;

    energia = 0.5 * mision->masa *
              mision->velocidadInicial *
              mision->velocidadInicial;

    return energia;
}

/* Menú de configuración de la misión */

void configurarMision(Mision *mision)
{
    int opcion;
    do
    {
        // Mostrar los valores actuales.
        printf("================================\n");
        printf("     CONFIGURAR MISIÓN\n");
        printf("================================\n");
        printf(" \n");
        printf("Masa: %.2f kg\n", mision->masa);
        printf("Velocidad inicial: %.2f m/s\n", mision->velocidadInicial);
        printf("Distancia Tierra-Luna: %.2f m\n", mision->distanciaTierraLuna);
        printf("Altura orbital: %.2f m\n", mision->alturaOrbital);

        // Mostrar el menú de configuración.
        printf(" \n");
        printf("Seleccione el parámetro a modificar:\n");
        printf(" \n");
        printf("1) Masa\n");
        printf("2) Velocidad inicial\n");
        printf("3) Distancia Tierra-Luna\n");
        printf("4) Altura orbital\n");
        printf("0) Volver al menú principal\n");

        // Leer qué parámetro desea modificar (validado).
        opcion = leer_entero("Ingrese una opcion: ", 0, 4);

        // Actualizar el campo correspondiente.
        switch (opcion)
        {
            case 1:
                mision->masa = leer_flotante("Ingrese la nueva masa (kg): ", 1.0, 1000000.0);
                limpiarPantalla();
                break;
            case 2:
                mision->velocidadInicial = leer_flotante("Ingrese la nueva velocidad inicial (m/s): ", 1.0, 15000.0);
                limpiarPantalla();
                break;
            case 3:
                mision->distanciaTierraLuna = leer_flotante("Ingrese la nueva distancia Tierra-Luna (m): ", 1000000.0, 1000000000.0);
                limpiarPantalla();
                break;
            case 4:
                mision->alturaOrbital = leer_flotante("Ingrese la nueva altura orbital (m): ", 100000.0, 2000000.0);
                limpiarPantalla();
                break;
            case 0:
                printf("Volviendo al menú principal...\n");
                break;
        }
    } while (opcion != 0);
}

/* Menú de preguntas de análisis */

void preguntasAnalisis(const Mision *mision)
{
    int opcion;

    do
    {
        printf("================================\n");
        printf("     PREGUNTAS DE ANÁLISIS\n");
        printf("================================\n\n");
        printf("¿Qué desea analizar?\n");
        printf("1) Aplicar y analizar la primera ley de Newton\n");
        printf("2) Calcular la energía cinética inicial\n");
        printf("3) Trabajo externo mínimo hasta el punto de equilibrio\n");
        printf("4) Comparación energética entre alunizaje y aterrizaje.\n");
        printf("0) Volver al menú principal\n");

        opcion = leer_entero("Ingrese una opcion: ", 0, 4);
        limpiarPantalla();

        switch (opcion)
        {
            case 1:
                printf("Aún no se ha implementado\n");
                pausar();
                break;
            case 2:
                analizarEnergiaCinetica(mision);
                pausar();
                break;
            case 3:
                printf("Aún no se ha implementado\n");
                pausar();
                break;
            case 4:
                printf("Aún no se ha implementado\n");
                pausar();
                break;
        }
    } while (opcion != 0);
}

// b) Energia cinetica inicial
void analizarEnergiaCinetica(const Mision *mision)
{
    double energia;

    energia = calcularEnergiaCinetica(mision);

    printf("=== ENERGÍA CINÉTICA INICIAL ===\n\n");
    printf("Formula: Ec = 1/2 * m * v^2\n");
    printf("Masa: %.2f kg\n", mision->masa);
    printf("Velocidad: %.2f m/s\n", mision->velocidadInicial);
    printf("\nEnergia cinetica inicial: %.4e J\n", energia);
    printf("Por unidad de masa: %.4e J/kg\n", energia / mision->masa);
}
