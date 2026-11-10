#ifndef VALIDACIONES_H
#define VALIDACIONES_H

void limpiarPantalla(void);
void pausar(void);

int leer_entero(const char *mensaje, int minimo, int maximo);
double leer_flotante(const char *mensaje, double minimo, double maximo);
char leer_caracter(const char *mensaje, const char *validos);

#endif
