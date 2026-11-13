# TFIC-GB4 - Simulador de Misiones Artemis (Lenguaje C)

**Comisión:** K1.2

## Integrantes
- Casabuena Milagros Sofía
- (completar)
- (completar)
- (completar)
- (completar)

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

## Compilación y ejecución
(completar)

## Registro de uso de IA
**Casabuena Milagros: Claude**
- **Tareas:** explicación de `fgets`, `strtol`, `strtod`, `strchr` y punteros; esqueleto de las tres funciones; apoyo con la instalación del entorno (VS Code, gcc), Git/GitHub y errores del compilador.
- **Cómo se validó y adaptó:** Claude propuso el esqueleto y la versión corregida de las funciones; yo escribí y corregí los chequeos, las compilé, y probé cada una con entradas erróneas (letras, `12abc`, fuera de rango, `nan`, solo Enter).