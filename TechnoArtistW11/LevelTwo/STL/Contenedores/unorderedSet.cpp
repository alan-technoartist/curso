#include <iostream>
#include <unordered_set>

void testUnorderedSet() {
	// Hash set
	std::unordered_set<std::string> cuponesUsados;

	cuponesUsados.insert("CUPON1234");
	cuponesUsados.insert("CUPON8FE4");
	cuponesUsados.insert("CUPON1DF4");

	for (const auto& cupon : cuponesUsados) {
		std::cout << cupon << std::endl;
	}

	std::string cuponUsuario = "CUPON1249";

	// Operacion eficiente O(1)
	auto resultado = cuponesUsados.count(cuponUsuario);

	if (resultado == 1) {
		std::cout << "Cupon ya fue utilizado" << std::endl;
	}
	else {
		std::cout << "Cupon " << cuponUsuario << " aplicado" << std::endl;
		cuponesUsados.insert(cuponUsuario);
	}

	for (const auto& cupon : cuponesUsados) {
		std::cout << cupon << std::endl;
	}
}