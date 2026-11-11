Trabajo Práctico Integrador Final - Lenguaje C

Simulador de Misiones Artemis (Situación-Problema 3)

Universidad Tecnológica Nacional (UTN) - Facultad Regional Resistencia

Cátedra: Algoritmos y Estructuras de Datos | Ingeniería en Sistemas de Información

INTEGRANTES Y COMISIÓN

FALTA ACTUALIZAR: NOMBRES COMPLETOS Y COMISIÓN DE CADA INTEGRANTEEEEEE 

Nom y Ape 1 - legajo

Nom y Ape  2 - legajo

Nom y Ape  3 - legajo

Nom y Ape  4 - legajo

Francisco Ancarani - 28845 / FranciscoAncarani

DESCRIPCIÓN DEL ESCENARIO ASIGNADO

Situación - Problema 3: Inyección Translunar - TLI e Inercia en Trayectoria Libre (1.ª Ley de Newton y Energía)

Estando en órbita baja (LEO), la etapa superior ICPS ejecuta la maniobra de Inyección Translunar (TLI), impulsando a la nave Orion hasta una velocidad de escape/inyección v_TLI = 10.900,0 m/s. Inmediatamente después del encendido, la etapa ICPS se desacopla y los motores principales se apagan por completo. La nave Orion (m = 26.000,0 kg) entra en una trayectoria de retorno libre (Free Return Trajectory) hacia la Luna, ubicada a una distancia media Tierra-Luna de D = 384.000.000,0 m.

REQUISITOS TÉCNICOS Y ARQUITECTURA DEL CÓDIGO

El proyecto está modularizado en archivos .c y .h respetando las buenas prácticas de programación estructurada:

main.c: Contiene la función main(), la inicialización de parámetros por defecto de la misión y el flujo del menú principal interactivo.

artemis.h / artemis.c: Contiene la declaración de constantes de la misión/físicas, la estructura Mision, el menú de configuración de parámetros, las preguntas analíticas de física y el cálculo de la energía cinética inicial.

validaciones.h / validaciones.c: Módulo dedicado al ingreso seguro de datos por consola, evitando cierres inesperados mediante:

int leer_entero(mensaje, mínimo, máximo)

double leer_flotante(mensaje, mínimo, máximo)

char leer_caracter(mensaje, válidos)

*** FALTA COMPLETAR EN EL CÓDIGO Y DETALLAR ACA: ***
*** 1. OPCIONES DE ANÁLISIS DE FÍSICA FALTANTES (1, 3 Y 4 EN artemis.c) ***
*** 2. MÓDULO DE REPORTE Y ARCHIVOS (OPCIÓN 5 EN main.c) ***
*** 3. ARCHIVO DE CABECERA simulador.h ***

INSTRUCCIONES DE COMPILACIÓN Y EJECUCIÓN

Requisitos previos

Compilador GCC instalado (MinGW-w64 / MSYS2 o similar).

Compilación directa con GCC:

gcc main.c artemis.c validaciones.c -o programa.exe

Ejecución:

En Windows (consola CMD / PowerShell):

.\programa.exe

*** FALTA CREACIÓN Y SUBIDA DEL ARCHIVO Makefile ***********************

REGISTRO DE USO DE INTELIGENCIA ARTIFICIAL

De acuerdo con las normativas de la cátedra, se detalla la utilización de herramientas de IA Generativa durante el desarrollo del proyecto:

Herramientas utilizadas: ChatGPT / Claude / Gemini.

Uso realizado:

Ideas de estructura de menú e interfaz para consola.

Asistencia técnica en la implementación del módulo de validaciones para evitar el uso de scanf.

Adaptación y Validación: El código sugerido por la IA fue analizado, adaptado y refactorizado por los integrantes del equipo para alinearse con los requerimientos específicos de la cátedra y el flujo de la aplicación.

VIDEO DE DEMOSTRACIÓN GRUPAL

*** FALTA AGREGAR: ENLACE AL VIDEO GRUPAL (MÁXIMO 5 MINUTOS) EN YOUTUBE/DRIVE ***


Link al Video: 
