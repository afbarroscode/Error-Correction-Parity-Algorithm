#include "header.h"

// Variable estática locales
int contadorParidad = 0;

int calcularParidad(const std::string &cadena, bool bitExpuesto) {
    int conteo = 0;
    // Recorrer la cadena y contar los bits '1'
    for (char bit : cadena) {
        if (bit == '1') {
            ++conteo;
        }
    }
    if(bitExpuesto == true) 
    {
        ++contadorParidad;
    }
    else {;}
    // Retornar la paridad (1 si el conteo es impar, 0 si es par)
    return conteo % 2;
}

// Función para obtener el valor actual del contador de paridad
int obtenerContadorParidad() {
    return contadorParidad;
}

// Restablecer el contador de paridad
void reiniciarContadorParidad() {
    contadorParidad = 0;
}

// Función para obtener subcadenas con paridades distintas
std::tuple<std::vector<std::string>, std::vector<std::string>, std::vector<std::vector<int>>> obtenerSubcadenasConParidadesDistintas(    
    const std::vector<std::string> &subcadenasAlice,
    const std::vector<int> &paridadesAlice,
    const std::vector<std::string> &subcadenasBob,
    const std::vector<int> &paridadesBob,
    const std::vector<std::vector<int>> &permutacionDividida) {
    
    if (subcadenasAlice.size() != paridadesAlice.size() || 
        subcadenasBob.size() != paridadesBob.size() || 
        subcadenasAlice.size() != subcadenasBob.size() ||
        permutacionDividida.size() != subcadenasAlice.size()) {
        throw std::invalid_argument("Los tamaños de las subcadenas y las paridades deben coincidir.");
    }

    std::vector<std::string> subcadenasDistintasAlice;
    std::vector<std::string> subcadenasDistintasBob;
    std::vector<std::vector<int>> permutacionDistinta;

    for (size_t i = 0; i < paridadesAlice.size(); ++i) {
        if (paridadesAlice[i] != paridadesBob[i]) {
            subcadenasDistintasAlice.push_back(subcadenasAlice[i]);
            subcadenasDistintasBob.push_back(subcadenasBob[i]);
            permutacionDistinta.push_back(permutacionDividida[i]);

        }
    }

    return std::make_tuple(subcadenasDistintasAlice, subcadenasDistintasBob, permutacionDistinta);
}

int buscarBitDiferenteDicotomicoRecursivo(const std::string &subcadenaAlice,
                                          const std::string &subcadenaBob,
                                          const std::vector<int> &posicionBitsBloque) {
    // Caso base: si la longitud de la subcadena es 1, hemos encontrado el bit diferente
    if (subcadenaAlice.size() == 1) {
        // std::cout << "-------------------------------------------------------------------------------\n";
        // std::cout << "Bit erroneo encontrado en la posición original: ";
        // for (int pos : posicionBitsBloque)
        // {
        //     std::cout << pos << " ";
        // }
        // std::cout << std::endl;
        // std::cout << "-------------------------------------------------------------------------------\n";
        return posicionBitsBloque[0]; // Devuelve la posición del bit diferente
    }

    // Dividir las subcadenas actuales
    auto [bloquesAlice, paridadesAlice] = dividirCadena(subcadenaAlice, subcadenaAlice.size() / 2, false);
    auto [bloquesBob, paridadesBob] = dividirCadena(subcadenaBob, subcadenaBob.size() / 2, true);
    auto [mitadIzquierda, mitadDerecha] = dividirCadenaEnDos(posicionBitsBloque);

    // Imprimir los bloques resultantes y sus paridades
    // std::cout << "-------------------------------------------------------------------------------\n";
    // std::cout << "Bloques resultantes en Alice:" << std::endl;
    // for (size_t j = 0; j < bloquesAlice.size(); ++j) {
    //     std::cout << "\tBloque " << (j == 0 ? "Izquierdo" : "Derecho") << ": " << bloquesAlice[j]
    //               << " (Paridad: " << paridadesAlice[j] << ") (Posiciones mitad "
    //               << (j == 0 ? "Izquierda" : "Derecha") << ": ";
    //     const std::vector<int> &posiciones = (j == 0) ? mitadIzquierda : mitadDerecha;
    //     for (int pos : posiciones) {
    //         std::cout << pos << " ";
    //     }
    //     std::cout << ")" << std::endl;
    // }

    // std::cout << "Bloques resultantes en Bob:" << std::endl;
    // for (size_t j = 0; j < bloquesBob.size(); ++j) {
    //     std::cout << "\tBloque " << (j == 0 ? "Izquierdo" : "Derecho") << ": " << bloquesBob[j]
    //               << " (Paridad: " << paridadesBob[j] << ")" << std::endl;
    // }
    // std::cout << "-------------------------------------------------------------------------------\n";
    
    // Comparar las paridades de los bloques izquierdos
    if (paridadesAlice[0] != paridadesBob[0]) {
        // Si las paridades son diferentes, el bit diferente está en el bloque izquierdo
        --contadorParidad;
        return buscarBitDiferenteDicotomicoRecursivo(bloquesAlice[0], bloquesBob[0], mitadIzquierda);
    }

    // Comparar las paridades de los bloques derechos
    if (paridadesAlice[1] != paridadesBob[1]) {
        // Si las paridades son diferentes, el bit diferente está en el bloque derecho
        --contadorParidad;
        return buscarBitDiferenteDicotomicoRecursivo(bloquesAlice[1], bloquesBob[1], mitadDerecha);
    }

    return -1; // Caso en el que no se encuentre el bit diferente (no debería ocurrir si hay un bit diferente)
}

std::vector<int> buscarBitDiferenteDicotomico(const std::vector<std::string> &subcadenasDistintasAlice,
                                              const std::vector<std::string> &subcadenasDistintasBob,
                                              const std::vector<std::vector<int>> &posicionesBitsSubcadenasDistintas) {
    std::vector<int> posicionesDiferentes;

    // Iterar sobre las subcadenas distintas y sus posiciones
    for (size_t i = 0; i < subcadenasDistintasAlice.size(); ++i) {
        const std::string &subcadenaAlice = subcadenasDistintasAlice[i];
        const std::string &subcadenaBob = subcadenasDistintasBob[i];
        std::vector<int> posicionBitsBloque = posicionesBitsSubcadenasDistintas[i];

        // Llamar a la función recursiva y almacenar la posición del bit diferente
        int posicionDiferente = buscarBitDiferenteDicotomicoRecursivo(subcadenaAlice, subcadenaBob, posicionBitsBloque);
        if (posicionDiferente != -1) {
            posicionesDiferentes.push_back(posicionDiferente);
        }
    }

    return posicionesDiferentes;
}

int buscarBitDiferenteDicotomicoRecursivoBacktracking(const std::string &subcadenaAlice,
                                          const std::string &subcadenaBob,
                                          const std::vector<int> &posicionBitsBloque) {
    // Caso base: si la longitud de la subcadena es 1, hemos encontrado el bit diferente
    if (subcadenaAlice.size() == 1) {
        // std::cout << "-------------------------------------------------------------------------------\n";
        // std::cout << "Bit erroneo encontrado en la posición original: ";
        // for (int pos : posicionBitsBloque)
        // {
        //     std::cout << pos << " ";
        // }
        // std::cout << std::endl;
        // std::cout << "-------------------------------------------------------------------------------\n";
        return posicionBitsBloque[0]; // Devuelve la posición del bit diferente
    }

    // Dividir las subcadenas actuales
    auto [bloquesAlice, paridadesAlice] = dividirCadena(subcadenaAlice, subcadenaAlice.size() / 2, false);
    auto [bloquesBob, paridadesBob] = dividirCadena(subcadenaBob, subcadenaBob.size() / 2, false);
    auto [mitadIzquierda, mitadDerecha] = dividirCadenaEnDos(posicionBitsBloque);

    // Imprimir los bloques resultantes y sus paridades
    // std::cout << "-------------------------------------------------------------------------------\n";
    // std::cout << "Bloques resultantes en Alice:" << std::endl;
    // for (size_t j = 0; j < bloquesAlice.size(); ++j) {
    //     std::cout << "\tBloque " << (j == 0 ? "Izquierdo" : "Derecho") << ": " << bloquesAlice[j]
    //               << " (Paridad: " << paridadesAlice[j] << ") (Posiciones mitad "
    //               << (j == 0 ? "Izquierda" : "Derecha") << ": ";
    //     const std::vector<int> &posiciones = (j == 0) ? mitadIzquierda : mitadDerecha;
    //     for (int pos : posiciones) {
    //         std::cout << pos << " ";
    //     }
    //     std::cout << ")" << std::endl;
    // }

    // std::cout << "Bloques resultantes en Bob:" << std::endl;
    // for (size_t j = 0; j < bloquesBob.size(); ++j) {
    //     std::cout << "\tBloque " << (j == 0 ? "Izquierdo" : "Derecho") << ": " << bloquesBob[j]
    //               << " (Paridad: " << paridadesBob[j] << ")" << std::endl;
    // }
    // std::cout << "-------------------------------------------------------------------------------\n";
    
    // Comparar las paridades de los bloques izquierdos
    if (paridadesAlice[0] != paridadesBob[0]) {
        // Si las paridades son diferentes, el bit diferente está en el bloque izquierdo
        --contadorParidad;
        return buscarBitDiferenteDicotomicoRecursivoBacktracking(bloquesAlice[0], bloquesBob[0], mitadIzquierda);
    }

    // Comparar las paridades de los bloques derechos
    if (paridadesAlice[1] != paridadesBob[1]) {
        // Si las paridades son diferentes, el bit diferente está en el bloque derecho
        --contadorParidad;
        return buscarBitDiferenteDicotomicoRecursivoBacktracking(bloquesAlice[1], bloquesBob[1], mitadDerecha);
    }

    return -1; // Caso en el que no se encuentre el bit diferente (no debería ocurrir si hay un bit diferente)
}

std::vector<int> buscarBitDiferenteDicotomicoBacktracking(const std::vector<std::string> &subcadenasDistintasAlice,
                                              const std::vector<std::string> &subcadenasDistintasBob,
                                              const std::vector<std::vector<int>> &posicionesBitsSubcadenasDistintas) {
    std::vector<int> posicionesDiferentes;

    // Iterar sobre las subcadenas distintas y sus posiciones
    for (size_t i = 0; i < subcadenasDistintasAlice.size(); ++i) {
        const std::string &subcadenaAlice = subcadenasDistintasAlice[i];
        const std::string &subcadenaBob = subcadenasDistintasBob[i];
        std::vector<int> posicionBitsBloque = posicionesBitsSubcadenasDistintas[i];

        // Llamar a la función recursiva y almacenar la posición del bit diferente
        int posicionDiferente = buscarBitDiferenteDicotomicoRecursivoBacktracking(subcadenaAlice, subcadenaBob, posicionBitsBloque);
        if (posicionDiferente != -1) {
            posicionesDiferentes.push_back(posicionDiferente);
        }
    }

    return posicionesDiferentes;
}