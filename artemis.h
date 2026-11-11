#ifndef ARTEMIS_H
#define ARTEMIS_H

// Constantes de la mision Artemis
#define MASA_ORION 26000.0
#define VELOCIDAD_TLI 10900.0
#define DISTANCIA_LUNA 384000000.0
#define ALTURA_ORBITAL 192000.0

// Constantes fisicas
#define G 6.674e-11
#define MASA_TIERRA 5.972e24
#define MASA_LUNA 7.342e22
#define RADIO_TIERRA 6378000.0
#define RADIO_LUNA 1737400.0

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
void preguntasAnalisis(const Mision *mision);
void analizarEnergiaCinetica(const Mision *mision);
void analizarTrabajoEquilibrio(const Mision *mision);
void analizarComparacionEnergetica(const Mision *mision);
#endif
