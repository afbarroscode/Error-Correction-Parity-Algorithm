#include "header.h"

std::vector<std::pair<size_t, std::vector<int>>> findVectorsContainingPositions(
    const std::vector<int>& posicionesDiferentes, 
    const std::vector<std::vector<int>>& permutacionDivididaBack) 
{
    std::vector<std::pair<size_t, std::vector<int>>> result;

    // Recorrer cada vector de permutacionDivididaBack con su índice
    for (size_t i = 0; i < permutacionDivididaBack.size(); ++i) {
        const auto& vec = permutacionDivididaBack[i];
        // Verificar si el vector actual contiene algún elemento de posicionesDiferentes
        for (int pos : posicionesDiferentes) {
            if (std::find(vec.begin(), vec.end(), pos) != vec.end()) {
                result.emplace_back(i, vec);
                break; // Salir del bucle interno si encontramos un elemento
            }
        }
    }

    return result;
}

// Función para obtener los strings en función de sus posiciones
std::vector<std::string> getStringsByIndices(const std::vector<std::string>& original, const std::vector<size_t>& indices) {
    std::vector<std::string> result;

    for (size_t index : indices) {
        if (index >= original.size()) {
            throw std::out_of_range("getStringsByIndices:Índice fuera de rango");
        }
        result.push_back(original[index]);
    }

    return result;
}

std::vector<std::vector<int>> getVectorsByIndices(
    const std::vector<std::vector<int>>& original, 
    const std::vector<size_t>& indices) 
{
    std::vector<std::vector<int>> result;

    for (size_t index : indices) {
        if (index >= original.size()) {
            throw std::out_of_range("getVectorsByIndices: Índice fuera de rango");
        }
        result.push_back(original[index]);
    }

    return result;
}

void eliminarDuplicados(std::vector<size_t>& bloquesBacktracking) {
    // Usamos un set para eliminar duplicados
    std::set<size_t> elementosUnicos(bloquesBacktracking.begin(), bloquesBacktracking.end());
    
    // Vaciamos el vector original
    bloquesBacktracking.clear();
    
    // Rellenamos el vector con los elementos únicos del set
    bloquesBacktracking.assign(elementosUnicos.begin(), elementosUnicos.end());
}

std::vector<int> backtracking(
    std::string cadenaAlice, std::string cadenaBob,
    double QBER, int numero_iteracion,
    std::vector<int> permutacionIterAnterior,
    std::vector<int> posicionesDiferentes){

    aplicarPermutacion(cadenaAlice, permutacionIterAnterior);
    aplicarPermutacion(cadenaBob, permutacionIterAnterior);

    // Recuperar vectores de almacenamiento con indices
    size_t indexAlice = 2*(numero_iteracion - 1);
    size_t indexBob = 2*(numero_iteracion - 1) + 1;
    size_t indexPermutacion = numero_iteracion - 1;

    std::vector<std::string> tlbAliceBack = StringVectorStorage::getInstance().retrieve(indexAlice);
    std::vector<std::string> tlbBobBack = StringVectorStorage::getInstance().retrieve(indexBob);
    std::vector<std::vector <int>> permutacionDivididaBack = IntVectorStorage::getInstance().retrieve(indexPermutacion);
    // std::vector<int> paridadesAliceBack = IntStorage::getInstance().retrieve(0);
    // std::vector<int> paridadesBobBack = IntStorage::getInstance().retrieve(0);

    // std::cout << "------ Backtracking -------"<< std::endl;
    // for(int i = 0; i < tlbAliceBack.size(); ++i){
    // std::cout << "Numero de bloque : " << i << std::endl;
    // std::cout << "TLB alice backtracking : " << tlbAliceBack[i] << "// paridad = " << paridadesAliceBack[i] << std::endl;
    // std::cout << "TLB bob backtracking : " << tlbBobBack[i] << "// paridad = " << paridadesBobBack[i] << std::endl;
    // imprimirVector(permutacionDivididaBack[i]);
    // }

    std::vector<size_t> bloquesBacktracking ={};
    int contadorBloquesBack = 0;
    for (size_t i = 0; i < permutacionDivididaBack.size(); ++i) {
        for (int element : permutacionDivididaBack[i]) {
            for (int pos : posicionesDiferentes) {
                if (pos == element) {
                    // std::cout << "Pos == element = " << pos << std::endl;
                    std::cout << "Bloque agregado a bloqueBacktracking : " << std::endl;
                    imprimirVector(permutacionDivididaBack[i]);
                    bloquesBacktracking.push_back(i);
                    ++ contadorBloquesBack;
                }
                else{}
            }
        }
    }

    eliminarDuplicados(bloquesBacktracking);

    // Validar los índices antes de usar las funciones
    // if (bloquesBacktracking.empty()) {
    //     std::cout << "No se han encontrado bits erroneos para hacer backtracking" << std::endl;
    //     return std::make_tuple(result, lenk);
    // }
    std::vector<std::string> selectedStringsAlice = getStringsByIndices(tlbAliceBack, bloquesBacktracking);
    std::vector<std::string> selectedStringsBob = getStringsByIndices(tlbBobBack, bloquesBacktracking);
    std::vector<std::vector<int>> selectedVectors = getVectorsByIndices(permutacionDivididaBack, bloquesBacktracking);


    // std::cout << "Subcadenas distintas Iteracion Backtracking" << std::endl;
    // for(int i = 0; i < selectedStringsAlice.size(); ++i){
    //     std::cout << "Alice" << selectedStringsAlice[i] << std::endl;
    //     std::cout << "Bob" << selectedStringsBob[i] << std::endl;
    //     std::cout << "Permutacion" << std::endl; imprimirVector(selectedVectors[i]);
    // }

    for (int i = 0; i < selectedVectors.size(); ++i) {
        for (int j = 0; j < selectedVectors[i].size(); ++j) {
            for (int pos : posicionesDiferentes) {
                if (pos == selectedVectors[i][j]) {
                    std::cout << "Posicion que XOReada : " << pos << " en el bloque = " << j << std::endl;
                    std::cout << "Alice TLB" << selectedStringsAlice[i] << std::endl;
                    std::cout << "Bob   TLB" << selectedStringsBob[i] << std::endl;
                    imprimirVector(selectedVectors[i]);
                }
            }
        }
    }

    std::vector<int> posicionesDiferentesBack = buscarBitDiferenteDicotomicoBacktracking(selectedStringsAlice, selectedStringsBob, selectedVectors);

    deshacerPermutacion(cadenaAlice, permutacionIterAnterior);
    deshacerPermutacion(cadenaBob, permutacionIterAnterior);

    // StringVectorStorage::getInstance().remove(indexAlice);
    // StringVectorStorage::getInstance().remove(indexBob);
    // IntVectorStorage::getInstance().remove(indexPermutacion);

    return posicionesDiferentesBack;

}