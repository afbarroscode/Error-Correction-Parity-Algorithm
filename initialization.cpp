#include "header.h"

// Función para generar una cadena de bits aleatoria
std::string generarCadenaDeBits(int longitud) {
    std::string cadena;
    for (int i = 0; i < longitud; ++i) {
        cadena += (rand() % 2) ? '1' : '0';
    }
    return cadena;
}

// Función para generar posiciones aleatorias
std::vector<int> generarPosicionesAleatorias(int longitud, double porcentaje) {
    int numPosiciones = static_cast<int>(longitud * porcentaje);
    std::vector<int> posiciones(longitud);
    for (int i = 0; i < longitud; ++i) {
        posiciones[i] = i;
    }

    // Inicializar un motor de números aleatorios
    std::random_device rd;
    std::default_random_engine rng(rd());

    // Barajar las posiciones
    std::shuffle(posiciones.begin(), posiciones.end(), rng);

    // Seleccionar las primeras numPosiciones
    posiciones.resize(numPosiciones);

    return posiciones;
}

// Función para inicializar el proceso
std::tuple<double, double, double, int> inicializacion() {

    int longitud;
    std::cout << "............................................." << std::endl;
    std::cout << "Ingrese la longitud de la cadena de bits: " << std::endl;
    std::cin >> longitud;
    int longitud_potenciadeDos = potenciaDeDosCercana(longitud, true);
    std::cout << "Longitud de las cadenas de Alice y Bob: " << longitud_potenciadeDos << std::endl;
    std::cout << std::endl;

    // Solicitar el porcentaje de bits a modificar al usuario
    double QBERMin;
    double QBERMax;
    double refinement;
    std::cout << "............................................." << std::endl;
    std::cout << "Ingrese el QBER minimo (debe ser un número decimal entre 0 y 1): " << std::endl;
    std::cin >> QBERMin;
    std::cout << "Ingrese el QBER maximo (debe ser un número decimal entre 0 y 1): " << std::endl;
    std::cin >> QBERMax;
    std::cout << "Ingrese el factor de refinamiento (debe ser un número decimal entre 0 y 1): " << std::endl;
    std::cin >> refinement;

    return std::make_tuple(QBERMin, QBERMax, refinement, longitud_potenciadeDos);
}

std::vector<double> construirVector(double inicio, double fin, double paso) {
    std::vector<double> vec;
    for (double valor = inicio; valor <= fin; valor += paso) {
        vec.push_back(valor);
    }
    return vec;
}

std::tuple<std::string, std::string> generacionCondicionesIniciales(double qber, int longitud){

    // Inicializa el generador de números aleatorios con una semilla basada en el tiempo
    srand(static_cast<unsigned int>(time(0)));

    // Genera la cadena de bits aleatoria
    std::string cadenaAlice = generarCadenaDeBits(longitud);

    // // Muestra la cadena generada
    // std::cout << "............................................." << std::endl;
    // std::cout << "Cadena de Alice: " << cadenaAlice << std::endl;

    std::string cadenaBob = cadenaAlice;

    // Generar posiciones aleatorias basadas en el porcentaje
    std::vector<int> posiciones_erroneas = generarPosicionesAleatorias(cadenaBob.length(), qber);
    // std::cout << "Posiciones erroneas: " << std::endl; 
    // imprimirVector(posiciones_erroneas);

    // Realizar la operación XOR en las posiciones generadas
    realizarXOR(cadenaBob, posiciones_erroneas);

    // Mostrar la cadena resultante
    // std::cout << "............................................." << std::endl;
    // std::cout << "Cadena de Bob: " << cadenaBob << std::endl;

    return std::make_tuple(cadenaAlice, cadenaBob);
}