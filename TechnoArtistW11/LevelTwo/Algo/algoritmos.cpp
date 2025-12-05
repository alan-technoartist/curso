#include <iostream>
#include <random>
#include "ordenamiento.hpp"

void generarEnteros(std::vector<int>& datos, int num) {

	// Fuente de entropía
	std::random_device semilla;

	// Motor de generación (Mersenne Twister)
	//std::mt19937 generador(semilla());
	std::mt19937 generador(21);

	// Distribución uniforme (rango: 1-1000)
	std::uniform_int_distribution distribucion(1, 1000);

	for (int i = 0; i < num; i++) {
		int aleatorio = distribucion(generador);
		datos.push_back(aleatorio);
	}
}

void imprimirVector(std::vector<int>& datos) {
	for (int& elemento : datos) {
		std::cout << elemento << " ";
	}
	std::cout << std::endl;
}

int busquedaBinaria(std::vector<int>& datos, int objetivo) {
	int izq = 0;
	int der = datos.size() - 1;

	do {
		int med = izq + (der - izq) / 2;

		if (objetivo == datos[med]) {
			return med;
		}

		if (objetivo < datos[med]) {
			// recorrer indice derecho
			der = med - 1;
		}
		else {
			// recorrer indice izquierdo
			izq = med + 1;
		}
	} while (izq <= der);

	if (datos[izq] == objetivo) {
		return izq;
	}

	return -1;

}

void testBusquedaBinaria() {
	std::vector<int> datos;

	generarEnteros(datos, 1000);

	int objetivo = 130;

	std::sort(datos.begin(), datos.end());

	imprimirVector(datos);

	int resultado = busquedaBinaria(datos, objetivo);

	if (resultado != -1) {
		std::cout << "Objetivo encontrado en: " << resultado << std::endl;
	}
	else {
		std::cout << "Objetivo no encontrado" << std::endl;
	}
}