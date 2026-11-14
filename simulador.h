#ifndef SIMULADOR_H
#define SIMULADOR_H

/*
 * simulador.h
 * -----------
 * Este header (.h) es el "índice" del módulo de reportes: dice QUÉ existe
 * (la estructura y los nombres de las funciones), pero no tiene el código.
 * El código de cada función está en simulador.c.
 *
 * Los tres renglones de arriba/abajo (ifndef, define, endif) evitan que
 * el compilador lea este archivo dos veces si varios archivos lo incluyen.
 */

#include <time.h>      /* de acá sale time_t, el tipo para guardar fecha y hora */
#include "artemis.h"   /* de acá sale la estructura Mision (masa, velocidad, etc.) */

/* Nombre del archivo de texto donde se guardan los reportes. */
#define ARCHIVO_REPORTES "reportes.txt"

/*
 * Simulacion: un "nodo" de la lista. Cada nodo es UNA simulación hecha.
 *
 *   id               -> número de reporte (1, 2, 3...)
 *   parametros       -> copia de la Mision con la que se simuló
 *                       (masa, velocidad, distancia, altura). Se guarda una
 *                       COPIA para que, si el usuario cambia la configuración
 *                       después, este reporte siga mostrando lo que se usó.
 *   energiaCinetica  -> resultado (J)
 *   trabajoExterno   -> resultado (J/kg)
 *   fecha            -> fecha y hora en que se hizo la simulación
 *   prox             -> "flecha" al siguiente nodo.
 *                       Es un puntero: guarda DÓNDE está el siguiente nodo.
 *                       En el último nodo vale NULL.
 */
typedef struct Simulacion
{
    int id;
    Mision parametros;
    double energiaCinetica;
    double trabajoExterno;
    time_t fecha;
    struct Simulacion *prox;
} Simulacion;

/*
 * grabSim: graba un reporte NUEVO al final de la lista (llama a agrCola,
 * que es interna de simulador.c).
 * Parametros:
 *   prim    - el primer nodo de la lista (NULL si todavía no hay ninguno)
 *   mision  - los parámetros usados en la simulación
 *   energia - energía cinética calculada
 *   trabajo - trabajo externo calculado
 * Retorna: el primer nodo de la lista (hay que guardarlo: historial = grabSim(...))
 * Nota: el id y la fecha/hora se completan solos.
 */
Simulacion *grabSim(Simulacion *prim, Mision mision,
                    double energia, double trabajo);

/*
 * mostrar_reportes: imprime en pantalla todos los reportes, del primero
 * al último. No modifica la lista.
 */
void mostrar_reportes(const Simulacion *prim);

/*
 * guardar_reportes: escribe todos los reportes en un archivo de texto,
 * una línea por reporte, en el orden en que se hicieron.
 * Si la lista está vacía avisa y no crea el archivo.
 */
void guardar_reportes(const Simulacion *prim, const char *nombreArchivo);

/*
 * cargar_reportes: lee el archivo de texto y arma la lista con su contenido.
 * REEMPLAZA la lista actual (la libera primero).
 * Retorna: el nuevo primer nodo de la lista.
 */
Simulacion *cargar_reportes(Simulacion *prim, const char *nombreArchivo);

/*
 * disponer_reportes: devuelve al sistema la memoria de todos los nodos.
 * Hay que llamarla antes de cerrar el programa.
 * Retorna: NULL (la lista queda vacía).
 */
Simulacion *disponer_reportes(Simulacion *prim);

/*
 * menu_reportes: submenú de la opción 3 del menú principal
 * (generar, ver, guardar y cargar reportes).
 * Parametros:
 *   prim   - el primer nodo de la lista de reportes
 *   mision - la misión configurada actualmente (de acá se toman los datos
 *            cuando se genera un reporte nuevo)
 * Retorna: el primer nodo de la lista (puede cambiar si se generó un
 *          reporte o se cargó un archivo).
 */
Simulacion *menu_reportes(Simulacion *prim, const Mision *mision);

#endif
