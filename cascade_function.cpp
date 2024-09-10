#include "header.h"

std::tuple<std::string, std::string, int> iteracion_cascade(
    std::vector<int> permutacion, std::string cadenaAlice, std::string cadenaBob,
    double QBER, int numero_iteracion, std::vector<int> permutacionIterAnterior)
{
    // Imprimir número de la iteración
    // std::cout << "*******************" << std::endl;
    //std::cout << "ITERACION NUMERO " << numero_iteracion + 1 << std::endl;
    // Solicitar el tamaño deseado de las subcadenas
    int lenk = pow(2, numero_iteracion) * pow(2, std::floor((log2(std::floor(0.73/QBER)))));
    std::cout << "Longitud de bloques en iteracion " << numero_iteracion + 1 << " = " << lenk << std::endl;
    
    // Aplicar permutación
    aplicarPermutacion(cadenaAlice, permutacion);
    aplicarPermutacion(cadenaBob, permutacion);   

    // Dividir la cadena en subcadenas de tamaño de una potencia de dos más cercana
    auto [tlbAlice, paridadesAlice] = dividirCadena(cadenaAlice, lenk, false);
    auto [tlbBob, paridadesBob] = dividirCadena(cadenaBob, lenk, true);
    std::vector<std::vector<int>> permutacionDividida = dividirVector(permutacion, lenk);

    // Obtener subcadenas con paridades distintas
    auto subcadenasDistintas = obtenerSubcadenasConParidadesDistintas(tlbAlice, paridadesAlice, tlbBob, paridadesBob, permutacionDividida);
    auto subcadenasDistintasAlice = std::get<0>(subcadenasDistintas);
    auto subcadenasDistintasBob = std::get<1>(subcadenasDistintas);
    auto posicionesBitsSubcadenasDistintas = std::get<2>(subcadenasDistintas);

    std::vector<int> posicionesDiferentes = buscarBitDiferenteDicotomico(subcadenasDistintasAlice, subcadenasDistintasBob, posicionesBitsSubcadenasDistintas);
    std::cout << "Bits erroneos encontrados" << std::endl;
    imprimirVector(posicionesDiferentes);

    // Deshago la permutacion
    deshacerPermutacion(cadenaAlice, permutacion);
    deshacerPermutacion(cadenaBob, permutacion);

    std::string result = xorBitsAtPositions(cadenaBob, posicionesDiferentes);

    aplicarPermutacion(cadenaAlice, permutacion);
    aplicarPermutacion(result, permutacion);

    // Dividir la cadena en subcadenas de tamaño de una potencia de dos más cercana
    auto [tlbAlice_store, paridadesAlice_store] = dividirCadena(cadenaAlice, lenk, false);
    auto [tlbBob_store, paridadesBob_store] = dividirCadena(result, lenk, false);
    std::vector<std::vector<int>> permutacionDividida_store = dividirVector(permutacion, lenk);

    for (int i = 0; i < permutacionDividida_store.size(); ++i) {
        std::cout << "Alice TLB storing" << tlbAlice_store[i] << std::endl;
        std::cout << "Bob   TLB storing" << tlbBob_store[i] << std::endl;
        imprimirVector(permutacionDividida_store[i]);
    }

    // Almacenar TLBs sin fallos de la iteracion actual
    StringVectorStorage::getInstance().store(tlbAlice_store);
    StringVectorStorage::getInstance().store(tlbBob_store);
    IntVectorStorage::getInstance().store(permutacionDividida_store);

    deshacerPermutacion(cadenaAlice, permutacion);
    deshacerPermutacion(result, permutacion);

    if (numero_iteracion == 0 || posicionesDiferentes.empty()) {
        return std::make_tuple(result, cadenaAlice, lenk);
    }
    else {
        std::vector<int> posicionesDiferentesBack = backtracking(cadenaAlice, result, QBER, numero_iteracion, permutacionIterAnterior, posicionesDiferentes);
        std::cout << "Bits erroneos encontrados debido a backtracking" << std::endl;
        imprimirVector(posicionesDiferentesBack);

        std::string resultBack = xorBitsAtPositions(result, posicionesDiferentesBack);

        size_t indexAlice = 2*(numero_iteracion - 1);
        size_t indexBob = 2*(numero_iteracion - 1) + 1;
        size_t indexPermutacion = numero_iteracion - 1;

        StringVectorStorage::getInstance().remove(indexAlice);
        StringVectorStorage::getInstance().remove(indexBob);
        IntVectorStorage::getInstance().remove(indexPermutacion);

        auto [tlbAlice_storeBack, paridadesAlice_storeBack] = dividirCadena(cadenaAlice, lenk, false);
        auto [tlbBob_storeBack, paridadesBob_storeBack] = dividirCadena(resultBack, lenk, false);
        std::vector<std::vector<int>> permutacionDividida_storeBack = dividirVector(permutacion, lenk);

        // // std::cout << "**************iteracion_cascade ****************"<< std::endl;
        // // for(int i = 0; i < tlbAlice_store.size(); ++i){
        // // std::cout << "Numero de bloque : " << i << std::endl;
        // // std::cout << "TLB alice backtracking : " << tlbAlice_store[i] << std::endl;
        // // std::cout << "TLB bob backtracking : " << tlbBob_store[i] << std::endl;
        // // imprimirVector(permutacionDividida_store[i]);
        // // }

        // // Almacenar TLBs
        StringVectorStorage::getInstance().store(tlbAlice_storeBack);
        StringVectorStorage::getInstance().store(tlbBob_storeBack);
        IntVectorStorage::getInstance().store(permutacionDividida_storeBack);

        return std::make_tuple(resultBack, cadenaAlice, lenk);
    }
}

void cascade(double qberMin, double qberMax, double refinement, int longitud){

    int lenk;
    std::string cadenaAlice;
    std::string cadenaBob;
    double limiteShannon;

    std::vector<double> bitExpuestos;
    std::vector<double> eficienciaReconciliacion;
    std::vector<double> tasaGeneracionClaves;
    std::vector<double> frameErrorRate;
    std::vector<double> qberVec = construirVector(qberMin, qberMax, refinement);

    progressbar bar((qberMax-qberMin)/refinement);

    for (double qber : qberVec){
        do{
            std::cout << "********* QBER = " << qber << "********" <<std::endl;  
            reiniciarContadorParidad();
            std::tuple<std::string, std::string> init_state = generacionCondicionesIniciales(qber, longitud);
            cadenaAlice = std::get<0>(init_state);
            cadenaBob = std::get<1>(init_state);
            limiteShannon = (-1)*qber*log2(qber) + (-1)*(1-qber)*log2(1-qber);

            // GInicializacion clase permutacion
            Permutacion perm;
            int iter_number = 0;
            
            // Reinicializar las instancias del backtracking
            StringVectorStorage::getInstance().reset();
            IntVectorStorage::getInstance().reset();

            do {
                perm.agregarPermutacion(generarpermutacionAleatoria(cadenaAlice, cadenaBob));
                //std::cout << "CASCADE iteracion " << iter_number << std::endl;
                if(iter_number == 0){
                    // Obtener permutación de la iteracion actual
                    std::vector<int> permutacionIter = perm.getPermutacionPorIndice(iter_number);
                    // std::cout << "Permutacion iteracion " << iter_number <<" : " << std::endl;
                    // imprimirVector(permutacionIter);
                    std::tuple<std::string, std::string, int> iter_result = iteracion_cascade(permutacionIter, cadenaAlice, cadenaBob, qber, iter_number, 
                                                                                permutacionIter);
                    cadenaBob = std::get<0>(iter_result);
                    cadenaAlice = std::get<1>(iter_result);
                    iter_number++;
                }
                else {
                    // Obtener permutación de la iteracion actual
                    std::vector<int> permutacionIter = perm.getPermutacionPorIndice(iter_number);
                    std::vector<int> permutacionIterAnterior = perm.getPermutacionPorIndice(iter_number - 1);
                    // std::cout << "Permutacion iteracion " << iter_number <<" : " << std::endl;
                    // imprimirVector(permutacionIter);

                    // std::cout << "Permutacion iteracion anterior" << iter_number <<" : " << std::endl;
                    // imprimirVector(permutacionIterAnterior);

                    std::tuple<std::string, std::string, int> current_iter_result = iteracion_cascade(permutacionIter, cadenaAlice, cadenaBob, qber, iter_number, 
                                                                                        permutacionIterAnterior);
                    cadenaBob = std::get<0>(current_iter_result);
                    cadenaAlice = std::get<1>(current_iter_result);
                    iter_number++;
                }
                //std::cout << "Bits expuestos en la iteracion " << iter_number - 1 << " (sumatorio): " << obtenerContadorParidad() << std::endl;
                //std::cout << "Longitud de bloques en iteracion " << iter_number - 1 << " = " << lenk << std::endl;
            } while (iter_number < 4);

            //¿EXITO EN LA RECONCILIACION?
            //std::cout << std::endl;    
            int res = compararCadenas(cadenaAlice, cadenaBob);
            //std::cout << "****************" << std::endl;
            if (res == 0) {
                //std::cout << "RECONCILIACION = YES" << std::endl;
                //DATA STUDY
                double bitsExpuestosTotales = obtenerContadorParidad();
                //std::cout << "Bits expuestos totales" << bitsExpuestosTotales << std::endl;
                //std::cout << "Tamaño cadenas" << cadenaAlice.size() << std::endl;
                bitExpuestos.push_back(bitsExpuestosTotales);
                double eficienciaReconciliacionValue = bitsExpuestosTotales/(cadenaAlice.size()*limiteShannon);
                eficienciaReconciliacion.push_back(eficienciaReconciliacionValue);
                double tasaGeneracionValue = 1 - (1 + eficienciaReconciliacionValue)*limiteShannon;
                tasaGeneracionClaves.push_back(tasaGeneracionValue);
                //std::cout << "Limite de Shannon" << " " << limiteShannon  << std::endl;
                int iter = 0;
                // for (int bits : bitExpuestosIteracion) 
                // {
                //     std::cout << "Bits expuestos en la iteracion " << iter << " (sumatorio): " << bits << " " << std::endl;
                //     ++iter;
                // }
                // std::cout << "Total de bits expuestos" << " " << bitsExpuestosTotales  << std::endl;
                // std::cout << "Total de bits restantes para formar claves seguras" << " " << cadenaAlice.size() - bitsExpuestosTotales  << std::endl;
                // std::cout << "Eficiencia de reconciliación" << " " << eficienciaReconciliacionValue << std::endl;
                // std::cout << "Tasa de generacion de claves" << " " << tasaGeneracionValue  << std::endl;
                }
            else {
                //std::cout << "RECONCILIACION = NO" << std::endl;
                }
        }while(cadenaAlice != cadenaBob);
        bar.update();
        //std::cout << " " << std::endl;
    }
    hacer_grafica(qberVec, bitExpuestos, L"Bits Expuestos", L"QBER", L"Bits Expuestos totales", "cascade_QBER.png");
    hacer_grafica(qberVec, eficienciaReconciliacion, L"Eficiencia Reconciliacion", L"QBER", L"f", "cascade_eficiencia.png");
    hacer_grafica(qberVec, tasaGeneracionClaves, L"Tasa de Generacion de Claves Seguras", L"QBER", L"SKR(bps)", "cascade_tasaClaves.png");
}