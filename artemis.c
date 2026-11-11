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

// Energía potencial por unidad de masa (J/kg) a una distancia r (m)
// del centro de la Tierra, sobre la línea Tierra-Luna.
// Suma la atracción de la Tierra y la de la Luna:
// u = -G*Mt/r - G*Ml/(D - r)
double potencialGravitatorio(const Mision *mision, double r)
{
    double distanciaALuna;

    distanciaALuna = mision->distanciaTierraLuna - r;
    return -G * MASA_TIERRA / r - G * MASA_LUNA / distanciaALuna;
}

// Distancia (m) desde el centro de la Tierra hasta el punto donde la
// atracción de la Tierra y la de la Luna son iguales.
// Sale de igualar G*Mt/x^2 = G*Ml/(D - x)^2 y despejar x.
double calcularPuntoEquilibrio(const Mision *mision)
{
    return mision->distanciaTierraLuna / (1.0 + sqrt(MASA_LUNA / MASA_TIERRA));
}

// Energía por kg para ir desde la órbita baja terrestre
// hasta el punto de equilibrio (J/kg).
double energiaIda(const Mision *mision)
{
    double rInicio;
    double rEquilibrio;

    rInicio = RADIO_TIERRA + mision->alturaOrbital;
    rEquilibrio = calcularPuntoEquilibrio(mision);
    return potencialGravitatorio(mision, rEquilibrio)
           - potencialGravitatorio(mision, rInicio);
}

// Energía por kg para ir desde la superficie de la Luna
// hasta el punto de equilibrio (J/kg).
double energiaVuelta(const Mision *mision)
{
    double rInicio;
    double rEquilibrio;

    rInicio = mision->distanciaTierraLuna - RADIO_LUNA;
    rEquilibrio = calcularPuntoEquilibrio(mision);
    return potencialGravitatorio(mision, rEquilibrio)
           - potencialGravitatorio(mision, rInicio);
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
                analizarComparacionEnergetica(mision);
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
    double rInicio;       // distancia inicial al centro de la Tierra (m)
    double rEquilibrio;   // punto de equilibrio, desde el centro de la Tierra (m)
    double uInicio;       // energía potencial por kg en la órbita (J/kg)
    double uEquilibrio;   // energía potencial por kg en el equilibrio (J/kg)
    double deltaU;        // energía potencial que hay que ganar (J/kg)
    double kInicial;      // energía cinética por kg tras la TLI (J/kg)
    double trabajo;       // trabajo adicional por kg (J/kg)
    double vLlegada;      // velocidad al llegar al equilibrio (m/s)

    rInicio = RADIO_TIERRA + mision->alturaOrbital;
    rEquilibrio = calcularPuntoEquilibrio(mision);
    uInicio = potencialGravitatorio(mision, rInicio);
    uEquilibrio = potencialGravitatorio(mision, rEquilibrio);
    deltaU = energiaIda(mision);
    kInicial = 0.5 * mision->velocidadInicial * mision->velocidadInicial;

    printf("=== TRABAJO EXTERNO MÍNIMO HASTA EL PUNTO DE EQUILIBRIO ===\n\n");
    printf("Conservación de la energía mecánica (por unidad de masa):\n");
    printf("  k_i + u_i + W_ext/m = k_f + u_f\n");
    printf("El trabajo es mínimo cuando la nave llega con v = 0 (k_f = 0).\n\n");

    printf("Datos:\n");
    printf("  Órbita inicial:      %.0f km del centro de la Tierra\n", rInicio / 1000.0);
    printf("  Punto de equilibrio: %.0f km del centro de la Tierra\n\n", rEquilibrio / 1000.0);

    printf("Energía potencial por kg (u = -G*Mt/r - G*Ml/(D - r)):\n");
    printf("  En la órbita:      %.4e J/kg\n", uInicio);
    printf("  En el equilibrio:  %.4e J/kg\n", uEquilibrio);
    printf("  Diferencia (du):   %.4e J/kg\n\n", deltaU);

    printf("1) Partiendo del reposo en la órbita (k_i = 0):\n");
    printf("   W_ext/m = du = %.4e J/kg\n\n", deltaU);

    printf("2) Con la energía cinética de la TLI (v = %.2f m/s):\n", mision->velocidadInicial);
    printf("   k_i = v^2 / 2 = %.4e J/kg\n", kInicial);

    trabajo = deltaU - kInicial;

    if (trabajo > 0)
    {
        printf("   W_ext/m = du - k_i = %.4e J/kg\n", trabajo);
        printf("   La TLI no alcanza: faltan %.4e J por kg para llegar.\n", trabajo);
        printf("   Para toda la nave: %.4e J\n", trabajo * mision->masa);
    }
    else
    {
        vLlegada = sqrt(2.0 * (kInicial - deltaU));
        printf("   W_ext/m = 0 J/kg: no hace falta trabajo adicional.\n");
        printf("   La energía de la TLI alcanza y la nave llega al\n");
        printf("   equilibrio con %.2f m/s; desde ahí la Luna la atrae.\n", vLlegada);
    }
}

//d) Comparación energética entre alunizaje y aterrizaje
void analizarComparacionEnergetica(const Mision *mision)
{
    double rEquilibrio;  //punto de equilibrio, desde el centro de la Tierra (m)
    double ida;         //enegía por kg Tierra -> equilibio (J/kg)
    double vuelta;      //energía por kg Luna -> equilibio (J/kg)

    rEquilibrio = calcularPuntoEquilibrio(mision);
    ida = energiaIda(mision);
    vuelta = energiaVuelta(mision);

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
