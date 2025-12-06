#include <iostream>
#include <vector>
#include <map>

struct Transaccion {
	std::string categoria; // llave
	float monto;
};

void testMap() {
	std::vector<Transaccion> transacciones = {
		{ "Alimentos", 19.4f },
		{ "Transporte", 5.5f },
		{ "Ocio", 30.0f },
		{ "Alimentos", 15.0f },
		{ "Ocio", 45.0f },
	};

	std::map<std::string, float> resumenGastos;
	float totalGastos = 0.0f;

	// procesar datos (vector => mapa)
	for (const auto& t : transacciones) {
		resumenGastos[t.categoria] += t.monto;
		totalGastos += t.monto;
	}

	std::cout << "Categoria\t Monto" << std::endl;
	for (const auto& gasto : resumenGastos) {
		std::cout << gasto.first << "\t" << gasto.second << std::endl;
	}

	std::cout << "Gasto total: " << totalGastos << std::endl;
}