#include "header.h"

// Función para imprimir un std::vector<int>
void imprimirVector(const std::vector<int>& vec) {
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Función para realizar la operación XOR en las posiciones generadas
void realizarXOR(std::string &cadena, const std::vector<int> &posiciones) {
    // Imprimir las posiciones de los bits erróneos en la cadena original
    // std::cout << "Posiciones de los bits erróneos en la cadena original: " << std::endl;
    // for (int index : posiciones) {
    //     std::cout << index << " ";
    // }
    // std::cout << std::endl;

    for (int index : posiciones) {
        cadena[index] = (cadena[index] == '0') ? '1' : '0';
    }
}

// Función para dividir un vector de enteros en subcadenas de longitud lenk
std::vector<std::vector<int>> dividirVector(const std::vector<int> &posiciones, int lenk) {
    std::vector<std::vector<int>> subcadenas;

    int totalSize = posiciones.size();
    for (int i = 0; i < totalSize; i += lenk) {
        std::vector<int> subVector(posiciones.begin() + i, posiciones.begin() + std::min(i + lenk, totalSize));
        subcadenas.push_back(subVector);
    }

    return subcadenas;
}

// Función para determinar la potencia de dos más cercana
int potenciaDeDosCercana(int valor, bool redondearArriba) {
    int potencia = 1;
    while (potencia < valor) {
        potencia *= 2;
    }
    int anterior = potencia / 2;

    if (redondearArriba) {
        // Redondear hacia arriba
        return potencia;
    } else {
        // Redondear hacia abajo
        return anterior;
    }
}

// Función para dividir una cadena de bits en subcadenas de tamaño de una potencia de dos más cercana
std::tuple<std::vector<std::string>, std::vector<int>> dividirCadena(const std::string &cadena, int tamanioSubcadena, bool bitExpuesto) {
     int potenciaCercana = potenciaDeDosCercana(tamanioSubcadena, true);
     int longitudCadena = cadena.length();
     std::vector<std::string> subcadenas;
     std::vector<int> paridades;

     for (int i = 0; i < longitudCadena; i += potenciaCercana) {
         std::string subcadena = cadena.substr(i, potenciaCercana);
         subcadenas.push_back(subcadena);
         // Calcular la paridad de la subcadena y almacenarla
         int paridad = calcularParidad(subcadena, bitExpuesto);
         paridades.push_back(paridad);
     }
    return std::make_tuple(subcadenas, paridades);
}

// Función para dividir una cadena de vectores de enteros en dos mitades
std::tuple<std::vector<int>, std::vector<int>> dividirCadenaEnDos(const std::vector<int> &cadena) {
    int longitudCadena = cadena.size();
    int mitad = longitudCadena / 2;

    // Dividir la cadena en dos mitades
    std::vector<int> mitadIzquierda(cadena.begin(), cadena.begin() + mitad);
    std::vector<int> mitadDerecha(cadena.begin() + mitad, cadena.end());

    return std::make_tuple(mitadIzquierda, mitadDerecha);
}

// Función para realizar una operación XOR en bits específicos de una cadena binaria
std::string xorBitsAtPositions(std::string &binaryString, const std::vector<int> &positions) {
    std::string result = binaryString;

    // Verificar que todas las posiciones sean válidas
    for (int pos : positions) {
        if (pos < 0 || pos >= binaryString.length()) {
            throw std::out_of_range("Posición fuera de rango: " + std::to_string(pos));
        }
    }
    // Realizar la operación XOR en las posiciones especificadas
    for (int pos : positions) {
        //std::cout << "Bit numero " << pos << " corregido" << std::endl;
        result[pos] = (binaryString[pos] == '0') ? '1' : '0';
        //std::cout << "Nuevo valor " << result[pos] << std::endl;
    }
    return result;
}

// Función para realizar una operación XOR en un bit específico de una cadena binaria
std::string xorBitsAtPositionBacktracking(std::string &binaryString, int position) {
    std::string result = binaryString;
    // Verificar que la posición sea válida
    if (position < 0 || position >= binaryString.length()) {
        throw std::out_of_range("Posición fuera de rango: " + std::to_string(position));
    }

    // Realizar la operación XOR en la posición especificada
    result[position] = (binaryString[position] == '0') ? '1' : '0';

    return result;
}

int compararCadenas(const std::string& cadena1, const std::string& cadena2) {
    if (cadena1 == cadena2)
    {
        return 0;
    }
    else
    {
        return  1;
    }
}