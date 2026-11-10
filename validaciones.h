#ifndef VALIDACIONES_H
#define VALIDACIONES_H

void limpiarPantalla(void);
void pausar(void);

/*
*leer_entero: pide un entero por consola hasta que sea valido.
Parametros: 
    mensaje - texto que se muestra al usuario
    minimo, maximo - limites permitidos
Retorna: el entero ingresado, ya validado.
Nota: rechaza letras, basura despues del numero y valores fuera de rango.
*/
int leer_entero(const char *mensaje, int minimo, int maximo);

/*leer_flotante: pide un numero decimal por consola hasta que sea valido.
Parametros:
    mensaje - texto que se muestra al usuario
    minimo, maximo - limites permitidos (inclusive)
Retorna: el numero decimal ingresado (double), ya validado.
Nota: los decimales se escriben con punnto (10.5), no con coma. 
    Rechaza letras y valores fuera de rango.*/
double leer_flotante(const char *mensaje, double minimo, double maximo);

/*
leer_caracter: pide un unico caracter por consola hasta que sea valido.
Parametros:
   mensaje - texto que se muestra al usuario
   validos - texto con los caracteres permitidos (ej: "sn")
Retorna: el caracter ingresado, que esta dentro de validos.
Nota: rechaza si se ingresa mas de un caracter, si se aprieta solo
       Enter, o si el caracter no esta en validos.
 */
char leer_caracter(const char *mensaje, const char *validos);

#endif