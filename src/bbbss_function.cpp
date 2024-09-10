#include "header.h"

void export_to_csv(const std::vector<double>& data_x, const std::vector<double>& data_y, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "x,y\n";  // Encabezado para los datos
        for (size_t i = 0; i < data_x.size(); ++i) {
            file << data_x[i] << "," << data_y[i] << "\n";
        }
        file.close();
        std::cout << "Datos exportados a " << filename << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo!" << std::endl;
    }
}

std::tuple<std::string, int> iteracion_bbbss(std::string cadenaAlice, std::string cadenaBob, double QBER, int numero_iteracion) {
    //Imprimir numero de la iteracion
    // std::cout << "*******************" << std::endl;
    // std::cout << "ITERACION NUMERO " << numero_iteracion + 1 << std::endl;

    // Realizar permutación aleatoria sobre ambas cadenas
    std::vector<int> permutacion = permutacionAleatoria(cadenaAlice, cadenaBob);

    // Solicitar el tamaño deseado de las subcadenas
    int lenk = pow(2, numero_iteracion)*pow(2, std::floor((log2(std::ceil(1/QBER))-1)));
    // std::cout << "Tamaño de las subcadenas son de " << lenk << std::endl;

    // Dividir la cadena en subcadenas de tamaño de una potencia de dos más cercana
    auto [tlbAlice, paridadesAlice] = dividirCadena(cadenaAlice, lenk, false);
    auto [tlbBob, paridadesBob] = dividirCadena(cadenaBob, lenk, true); 
    std::vector<std::vector<int>> permutacionDividida = dividirVector(permutacion, lenk);

    // // Mostrar las subcadenas y sus paridades
    // std::cout << "Subcadenas y paridades resultantes de Alice:" << std::endl;
    // for (size_t i = 0; i < tlbAlice.size(); ++i) {
    //     std::cout << i + 1 << ")" << tlbAlice[i] << " (Paridad: " << paridadesAlice[i] << ")" << std::endl;
    // }
    // std::cout << "Subcadenas y paridades resultantes de Bob:" << std::endl;
    // for (size_t i = 0; i < tlbBob.size(); ++i) {
    //     std::cout << i + 1 << ")"<< tlbBob[i] << " (Paridad: " << paridadesBob[i] << ")" << std::endl;
    // }

    // Obtener subcadenas con paridades distintas
    auto subcadenasDistintas = obtenerSubcadenasConParidadesDistintas(tlbAlice, paridadesAlice, tlbBob, paridadesBob, permutacionDividida);
    auto subcadenasDistintasAlice = std::get<0>(subcadenasDistintas);
    auto subcadenasDistintasBob = std::get<1>(subcadenasDistintas);
    auto posicionesBitsSubcadenasDistintas = std::get<2>(subcadenasDistintas);

    // std::cout << "Subcadenas con paridades distintas:" << std::endl;
    // std::cout << "             " << "Alice"<< "/" << "Bob" <<std::endl;
    // for (size_t i = 0; i < subcadenasDistintasAlice.size(); ++i) 
    // {
    //     std::cout << "Subcadena" << i + 1 << ": " << subcadenasDistintasAlice[i] << " / " << subcadenasDistintasBob[i] << std::endl;
    // }

    std::vector<int> posicionesDiferentes = buscarBitDiferenteDicotomico(subcadenasDistintasAlice, subcadenasDistintasBob, posicionesBitsSubcadenasDistintas);
    // for (int pos : posicionesDiferentes) {
    //     std::cout << "Bit erroneo encontrado en la posición original: " << pos << std::endl;
    // }
    deshacerPermutacion(cadenaAlice, permutacion);
    deshacerPermutacion(cadenaBob, permutacion);

    std::string result = xorBitsAtPositions(cadenaBob, posicionesDiferentes);

    return std::make_tuple(result, lenk);
}

void bbbss(double qberMin, double qberMax, double refinement, int longitud){

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
            //std::cout << "********* QBER = " << qber << "********" <<std::endl;  
            reiniciarContadorParidad();
            std::tuple<std::string, std::string> init_state = generacionCondicionesIniciales(qber, longitud);
            cadenaAlice = std::get<0>(init_state);
            cadenaBob = std::get<1>(init_state);
            limiteShannon = (-1)*qber*log2(qber) + (-1)*(1-qber)*log2(1-qber);

            //Reseteamos iteracion a 0
            int iter_number = 0;
            do {
                std::tuple<std::string, int> iter_result = iteracion_bbbss(cadenaAlice, cadenaBob, qber, iter_number);
                cadenaBob = std::get<0>(iter_result);
                lenk = std::get<1>(iter_result);
                iter_number++;
                //std::cout << "Bits expuestos en la iteracion " << iter_number << " (sumatorio): " << obtenerContadorParidad() << std::endl; 
            } while (lenk < cadenaAlice.size()/4);

            //¿EXITO EN LA RECONCILIACION?
            //std::cout << std::endl;    
            int res = compararCadenas(cadenaAlice, cadenaBob);
            //std::cout << "****************" << std::endl;
            if (res == 0) {
                //std::cout << "RECONCILIACION = YES" << std::endl;
                //DATA STUDY
                double bitsExpuestosTotales = obtenerContadorParidad();
                bitExpuestos.push_back(bitsExpuestosTotales);
                double eficienciaReconciliacionValue = bitsExpuestosTotales/(cadenaAlice.size()*limiteShannon);
                eficienciaReconciliacion.push_back(eficienciaReconciliacionValue);
                double tasaGeneracionValue = 1 - (1 + eficienciaReconciliacionValue)*limiteShannon;
                tasaGeneracionClaves.push_back(tasaGeneracionValue);
                //std::cout << "Limite de Shannon" << " " << limiteShannon  << std::endl;
                // int iter = 0;
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
    // hacer_grafica(qberVec, bitExpuestos, L"Bits Expuestos", L"QBER", L"Bits Expuestos totales", "bbbss_QBER.png");
    // hacer_grafica(qberVec, eficienciaReconciliacion, L"Eficiencia Reconciliacion", L"QBER", L"f", "bbbss_eficiencia.png");
    // hacer_grafica(qberVec, tasaGeneracionClaves, L"Tasa de Generacion de Claves Seguras", L"QBER", L"SKR(bps)", "bbbss_tasaClaves.png");
    export_to_csv(qberVec, bitExpuestos, "/home/alberto/Documentos/bbbss/figures/bitsexpuestos.csv");
    export_to_csv(qberVec, eficienciaReconciliacion, "/home/alberto/Documentos/bbbss/figures/eficiencia.csv");
    export_to_csv(qberVec, tasaGeneracionClaves, "/home/alberto/Documentos/bbbss/figures/tasa.csv");
}