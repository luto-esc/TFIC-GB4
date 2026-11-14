# TFIC-GB4 - Simulador de Misiones Artemis (Lenguaje C)

**Comisión:** K1.2

## Integrantes
- Casabuena Milagros Sofía
- Escalante Lucio
<<<<<<< HEAD
- Puyol Agustín
=======
- Puyol Ignacio Agustín
>>>>>>> origin/main
- De Maio Gastón
- Ancarani Francisco Santiago

## Escenario asignado
**Situación-Problema 3:** Inyección Translunar (TLI) e Inercia en Trayectoria Libre (1.ª Ley de Newton y Energía)
Estando en órbita baja (LEO), la etapa superior ICPS ejecuta la maniobra de Inyección Translunar (TLI), impulsando a la nave Orion hasta una velocidad de inyección v_TLI = 10.900,0 m/s. Inmediatamente después del encendido, la etapa ICPS se desacopla y los motores principales se apagan por completo. La nave Orion (m = 26.000,0 kg) entra en una trayectoria de retorno libre hacia la Luna, ubicada a una distancia media Tierra-Luna de D = 384.000.000,0 m.

### Descripción del programa
El programa permite cargar los parámetros de la misión (masa, velocidad, distancia Tierra-Luna y altura orbital) y responder las cuatro preguntas de análisis del escenario. Todos los cálculos se hacen con los valores cargados, así que al cambiar un parámetro se pueden comparar distintos escenarios.

## Funcionamiento

### Módulos
| Archivo | Responsabilidad |
|---|---|
| `main.c` | Función `main()`, valores iniciales de la misión y menú principal. |
| `artemis.h` | Constantes de la misión y físicas (`#define`), estructura `Mision` y prototipos. |
| `artemis.c` | Menú de configuración, preguntas de análisis y cálculos físicos. |
| `simulador.c/.h` | Reportes: historial de simulaciones en una lista enlazada, con guardado y carga desde archivo. |
| `validaciones.c/.h` | Ingreso seguro de datos y utilidades de pantalla. |

### Reglas del juego
- Es un simulador por consola: no hay ganar ni perder, el objetivo es analizar la misión.
- El usuario puede modificar los parámetros de la misión, cada uno dentro de un rango válido.
- Todos los cálculos usan los valores cargados, así que se pueden comparar distintas configuraciones.
- Cada simulación puede guardarse como reporte, y los reportes se guardan en un archivo y se vuelven a cargar.
- Cualquier entrada inválida se rechaza y se vuelve a preguntar.

### Menú principal
1. **Configurar misión:** modifica masa, velocidad inicial, distancia Tierra-Luna y altura orbital.
2. **Preguntas para análisis:** submenú con los puntos a, b, c y d del escenario.
3. **Guardar/Cargar reporte:** genera, muestra, guarda y carga reportes.
0. **Salir:** pide confirmación y libera la memoria antes de cerrar.

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
- **Tareas:** explicación de `fgets`, `strtol`, `strtod`, `strchr` y punteros; esqueleto de las tres funciones; apoyo con la instalación del entorno (VS Code, gcc), Git/GitHub, esqueleto de Makefile y errores del compilador.
- **Cómo se validó y adaptó:** Claude propuso el esqueleto y la versión corregida de las funciones; yo escribí y corregí los chequeos, las compilé, y probé cada una con entradas erróneas (letras, `12abc`, fuera de rango, `nan`, solo Enter).

**Escalante Lucio: Claude**
- **Uso de IA:** asistencia con manejo de archivos de texto (`fopen`, `fprintf`, `fgets`, `sscanf`).
- **Adaptación y Validación:** Lo compilé y probé en Linux generando reportes con distintas configuraciones, guardándolos en `reportes.txt` y volviéndolos a cargar. Testeos del codigo exitosos.

**De Maio Gastón: Claude**
- **Uso de IA:** Asistencia en las funciones de cálculo energético del punto D, detección de errores y verificación en la coherencia del resultado.
- **Adaptación y Validación:** El código sugerido por la IA no compilaba al comienzo, faltaban las funciones de cálculo. Había nombres de variables mal escritos. Lo fuimos corrigiendo con la IA y después probamos desde el menú, con los datos del enunciado, comprobando que la relación ida/vuelta daba cerca de 23 veces. Verificamos que el punto de equilibrio y la energía de ida coincidían con los del punto c, para que el programa no diera valores distintos.
  
**De Puyol Ignacio Agustin: ChatGPT**
- **Uso de IA:** asistencia en la implementación de las preguntas A y B.
- Indiqué cómo debía resolverse cada punto aplicando conocimientos básicos de física, y la IA generó el código a partir de esa lógica. Luego integré las funciones de validación de entrada desarrolladas por mi compañera (leer_entero, leer_flotante) en los datos solicitados, agregué las llamadas al menú y al main, y modifiqué detalles del código, como la redacción de las respuestas de la pregunta A.
