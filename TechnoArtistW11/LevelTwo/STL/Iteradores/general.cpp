#include <iostream>
#include <vector>

#include "iteradores.hpp"

void testIterator() {
	std::vector<int> arreglo = { 10, 23, 21 };

	for (auto iteradorArreglo = arreglo.begin(); iteradorArreglo != arreglo.end(); ++iteradorArreglo) {
		std::cout << *iteradorArreglo << std::endl;
	}

	for (auto elemento : arreglo) {
		std::cout << elemento << std::endl;
	}

}