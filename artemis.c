#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"

double calcularEnergiaCinetica(const Mision *mision)
{
    double energia;

    energia = 0.5 * mision->masa *
              mision->velocidadInicial *
              mision->velocidadInicial;

    return energia;
}
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
        // Leer qué parámetro desea modificar.
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        
        // Actualizar el campo correspondiente.
        switch (opcion)
        {
            case 1:
                // Modificar masa.
                printf("Ingrese la nueva masa (kg): ");
                scanf("%lf", &mision->masa);
                limpiarPantalla();
                break;
            case 2:
                // Modificar velocidad.
                printf("Ingrese la nueva velocidad inicial (m/s): ");
                scanf("%lf", &mision->velocidadInicial);
                limpiarPantalla();
                break;
            case 3:
                // Modificar distancia.
                printf("Ingrese la nueva distancia Tierra-Luna (m): ");
                scanf("%lf", &mision->distanciaTierraLuna); 
                limpiarPantalla();
                break;
            case 4:
                // Modificar altura.
                printf("Ingrese la nueva altura orbital (m): ");
                scanf("%lf", &mision->alturaOrbital);   
                limpiarPantalla();
                break;
            case 0:
                // Volver al menú principal.
                printf("Volviendo al menú principal...\n");      
                break;
            default:
                // Opción inválida.
                printf("Opción inválida.\n");
                break;
        }
    } while (opcion != 0);
}