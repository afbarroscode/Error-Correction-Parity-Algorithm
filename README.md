# Error-Correction-Parity-Algorithm

## Descripción

Este repositorio contiene una implementación del algoritmo de corrección de errores **BBBSS** (Bennett, Brassard, Breidbart, and Wiesner Subset Sum) en el contexto de **Distribución Cuántica de Claves** (QKD, por sus siglas en inglés). El código está escrito en **C++** y proporciona herramientas para la corrección de errores en protocolos cuánticos como **BB84**, donde los errores de transmisión pueden ocurrir debido a la interferencia y otros fenómenos físicos.

### Algoritmos Implementados

- **Algoritmo BBBSS**: Una técnica de corrección de errores que se utiliza para minimizar la cantidad de errores en los datos compartidos entre dos partes en un protocolo QKD.
- **Funciones de Permutación y Gestión**: Funciones auxiliares que optimizan el proceso de corrección y manejo de los datos recibidos.
- **Funciones Gráficas**: Generación de gráficos para representar los resultados de las simulaciones.
- **Funciones de Inicialización** : Alimenta al protocolo BBBSS con datos iniciales, como secuencia de bits de Alice y Bob, nivel de QBER, funciones de permutación.

## Estructura del Proyecto

- **`src/`**: Contiene todos los archivos fuente en C++ que implementan las funciones de corrección de errores y gráficos.
- **`bin/`**: El ejecutable generado tras la compilación se guarda en este directorio.
- **`figures/`**: Directorio donde se almacenan los datos de las gráficas generados por el programa.

### Archivos Principales

- `bbbss_main.cpp`: Punto de entrada principal del programa.
- `initialization.cpp`: Funciones para la inicialización de los parámetros de QKD y los datos.
- `algorithms.cpp`: Implementación de los algoritmos de corrección de errores.
- 'graficas_python.py' : Generación de gráficas.

## Requisitos

- **C++11** o superior
- Compilador GCC o cualquier otro compatible con C++11.
- Librerías para gráficos con python y con C++ (integradas en el proyecto).

## Compilación

Para compilar el proyecto y ejecutar BBBSS, puedes utilizar el archivo `Makefile` incluido. Solo necesitas ejecutar el siguiente comando en la terminal dentro del directorio del proyecto:

```bash
git clone https://github.com/afbarroscode/Error-Correction-Parity-Algorithm.git
make
./run.sh


