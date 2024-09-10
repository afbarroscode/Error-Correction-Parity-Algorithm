/*Para compilar en terminal

g++ -c bbbss_main.cpp -o bbbss_main.o
g++ -c common_function.cpp -o common_function.o
g++ bbbss_main.o common_function.o -o bbbss

Actualizacion para compilar con makefile:

    make --> bbbss*

*/

#include "header.h"

int main() {
    //Condiciones de inicializacion
    auto [qberMin, qberMax, refinement, longitud] = inicializacion();

    //Protocolo BBBSS
    std::cout << "-------RECONCILIACION BBBSS-------" << std::endl;
    bbbss(qberMin, qberMax, refinement, longitud);
    std::cout << std::endl;

    //Protocolo cascade
    // std::cout << "-------RECONCILIACION CASCADE-------" << std::endl;
    // cascade(qberMin, qberMax, refinement, longitud);
    // std::cout << std::endl;


    //Protocolo cascade modified 1
    // std::cout << "-------RECONCILIACION CASCADE MODIFIED 1-------" << std::endl;
    // cascade_optimized1(qberMin, qberMax, refinement, longitud);
    // std::cout << std::endl;

    return 0;
}