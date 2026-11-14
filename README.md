# TFIC-GB4 - Simulador de Misiones Artemis (Lenguaje C)

**Comisión:** K1.2

## Integrantes
- Casabuena Milagros Sofía
- (completar)
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

## Compilación y ejecución
(completar)

## Registro de uso de IA
**Casabuena Milagros: Claude**
- **Tareas:** explicación de `fgets`, `strtol`, `strtod`, `strchr` y punteros; esqueleto de las tres funciones; apoyo con la instalación del entorno (VS Code, gcc), Git/GitHub y errores del compilador.
- **Cómo se validó y adaptó:** Claude propuso el esqueleto y la versión corregida de las funciones; yo escribí y corregí los chequeos, las compilé, y probé cada una con entradas erróneas (letras, `12abc`, fuera de rango, `nan`, solo Enter).

**De Maio Gastón: Claude**
- **Uso de IA:** Asistencia en las funciones de cálculo energético del punto D, detección de errores y verificación en la coherencia del resultado.
- **Adaptación y Validación:** El código sugerido por la IA no compilaba al comienzo, faltaban las funciones de cálculo. Había nombres de variables mal escritos. Lo fuimos corrigiendo con la IA y después probamos desde el menú, con los datos del enunciado, comprobando que la relación ida/vuelta daba cerca de 23 veces. Verificamos que el punto de equilibrio y la energía de ida coincidían con los del punto c, para que el programa no diera valores distintos.

