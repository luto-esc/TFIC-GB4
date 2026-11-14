#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulador.h"
#include "validaciones.h"

/*
 * ============================================================
 *  MINI GUÍA DE PUNTEROS (lo mínimo para entender este archivo)
 * ============================================================
 *
 * Una variable normal guarda un valor:        int x = 5;
 * Un PUNTERO guarda DÓNDE está (la dirección en memoria) otra variable.
 *
 *   Simulacion *q;     "q es un puntero a un nodo Simulacion"
 *   NULL               "no apunta a nada" (es tu nil del pseudocódigo)
 *   q->id              "ir al nodo al que apunta q y leer su campo id"
 *                      (es como q.id, pero cuando q es un puntero)
 *   q->prox            "el siguiente nodo" (tu q.prox)
 *   &x                 "la dirección de x" (se usa en sscanf y localtime)
 *
 * La lista enlazada es una cadena de nodos:
 *
 *   prim --> [nodo 1] --> [nodo 2] --> [nodo 3] --> NULL
 *
 * Para recorrerla se usa un puntero que va saltando de nodo en nodo:
 *   q = q->prox;   hasta llegar a NULL.
 *
 * malloc  = pedir memoria para un nodo nuevo.
 * free    = devolver esa memoria cuando ya no se usa.
 *
 * PUNTEROS QUE USAMOS EN ESTE ARCHIVO (los mismos nombres de tu pseudocódigo):
 *   prim -> apunta al primer nodo de la lista
 *   q    -> puntero que recorre la lista
 *   p    -> puntero al nodo NUEVO que se está creando
 *   ant  -> puntero al nodo ANTERIOR a q (va un paso atrás de q)
 *   ult  -> puntero al ÚLTIMO nodo de la lista
 *   aux  -> puntero auxiliar para guardar un dato un momento
 * ============================================================
 */


/* ============================================================
 *  FUNCIONES INTERNAS (static = solo se usan dentro de este .c,
 *  por eso no están en simulador.h)
 * ============================================================ */

/*
 * agrCola: crea un nodo nuevo con una copia de "datos" y lo
 * enlaza al final de la lista ("carga encolada").
 */
static Simulacion *agrCola(Simulacion *prim, Simulacion datos)
{
    Simulacion *p;      /* el nodo nuevo */
    Simulacion *q;      /* recorre la lista */
    Simulacion *ant;    /* va un nodo atrás de q */

    /*Pedir memoria para UN nodo. sizeof(Simulacion) es el tamaño de un nodo. */
    p = (Simulacion *)malloc(sizeof(Simulacion));
    if (p == NULL)
    {
        /* malloc devuelve NULL si no hay memoria disponible */
        printf("Error: no hay memoria para guardar el reporte.\n");
        return prim;
    }

    /*Copiar todos los datos dentro del nodo nuevo. */
    *p = datos;
    p->prox = NULL;

    /*Si la lista estaba vacía, el nodo nuevo pasa a ser el primero. */
    if (prim == NULL)
    {
        return p;
    }

    /*Si no estaba vacía, recorrerla hasta pasarse del último.
          q avanza al siguiente nodo y ant se queda un paso atrás;
          cuando q llega a NULL, ant es el último nodo. */
    q = prim;
    ant = NULL;
    while (q != NULL)
    {
        ant = q;
        q = q->prox;     /* saltar al siguiente nodo */
    }

    /*Enlazar: el que era último ahora apunta al nuevo. */
    ant->prox = p;

    return prim;        /* el primero no cambió */
}


/* ============================================================
 *  REGISTRAR
 * ============================================================ */

Simulacion *grabSim(Simulacion *prim, Mision mision,
                    double energia, double trabajo)
{
    Simulacion datos;   /* acá armamos el reporte antes de meterlo en la lista */
    Simulacion *ult;    /* el último nodo de la lista */

    /* El id es 1 si es el primer reporte; si no, el del último + 1. */
    datos.id = 1;
    if (prim != NULL)
    {
        ult = prim;
        while (ult->prox != NULL)
        {
            ult = ult->prox;
        }
        datos.id = ult->id + 1;
    }

    datos.parametros = mision;          /* copia de masa, velocidad, distancia, altura */
    datos.energiaCinetica = energia;
    datos.trabajoExterno = trabajo;
    datos.fecha = time(NULL);           /* time(NULL) = fecha y hora actuales */
    datos.prox = NULL;

    return agrCola(prim, datos);
}


/* ============================================================
 *  MOSTRAR
 * ============================================================ */

void mostrar_reportes(const Simulacion *prim)
{
    const Simulacion *q;        /* puntero para recorrer */
    char fechaTexto[32];        /* acá se guarda la fecha ya convertida a texto */

    if (prim == NULL)
    {
        printf("No hay reportes para mostrar.\n");
        return;
    }

    printf("================================\n");
    printf("        REPORTES\n");
    printf("================================\n");

    q = prim;
    while (q != NULL)
    {
        /* Convertir la fecha (un número de segundos) a texto legible.
           localtime la pasa a hora local y strftime le da formato.
           Se usa &q->fecha porque localtime pide la DIRECCIÓN de la fecha. */
        strftime(fechaTexto, sizeof(fechaTexto), "%d/%m/%Y %H:%M:%S",
                 localtime(&q->fecha));

        printf("\nReporte N° %d  (%s)\n", q->id, fechaTexto);
        printf("  Masa:               %.2f kg\n", q->parametros.masa);
        printf("  Velocidad inicial:  %.2f m/s\n", q->parametros.velocidadInicial);
        printf("  Dist. Tierra-Luna:  %.2f m\n", q->parametros.distanciaTierraLuna);
        printf("  Altura orbital:     %.2f m\n", q->parametros.alturaOrbital);
        printf("  Energía cinética:   %.4e J\n", q->energiaCinetica);
        printf("  Trabajo externo:    %.4e J/kg\n", q->trabajoExterno);

        q = q->prox;     /* IMPORTANTE: pasar al próximo, si no el while no termina */
    }
}


/* ============================================================
 *  GUARDAR EN ARCHIVO
 * ============================================================ */

/*
 * Formato del archivo (texto plano, una línea por reporte, campos separados
 * por punto y coma):
 *
 *   id;masa;velocidad;distancia;altura;energia;trabajo;fecha
 *
 * Ejemplo:
 *   1;26000;10900;384000000;192000;1.5445e+12;5.85e+07;1731321600
 *
 * La fecha se guarda como número (segundos desde 1970), que es como C la
 * maneja internamente. Al mostrarla se convierte a texto.
 */
void guardar_reportes(const Simulacion *prim, const char *nombreArchivo)
{
    FILE *archivo;              /* "FILE *" es el puntero que C usa para manejar un archivo */
    const Simulacion *q;
    int cantidad = 0;

    /* si no hay nada, avisar y salir. */
    if (prim == NULL)
    {
        printf("No hay reportes que guardar.\n");
        return;
    }

    /* fopen abre el archivo. "w" = escribir (si existe, lo pisa; si no, lo crea).
       Si algo falla (disco lleno, sin permisos...) devuelve NULL. */
    archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL)
    {
        printf("Error: no se pudo abrir '%s' para guardar.\n", nombreArchivo);
        return;
    }

    /* Recorrer la lista de primero a último y escribir una línea por nodo. */
    q = prim;
    while (q != NULL)
    {
        /* fprintf es como printf, pero escribe en el archivo en vez de la pantalla.
           %d entero, %.15g número decimal, %ld entero largo (la fecha). */
        fprintf(archivo, "%d;%.15g;%.15g;%.15g;%.15g;%.15g;%.15g;%ld\n",
                q->id,
                q->parametros.masa,
                q->parametros.velocidadInicial,
                q->parametros.distanciaTierraLuna,
                q->parametros.alturaOrbital,
                q->energiaCinetica,
                q->trabajoExterno,
                (long)q->fecha);

        cantidad++;
        q = q->prox;
    }

    fclose(archivo);            /* SIEMPRE cerrar el archivo al terminar */
    printf("Se guardaron %d reporte(s) en '%s'.\n", cantidad, nombreArchivo);
}


/* ============================================================
 *  CARGAR DESDE ARCHIVO
 * ============================================================ */

Simulacion *cargar_reportes(Simulacion *prim, const char *nombreArchivo)
{
    FILE *archivo;
    char linea[256];            /* acá se guarda cada línea leída del archivo */
    Simulacion datos;
    long fecha;
    int leidos;
    int cargados = 0;
    int salteadas = 0;

    /* "r" = leer. Si el archivo no existe, fopen devuelve NULL. */
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        printf("No se encontró el archivo '%s'. No se cargó nada.\n", nombreArchivo);
        return prim;            /* la lista actual queda como estaba */
    }

    /* Se vacía la lista actual para no duplicar reportes. */
    prim = disponer_reportes(prim);

    /* fgets lee UNA línea del archivo. Devuelve NULL cuando se acaba el archivo. */
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        /* sscanf "desarma" la línea según el formato y mete cada valor en una
           variable. Por eso cada variable lleva & adelante (la dirección donde
           sscanf tiene que dejar el valor). %lf es para double.
           Devuelve cuántos valores pudo leer. */
        leidos = sscanf(linea, "%d;%lf;%lf;%lf;%lf;%lf;%lf;%ld",
                        &datos.id,
                        &datos.parametros.masa,
                        &datos.parametros.velocidadInicial,
                        &datos.parametros.distanciaTierraLuna,
                        &datos.parametros.alturaOrbital,
                        &datos.energiaCinetica,
                        &datos.trabajoExterno,
                        &fecha);

        if (leidos == 8)        /* la línea tenía los 8 datos: es válida */
        {
            datos.fecha = (time_t)fecha;
            datos.prox = NULL;
            prim = agrCola(prim, datos);
            cargados++;
        }
        else                    /* línea dañada o vacía: se ignora */
        {
            salteadas++;
        }
    }

    fclose(archivo);

    printf("Se cargaron %d reporte(s) desde '%s'.\n", cargados, nombreArchivo);
    if (salteadas > 0)
    {
        printf("Se ignoraron %d línea(s) con formato incorrecto.\n", salteadas);
    }
    return prim;
}


/* ============================================================
 *  LIBERAR MEMORIA
 * ============================================================ */

Simulacion *disponer_reportes(Simulacion *prim)
{
    Simulacion *q = prim;
    Simulacion *aux;

    while (q != NULL)
    {
        /* Primero anotar en aux cuál es el próximo, porque después de
           free(q) ya no se puede leer q->prox (el nodo dejó de existir). */
        aux = q->prox;
        free(q);
        q = aux;
    }

    return NULL;                /* lista vacía */
}


/* ============================================================
 *  SUBMENÚ (opción 3 del menú principal)
 * ============================================================ */

Simulacion *menu_reportes(Simulacion *prim, const Mision *mision)
{
    int opcion;
    char confirmar;
    double energia;             /* energía cinética calculada (J) */
    double trabajo;             /* trabajo externo mínimo por kg (J/kg) */

    do
    {
        printf("================================\n");
        printf("   REPORTES\n");
        printf("================================\n");
        printf("1) Generar reporte con la configuración actual\n");
        printf("2) Ver reportes\n");
        printf("3) Guardar reportes en archivo\n");
        printf("4) Cargar reportes desde archivo\n");
        printf("0) Volver al menú principal\n");

        opcion = leer_entero("Ingrese una opcion: ", 0, 4);
        limpiarPantalla();

        switch (opcion)
        {
        case 1:
            /* "mision" es un PUNTERO a la misión que se está usando.
               mision->masa lee un campo; *mision es la misión completa
               (se usa para guardar una COPIA en el reporte). */
            energia = calcularEnergiaCinetica(mision);

            /* Mismo cálculo que analizarTrabajoEquilibrio (opción 2 > 3):
               trabajo = (energía por kg para llegar al equilibrio)
                         - (energía cinética por kg de la TLI).
               Si da negativo, la TLI alcanza y no hace falta trabajo extra. */
            trabajo = energiaIda(mision)
                      - 0.5 * mision->velocidadInicial * mision->velocidadInicial;
            if (trabajo < 0.0)
            {
                trabajo = 0.0;
            }

            prim = grabSim(prim, *mision, energia, trabajo);
            printf("Reporte generado con la configuración actual.\n");
            pausar();
            break;
        case 2:
            mostrar_reportes(prim);
            pausar();
            break;
        case 3:
            guardar_reportes(prim, ARCHIVO_REPORTES);
            pausar();
            break;
        case 4:
            /* Cargar reemplaza lo que hay en memoria: si hay algo, preguntar. */
            if (prim != NULL)
            {
                confirmar = leer_caracter("Esto reemplaza los reportes actuales. ¿Continuar? (y/n): ", "yYnN");
                if (confirmar == 'n' || confirmar == 'N')
                {
                    limpiarPantalla();
                    break;
                }
            }
            prim = cargar_reportes(prim, ARCHIVO_REPORTES);
            pausar();
            break;
        }
    } while (opcion != 0);

    return prim;
}
