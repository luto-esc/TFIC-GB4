# TFIC-GB4 - Simulador de Misiones Artemis (Lenguaje C)

**Comisión:** K1.2

## Integrantes
- Casabuena Milagros Sofía
- Escalante Lucio
- (completar)
- De Maio Gastón
- Ancarani Francisco Santiago

## Escenario asignado
**Situación-Problema 3:** Inyección Translunar (TLI) e Inercia en Trayectoria Libre (1.ª Ley de Newton y Energía)

### Descripción y reglas del juego
(completar: lo escribe quien armó la simulación)

## Funcionamiento
(completar: módulos y flujo general del programa)

### Módulo de validaciones (`validaciones.c/.h`)
Tres funciones de ingreso seguro, que reemplazan a `scanf` y vuelven a preguntar si el dato es inválido:
- `leer_entero(mensaje, minimo, maximo)`: rechaza letras, basura después del número y valores fuera de rango.
- `leer_flotante(mensaje, minimo, maximo)`: igual, con decimales (con punto) y rechaza `nan`.
- `leer_caracter(mensaje, validos)`: acepta un solo carácter, y solo uno de los permitidos.

Todas leen la línea completa con `fgets` y la convierten con `strtol`/`strtod`, para evitar bucles infinitos.

### Módulo de reportes (`simulador.c/.h`)
Guarda un historial de las simulaciones realizadas, en una **lista enlazada** en memoria, y permite pasarlo a un archivo de texto y volver a cargarlo.

**Estructura `Simulacion` (un nodo de la lista):** `id`, una copia de los parámetros de la misión (`Mision`), `energiaCinetica`, `trabajoExterno`, `fecha` (fecha y hora de la simulación) y `prox` (puntero al siguiente nodo, `NULL` en el último). Se guarda una copia de la misión para que el reporte no cambie si después se reconfigura.

**Funciones:**
- `grabSim(prim, mision, energia, trabajo)`: agrega un reporte nuevo al final de la lista (carga encolada) con su `id` y fecha. Usa internamente `agrCola`.
- `mostrar_reportes(prim)`: recorre la lista y muestra todos los reportes, del más viejo al más nuevo.
- `guardar_reportes(prim, archivo)`: escribe la lista en `reportes.txt`, una línea por reporte con los campos separados por `;`.
- `cargar_reportes(prim, archivo)`: lee el archivo línea por línea (`fgets` + `sscanf`), ignora las líneas dañadas y reconstruye la lista.
- `disponer_reportes(prim)`: libera la memoria de todos los nodos (se llama al salir del programa).
- `menu_reportes(prim, mision)`: submenú de la opción 3: generar reporte con la configuración actual, ver, guardar y cargar.

**Formato de `reportes.txt`:** `id;masa;velocidad;distancia;altura;energia;trabajo;fecha`

## Compilación y ejecución
Requisito: compilador `gcc` (en Linux: `sudo apt install build-essential`; en Windows: MinGW-w64 / MSYS2).

    gcc -Wall -Wextra main.c artemis.c validaciones.c simulador.c -o programa -lm
    ./programa

También con `make` (usa el `Makefile` del repositorio) y `make clean` para borrar el ejecutable. En Windows el ejecutable es `programa.exe`.

El `-lm` es necesario en Linux porque se usa `sqrt` (librería matemática). El programa funciona en Windows y en Linux.

## Registro de uso de IA
**Casabuena Milagros: Claude**
- **Tareas:** explicación de `fgets`, `strtol`, `strtod`, `strchr` y punteros; esqueleto de las tres funciones; apoyo con la instalación del entorno (VS Code, gcc), Git/GitHub y errores del compilador.
- **Cómo se validó y adaptó:** Claude propuso el esqueleto y la versión corregida de las funciones; yo escribí y corregí los chequeos, las compilé, y probé cada una con entradas erróneas (letras, `12abc`, fuera de rango, `nan`, solo Enter).

**Escalante Lucio: Claude**
- **Uso de IA:** asistencia con manejo de archivos de texto (`fopen`, `fprintf`, `fgets`, `sscanf`);.
- **Adaptación y Validación:** Lo compilé y probé en Linux generando reportes con distintas configuraciones, guardándolos en `reportes.txt` y volviéndolos a cargar. Testeos del codigo exitosos por la el modelo utilizado.

**De Maio Gastón: Claude**
- **Uso de IA:** Asistencia en las funciones de cálculo energético del punto D, detección de errores y verificación en la coherencia del resultado.
- **Adaptación y Validación:** El código sugerido por la IA no compilaba al comienzo, faltaban las funciones de cálculo. Había nombres de variables mal escritos. Lo fuimos corrigiendo con la IA y después probamos desde el menú, con los datos del enunciado, comprobando que la relación ida/vuelta daba cerca de 23 veces. Verificamos que el punto de equilibrio y la energía de ida coincidían con los del punto c, para que el programa no diera valores distintos.
