#include "header.h"

// Función para realizar una permutación aleatoria sobre dos cadenas de bits
std::vector<int> permutacionAleatoria(std::string &cadena1, std::string &cadena2) {
    // Asegurarse de que ambas cadenas tengan la misma longitud
    if (cadena1.length() != cadena2.length()) {
        throw std::invalid_argument("Las cadenas deben tener la misma longitud.");
    }

    int longitud = cadena1.length();
    std::vector<int> posiciones(longitud);

    // Inicializar las posiciones
    for (int i = 0; i < longitud; ++i) {
        posiciones[i] = i;
    }

    // Obtener una semilla aleatoria basada en el tiempo
    std::random_device rd;
    std::default_random_engine rng(rd());

    // Barajar las posiciones utilizando std::shuffle
    std::shuffle(posiciones.begin(), posiciones.end(), rng);

    // Aplicar la permutación a ambas cadenas
    std::string cadena1Permutada = cadena1;
    std::string cadena2Permutada = cadena2;
    for (int i = 0; i < longitud; ++i) {
        char temp = cadena1[posiciones[i]];
        cadena1Permutada[i] = cadena1[posiciones[i]];
        cadena2Permutada[i] = cadena2[posiciones[i]];
    }

    // Actualizar las cadenas originales con las permutadas
    cadena1 = cadena1Permutada;
    cadena2 = cadena2Permutada;

    // Retornar las posiciones de la permutación
    return posiciones;
}

// Función para realizar una permutación aleatoria sobre dos cadenas de bits
std::vector<int> generarpermutacionAleatoria(std::string &cadena1, std::string &cadena2) {
    // Asegurarse de que ambas cadenas tengan la misma longitud
    if (cadena1.length() != cadena2.length()) {
        throw std::invalid_argument("Las cadenas deben tener la misma longitud.");
    }

    int longitud = cadena1.length();
    std::vector<int> posiciones(longitud);

    // Inicializar las posiciones
    for (int i = 0; i < longitud; ++i) {
        posiciones[i] = i;
    }

    // Obtener una semilla aleatoria basada en el tiempo
    std::random_device rd;
    std::default_random_engine rng(rd());

    // Barajar las posiciones utilizando std::shuffle
    std::shuffle(posiciones.begin(), posiciones.end(), rng);
    
    // Retornar las posiciones de la permutación
    return posiciones;
}

void deshacerPermutacion(std::string &cadena, const std::vector<int> &reglaPermutacion) {
    // Asegurarse de que la longitud de la cadena y la regla de permutación coincidan
    if (cadena.length() != reglaPermutacion.size()) {
        throw std::invalid_argument("La longitud de la cadena y la regla de permutación deben coincidir.");
    }

    std::string cadenaPermutada(cadena.length(), ' ');

    // Aplicar la permutación inversa
    for (size_t i = 0; i < reglaPermutacion.size(); ++i) {
        cadenaPermutada[reglaPermutacion[i]] = cadena[i];
    }

    // Copiar la cadena permutada de vuelta a la cadena original
    cadena = cadenaPermutada;
}

void aplicarPermutacion(std::string &cadena, const std::vector<int> &reglaPermutacion) {
    // Asegurarse de que la longitud de la cadena y la regla de permutación coincidan
    if (cadena.length() != reglaPermutacion.size()) {
        throw std::invalid_argument("La longitud de la cadena y la regla de permutación deben coincidir.");
    }

    std::string cadenaPermutada(cadena.length(), ' ');

    // Aplicar la permutación directa
    for (size_t i = 0; i < reglaPermutacion.size(); ++i) {
        cadenaPermutada[i] = cadena[reglaPermutacion[i]];
    }

    // Copiar la cadena permutada de vuelta a la cadena original
    cadena = cadenaPermutada;
}