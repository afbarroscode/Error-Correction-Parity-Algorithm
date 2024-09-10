#include "header.h"

using namespace std;

void shannon(){
	std::vector<double> qberVec = construirVector(0.01, 0.1, 0.0001);
	std::vector<double> LSHannon;
	for(double qber : qberVec){
		LSHannon.push_back((-1)*qber*log2(qber) + (-1)*(1-qber)*log2(1-qber));
	}
	hacer_grafica(qberVec, LSHannon, L"Entropía de Shannon binaria", L"QBER", L"h(QBER)", "entropia_shannon.png");
}