#include "header.h"

std::tuple<std::string, int> iteracion_cascade_modified1(
    std::vector<int> permutacion, std::string cadenaAlice, std::string cadenaBob,
    double QBER, int numero_iteracion, std::vector<int> permutacionIterAnterior, int longitud)
{
    // Imprimir número de la iteración
    // std::cout << "*******************" << std::endl;
    // std::cout << "ITERACION NUMERO " << numero_iteracion + 1 << std::endl;
    // Solicitar el tamaño deseado de las subcadenas
    int max, min;
    std::cout << pow(2, log2(1 / QBER)) << std::endl;
    if(QBER <= 0.25){
        std::vector<int> value_min = {static_cast<int>(pow(2, std::floor(log2(1 / QBER)))), longitud / 2};
        if(value_min[0] < value_min[1]){ 
            min = value_min[0];
        }
        else{
            min = value_min[1];
        }
    }
    else{
        std::vector<int> value_max = {static_cast<int>(pow(2, log2(1 / QBER) - 1)), 1};
        if(value_max[0] > value_max[1]){
            max = value_max[0];
        }
        else{
            max = value_max[1];
        }
        std::vector<int> value_min = {max, longitud / 2};
        if(value_min[0] < value_min[1]){
            min = value_min[0];
        }
        else{
            min = value_min[1];
        }
    }
    int lenk = pow(2, numero_iteracion) * min;
    std::cout << "Longitud de bloques en iteracion " << numero_iteracion << " = " << lenk << std::endl;
    
    // Aplicar permutación
    aplicarPermutacion(cadenaAlice, permutacion);
    aplicarPermutacion(cadenaBob, permutacion);   

    // Dividir la cadena en subcadenas de tamaño de una potencia de dos más cercana
    auto [tlbAlice, paridadesAlice] = dividirCadena(cadenaAlice, lenk, false);
    auto [tlbBob, paridadesBob] = dividirCadena(cadenaBob, lenk, true);
    std::vector<std::vector<int>> permutacionDividida = dividirVector(permutacion, lenk);

    // Almacenar TLBs
    StringVectorStorage::getInstance().store(tlbAlice);
    StringVectorStorage::getInstance().store(tlbBob);
    IntVectorStorage::getInstance().store(permutacionDividida);

    // Obtener subcadenas con paridades distintas
    auto subcadenasDistintas = obtenerSubcadenasConParidadesDistintas(tlbAlice, paridadesAlice, tlbBob, paridadesBob, permutacionDividida);
    auto subcadenasDistintasAlice = std::get<0>(subcadenasDistintas);
    auto subcadenasDistintasBob = std::get<1>(subcadenasDistintas);
    auto posicionesBitsSubcadenasDistintas = std::get<2>(subcadenasDistintas);

    std::vector<int> posicionesDiferentes = buscarBitDiferenteDicotomico(subcadenasDistintasAlice, subcadenasDistintasBob, posicionesBitsSubcadenasDistintas);
    // std::cout << "Bits erroneos encontrados" << std::endl;
    // imprimirVector(posicionesDiferentes);

    // Deshago la permutacion
    deshacerPermutacion(cadenaAlice, permutacion);
    deshacerPermutacion(cadenaBob, permutacion);

    std::string result = xorBitsAtPositions(cadenaBob, posicionesDiferentes);
    cadenaBob = result;

    if (numero_iteracion == 0 || posicionesDiferentes.empty()) {
        return std::make_tuple(result, lenk);
    } 
    else {
        std::vector<int> posicionesDiferentesBack = backtracking(cadenaAlice, cadenaBob, QBER, numero_iteracion, permutacionIterAnterior, posicionesDiferentes);
        std::string resultBack = xorBitsAtPositions(cadenaBob, posicionesDiferentes);
        cadenaBob = resultBack;

        auto [tlbAlice_storeBack, paridadesAlice_storeBack] = dividirCadena(cadenaAlice, lenk, false);
        auto [tlbBob_storeBack, paridadesBob_storeBack] = dividirCadena(cadenaBob, lenk, false);
        std::vector<std::vector<int>> permutacionDividida_storeBack = dividirVector(permutacion, lenk);

        // std::cout << "**************iteracion_cascade ****************"<< std::endl;
        // for(int i = 0; i < tlbAlice_store.size(); ++i){
        // std::cout << "Numero de bloque : " << i << std::endl;
        // std::cout << "TLB alice backtracking : " << tlbAlice_store[i] << std::endl;
        // std::cout << "TLB bob backtracking : " << tlbBob_store[i] << std::endl;
        // imprimirVector(permutacionDividida_store[i]);
        // }

        // Almacenar TLBs
        StringVectorStorage::getInstance().store(tlbAlice_storeBack);
        StringVectorStorage::getInstance().store(tlbBob_storeBack);
        IntVectorStorage::getInstance().store(permutacionDividida_storeBack);

        return std::make_tuple(cadenaBob, lenk);
    }
}

void cascade_optimized1(double qberMin, double qberMax, double refinement, int longitud){

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

            // Genramos todas las permutaciónes aleatoria sobre ambas cadenas
            std::vector<int> permutacion1 = generarpermutacionAleatoria(cadenaAlice, cadenaBob);
            std::vector<int> permutacion2 = generarpermutacionAleatoria(cadenaAlice, cadenaBob);
            std::vector<int> permutacion3 = generarpermutacionAleatoria(cadenaAlice, cadenaBob);
            std::vector<int> permutacion4 = generarpermutacionAleatoria(cadenaAlice, cadenaBob);
            Permutacion perm;
            perm.agregarPermutacion(permutacion1);
            perm.agregarPermutacion(permutacion2);
            perm.agregarPermutacion(permutacion3);
            perm.agregarPermutacion(permutacion4);

            //Reseteamos iteracion a 0
            int iter_number = 0;
            
            // Reinicializar las instancias del backtracking
            StringVectorStorage::getInstance().reset();
            IntVectorStorage::getInstance().reset();

            do {
                //std::cout << "CASCADE iteracion " << iter_number << std::endl;
                if(iter_number == 0){
                    // Obtener permutación de la iteracion actual
                    std::vector<int> permutacionIter = perm.getPermutacionPorIndice(iter_number);
                    std::tuple<std::string, int> iter_result = iteracion_cascade_modified1(permutacionIter, cadenaAlice, cadenaBob, qber, iter_number, 
                                                                                permutacionIter, longitud);
                    cadenaBob = std::get<0>(iter_result);
                    iter_number++;
                }
                else {
                    // Obtener permutación de la iteracion actual
                    std::vector<int> permutacionIter = perm.getPermutacionPorIndice(iter_number);
                    std::vector<int> permutacionIterAnterior = perm.getPermutacionPorIndice(iter_number - 1);

                    std::tuple<std::string, int> current_iter_result = iteracion_cascade_modified1(permutacionIter, cadenaAlice, cadenaBob, qber, iter_number, 
                                                                                        permutacionIterAnterior, longitud);
                    cadenaBob = std::get<0>(current_iter_result);
                    iter_number++;
                }
                //std::cout << "Bits expuestos en la iteracion " << iter_number << " (sumatorio): " << obtenerContadorParidad() << std::endl; 
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
    }
    hacer_grafica(qberVec, bitExpuestos, L"Bits Expuestos", L"QBER", L"Bits Expuestos totales", "cascade_modified1_QBER.png");
    hacer_grafica(qberVec, eficienciaReconciliacion, L"Eficiencia Reconciliacion", L"QBER", L"f", "cascade_modified1_eficiencia.png");
    hacer_grafica(qberVec, tasaGeneracionClaves, L"Tasa de Generacion de Claves Seguras", L"QBER", L"SKR(bps)", "cascade_modified1_tasaClaves.png");
}