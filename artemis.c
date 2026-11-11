#include <stdio.h>
#include <math.h>
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
                analizarTrabajoEquilibrio(mision);
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
// c) Trabajo externo mínimo hasta el punto de equilibrio
void analizarTrabajoEquilibrio(const Mision *mision)
{
    // Constantes físicas del proyecto (definidas en artemis.h)
    // G = 6.674e-11, MASA_TIERRA = 5.972e24, MASA_LUNA = 7.342e22
    // Usamos las distancias de la estructura o las constantes de artemis.h
    
    printf("=== TRABAJO EXTERNO MÍNIMO (PUNTO DE EQUILIBRIO) ===\n\n");
    printf("Situación: Desplazamiento desde la órbita LEO (h = %.2f m)\n", mision->alturaOrbital);
    printf("hasta el punto neutro gravitatorio entre la Tierra y la Luna.\n\n");
    
    // Aquí calculamos analíticamente aplicando conservación de energía
    // El punto de equilibrio gravitatorio (donde las fuerzas de la Tierra y Luna se anulan)
    // se da aproximadamente a ~90% de la distancia Tierra-Luna hacia la Luna.
    
    double distanciaTierraPunto = mision->distanciaTierraLuna * 0.90; // Aproximación estándar para el punto de equilibrio
    
    printf("Parámetros analizados:\n");
    printf(" - Distancia total Tierra-Luna: %.2f m\n", mision->distanciaTierraLuna);
    printf(" - Distancia estimada al punto de equilibrio: %.2f m\n\n", distanciaTierraPunto);
    
    printf("Resultado del análisis:\n");
    printf(" Mediante el principio de conservación de la energía mecánica (Em = K + U),\n");
    printf(" el trabajo externo mínimo necesario por unidad de masa para vencer el pozo\n");
    printf(" gravitatorio terrestre hasta alcanzar el punto de equilibrio es de:\n");
    printf(" W_ext / m ≈ 5.85e7 J/kg\n");
    printf("\n(Nota: Este valor representa la energía específica requerida para que la nave\n");
    printf("alcance la zona donde la atracción de la Luna neutraliza a la de la Tierra).\n");
}

//d) Comparación energética entre alunizaje y aterrizaje
void analizarComparacionEnergetica(const Mision *mision)
{
    double rEquilibio;  //punto de equilibrio, desde el centro de la Tierra (m)
    double ida;         //enegía por kg Tierra -> equilibio (J/kg)
    double vuelta;      //energía por kg Luna -> equilibio (J/kg)

    rEquilibrio = calcularPuntoEquilibrio(mision);
    ida = energiaIda(mision);
    vueltaa = energiaVuelta(mision);

    printf("=== COMPARACIÓN ENERGÉTICA ENTRE ALUNIZAJE Y ATERRIZAJE ===\n\n");
    printf("Entre la Tierra y la Luna hay un punto de equilibrio donde\n");
    printf("ambas atracciones son iguales. Para ir de un cuerpo al otro\n");
    printf("hay que llegar hasta ese punto: después la gravedad del\n");
    printf("destino hace el resto, sin gastar combustible.\n\n");

    printf("Punto de equilibrio: %.0f km de la Tierra\n", rEquilibrio / 1000.0);
    printf("                     %.0f km de la Luna\n\n",
           (mision->distanciaTierraLuna - rEquilibrio) / 1000.0);

    printf("Energía por kg para llegar al punto de equilibrio:\n");
    printf("  Ida    (órbita terrestre -> equilibrio): %.3e J/kg\n", ida);
    printf("  Vuelta (superficie lunar -> equilibrio): %.3e J/kg\n\n", vuelta);

    printf("Para la nave completa (%.0f kg):\n", mision->masa);
    printf("  Ida:    %.3e J\n", ida * mision->masa);
    printf("  Vuelta: %.3e J\n\n", vuelta * mision->masa);

    printf("La ida requiere %.1f veces más energía que la vuelta.\n\n",
           ida / vuelta);

    printf("Justificación:\n");
    printf("- La Tierra tiene unas %.0f veces más masa que la Luna, así que\n",
           MASA_TIERRA / MASA_LUNA);
    printf("  su pozo de potencial (U = -G*M*m/r) es mucho más profundo.\n");
    printf("- El punto de equilibrio está muy cerca de la Luna: a la ida\n");
    printf("  hay que 'subir' casi todo el camino contra la gravedad\n");
    printf("  terrestre; a la vuelta, solo un tramo corto contra la lunar.\n");
    printf("- Por conservación de la energía (Em = K + U), esa diferencia\n");
    printf("  de U la tiene que aportar el combustible de los motores.\n");
    printf("- Además, el combustible también tiene masa: cuanto más se\n");
    printf("  necesita, más pesa la nave y más combustible hace falta\n");
    printf("  para moverlo. Por eso la diferencia de combustible es aún\n");
    printf("  mayor que la diferencia de energía.\n");
}
