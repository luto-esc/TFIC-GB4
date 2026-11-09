#ifndef ARTEMIS_H
#define ARTEMIS_H

// Constantes de la mision Artemis
#define MASA_ORION 26000.0
#define VELOCIDAD_TLI 10900.0
#define DISTANCIA_LUNA 384000000.0
#define ALTURA_ORBITAL 192000.0

// Estructura para almacenar los parámetros de la misión
typedef struct
{
    double masa;
    double velocidadInicial;
    double distanciaTierraLuna;
    double alturaOrbital;
} Mision;
// Prototipos de funciones
double calcularEnergiaCinetica(const Mision *mision);
void configurarMision(Mision *mision);
#endif
