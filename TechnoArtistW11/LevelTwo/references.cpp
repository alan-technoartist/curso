#include <iostream>
#include <vector>

class estructuraBasica {
public:
	std::string cadena;
	double numero;
};


estructuraBasica estructuraGlobal; // almacenada en area global

void refs() {
	estructuraBasica estructura; // almacenada en stack (temporal)
	estructuraBasica* estructuraDinamica = new estructuraBasica; // almacenada en heap
	auto estructuraDinamica2 = std::make_shared<estructuraBasica>(); // almacenada en heap

}
