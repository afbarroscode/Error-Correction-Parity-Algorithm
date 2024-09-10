#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <stdarg.h>
#include <utility>
#include <string>
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <set>
#include <tuple>
#include <stdexcept>
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include "/home/alberto/Documentos/bbbss/progressbar/include/progressbar.hpp"


//Funcion para crear una grafica
int hacer_grafica(std::vector<double> x, std::vector<double> y,
                    std::wstring title, std::wstring xlabel, std::wstring ylabel,
                     std::string image_name);

// Función para generar una cadena de bits aleatoria
std::string generarCadenaDeBits(int longitud);

// Función para generar posiciones aleatorias
std::vector<int> generarPosicionesAleatorias(int longitud, float porcentaje);

// Función para realizar la operación XOR en las posiciones generadas
void realizarXOR(std::string &cadena, const std::vector<int> &posiciones);

//Funciones para manejo de vectores
std::vector<std::pair<size_t, std::vector<int>>> findVectorsContainingPositions(
    const std::vector<int>& posicionesDiferentes, 
    const std::vector<std::vector<int>>& permutacionDivididaBack);

std::vector<std::string> getStringsByIndices(const std::vector<std::string>& original, const std::vector<size_t>& indices);

std::vector<std::vector<int>> getVectorsByIndices(
    const std::vector<std::vector<int>>& original, 
    const std::vector<size_t>& indices);

void eliminarDuplicados(std::vector<size_t>& bloquesBacktracking);

//Funciones que implementan tecnica de Backtracking
std::vector<int> backtracking( 
    std::string cadenaAlice, std::string cadenaBob,
    double QBER, int numero_iteracion,
    std::vector<int> permutacionIterAnterior,
    std::vector<int> posicionesDiferentes);

std::string xorBitsAtPositionBacktracking(std::string &binaryString, int position);

void imprimirVector(const std::vector<int>& vec);

// Función para inicializar el proceso
std::tuple<double, double, double, int> inicializacion();

//Funcion para construir vectores de doubles
std::vector<double> construirVector(double inicio, double fin, double paso);

//Funcion para generar las condiciones iniciales de Alice y Bob
std::tuple<std::string, std::string> generacionCondicionesIniciales(double qber, int longitud);

// Función para realizar una permutación aleatoria sobre dos cadenas de bits
std::vector<int> permutacionAleatoria(std::string &cadena1, std::string &cadena2);

std::vector<int> generarpermutacionAleatoria(std::string &cadena1, std::string &cadena2);

void aplicarPermutacion(std::string &cadena, const std::vector<int> &reglaPermutacion);

void deshacerPermutacion(std::string &cadena, const std::vector<int> &reglaPermutacion);

// Función para dividir un vector de enteros en subcadenas de longitud lenk
std::vector<std::vector<int>> dividirVector(const std::vector<int> &posiciones, int lenk);

// Función para calcular la paridad de una cadena
int calcularParidad(const std::string &cadena, bool bitExpuesto);

// Función para obtener el valor actual del contador de paridad
int obtenerContadorParidad();

// Restablecer el contador de paridad
void reiniciarContadorParidad();

// Función para determinar la potencia de dos más cercana
int potenciaDeDosCercana(int valor, bool redondearArriba);

// Función para dividir una cadena de bits en subcadenas de tamaño de una potencia de dos más cercana
std::tuple<std::vector<std::string>, std::vector<int>> dividirCadena(const std::string &cadena, int tamanioSubcadena, bool bitExpuesto);

// Función para obtener la lista de paridades de un vector de subcadenas
std::vector<int> obtenerParidades(const std::vector<std::string> &subcadenas);

// Función para obtener subcadenas con paridades distintas
std::tuple<std::vector<std::string>, std::vector<std::string>, std::vector<std::vector<int>>>
obtenerSubcadenasConParidadesDistintas(const std::vector<std::string> &subcadenasAlice,
                                       const std::vector<int> &paridadesAlice,
                                       const std::vector<std::string> &subcadenasBob,
                                       const std::vector<int> &paridadesBob,
                                       const std::vector<std::vector<int>> &permutacion1Dividida);

// Función para dividir una cadena de vectores de enteros en dos mitades
std::tuple<std::vector<int>, std::vector<int>> dividirCadenaEnDos(const std::vector<int> &cadena);


// Función recursiva para la búsqueda dicotómica de bits diferentes
int buscarBitDiferenteDicotomicoRecursivo(const std::string &subcadenaAlice,
                                          const std::string &subcadenaBob,
                                          const std::vector<int> &posicionBitsBloque);

// Función principal para iterar sobre todas las subcadenas
std::vector<int> buscarBitDiferenteDicotomico(const std::vector<std::string> &subcadenasDistintasAlice,
                                              const std::vector<std::string> &subcadenasDistintasBob,
                                              const std::vector<std::vector<int>> &posicionesBitsSubcadenasDistintas);

int buscarBitDiferenteDicotomicoRecursivoBacktracking(const std::string &subcadenaAlice,
                                          const std::string &subcadenaBob,
                                          const std::vector<int> &posicionBitsBloque);

std::vector<int> buscarBitDiferenteDicotomicoBacktracking(const std::vector<std::string> &subcadenasDistintasAlice,
                                              const std::vector<std::string> &subcadenasDistintasBob,
                                              const std::vector<std::vector<int>> &posicionesBitsSubcadenasDistintas);

std::string xorBitsAtPositions(std::string &binaryString, const std::vector<int> &positions);

std::tuple<std::string, int> iteracion_bbbss(std::string cadenaAlice, std::string cadenaBob, double QBER, int numero_iteracion);

int compararCadenas(const std::string& cadena1, const std::string& cadena2);

void bbbss(double qberMin, double qberMax, double refinement, int longitud);

void cascade(double qberMin, double qberMax, double refinement, int longitud);

//Clase para agregar, obtener, imprimir permutaciones
class Permutacion {
private:
    std::vector<std::vector<int>> permutaciones;

public:
    // Constructor sin parámetros
    Permutacion() {}

    // Método para agregar una nueva permutacion
    void agregarPermutacion(const std::vector<int>& p) {
        permutaciones.push_back(p);
    }

    // Método para obtener todas las permutaciones
    std::vector<std::vector<int>> getPermutaciones() const {
        return permutaciones;
    }

    // Método para obtener una permutacion específica por índice
    std::vector<int> getPermutacionPorIndice(size_t indice) const {
        if (indice >= permutaciones.size()) {
            throw std::out_of_range("Clase Permutacion. Índice fuera de rango");
        }
        return permutaciones[indice];
    }

    // Método para imprimir todas las permutacio nes
    void imprimirPermutaciones() const {
        for (const auto& perm : permutaciones) {
            for (int num : perm) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }
};

// Clase para agregar, buscar e imprimir TLBs
class StringVectorStorage {
private:
    std::vector<std::vector<std::string>> storage;

    // Constructor privado
    StringVectorStorage() {}

public:
    // Método para obtener la instancia única
    static StringVectorStorage& getInstance() {
        static StringVectorStorage instance;
        return instance;
    }

    // Función para almacenar un std::vector<std::string>
    void store(const std::vector<std::string>& vec) {
        storage.push_back(vec);
    }

    // Función para recuperar un std::vector<std::string> por índice
    std::vector<std::string> retrieve(size_t index) const {
        if (index >= storage.size()) {
            throw std::out_of_range("StringVector: Índice fuera de rango");
        }
        return storage[index];
    }

    // Función para imprimir un std::vector<std::string>
    void printVector(const std::vector<std::string>& vec) const {
        for (const auto& str : vec) {
            std::cout << str << " ";
        }
        std::cout << std::endl;
    }

    // Función para imprimir todos los vectores almacenados
    void printAllVectors() const {
        for (const auto& vec : storage) {
            printVector(vec);
        }
    }

    // Método para reinicializar la instancia
    void reset() {
        storage.clear();
    }

    // Método para eliminar múltiples objetos según los índices
    void remove(size_t index) {
        if (index >= storage.size()) {
            throw std::out_of_range("StringVectorStorage: Índice fuera de rango");
        }
        storage.erase(storage.begin() + index);
    }

    // Eliminar las funciones de copia
    StringVectorStorage(const StringVectorStorage&) = delete;
    StringVectorStorage& operator=(const StringVectorStorage&) = delete;
};

// Clase para agregar, buscar e imprimir posiciones de TLBs
class IntVectorStorage {
private:
    std::vector<std::vector<std::vector<int>>> storage;

    // Constructor privado
    IntVectorStorage() {}

public:
    // Método para obtener la instancia única
    static IntVectorStorage& getInstance() {
        static IntVectorStorage instance;
        return instance;
    }

    // Función para almacenar un std::vector<std::vector<int>>
    void store(const std::vector<std::vector<int>>& vec) {
        storage.push_back(vec);
    }

    // Función para recuperar un std::vector<std::vector<int>> por índice
    std::vector<std::vector<int>> retrieve(size_t index) const {
        if (index >= storage.size()) {
            throw std::out_of_range("Int Vector: Índice fuera de rango");
        }
        return storage[index];
    }

    // Función para imprimir un std::vector<std::vector<int>>
    void printVector(const std::vector<std::vector<int>>& vec) const {
        for (const auto& innerVec : vec) {
            for (int num : innerVec) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }

    // Función para imprimir todos los vectores almacenados
    void printAllVectors() const {
        for (const auto& vec : storage) {
            printVector(vec);
        }
    }

    // Método para reinicializar la instancia
    void reset() {
        storage.clear();
    }

    void remove(size_t index) {
        if (index >= storage.size()) {
            throw std::out_of_range("IntVectorStorage: Índice fuera de rango");
        }
        storage.erase(storage.begin() + index);
    }

    // Eliminar las funciones de copia
    IntVectorStorage(const IntVectorStorage&) = delete;
    IntVectorStorage& operator=(const IntVectorStorage&) = delete;
};

// Clase para agregar, buscar e imprimir posiciones de TLBs, pero para std::vector<int>
class IntStorage {
private:
    std::vector<std::vector<int>> storage;

    // Constructor privado
    IntStorage() {}

public:
    // Método para obtener la instancia única
    static IntStorage& getInstance() {
        static IntStorage instance;
        return instance;
    }

    // Función para almacenar un std::vector<int>
    void store(const std::vector<int>& vec) {
        storage.push_back(vec);
    }

    // Función para recuperar un std::vector<int> por índice
    std::vector<int> retrieve(size_t index) const {
        if (index >= storage.size()) {
            throw std::out_of_range("Int Storage: Índice fuera de rango");
        }
        return storage[index];
    }

    // Función para imprimir un std::vector<int>
    void printVector(const std::vector<int>& vec) const {
        for (int num : vec) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    // Función para imprimir todos los vectores almacenados
    void printAllVectors() const {
        for (const auto& vec : storage) {
            printVector(vec);
        }
    }

    // Método para reinicializar la instancia
    void reset() {
        storage.clear();
    }

    void remove(size_t index) {
        if (index >= storage.size()) {
            throw std::out_of_range("IntStorage: Índice fuera de rango");
        }
        storage.erase(storage.begin() + index);
    }

    // Eliminar las funciones de copia
    IntStorage(const IntStorage&) = delete;
    IntStorage& operator=(const IntStorage&) = delete;
};

#endif FUNCIONES_H