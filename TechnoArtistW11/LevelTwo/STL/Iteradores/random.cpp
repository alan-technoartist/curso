#include <iostream>
#include <vector>

void testRandomIterator() {
	std::vector<int> vec = { 1, 45, 4, 6, 81, 13 };

	// iterador acceso aleatorio
	auto it = vec.begin();

	// leer elemento actual
	std::cout << *it << std::endl;

	// saltar iterador
	it = it + 3;

	// asignar elemento actual
	*it = 10;

	std::cout << "Elemento actual: " << *it << std::endl;

	// acceso por vista (no mueve el iterador)
	std::cout << "Elemento anterior: " << it[-1] << std::endl;

	// asignacion por vista (no mueve el iterador)
	it[-1] = 0;

	std::cout << "Elemento actual: " << *it << std::endl;

	std::cout << "Elemento anterior: " << it[-1] << std::endl;

	auto it_final = vec.end();

	// aritmetica (calculo de distancias)
	int distancia = it_final - it;

	std::cout << "Distancia al final del contenedor: " << distancia << std::endl;

	// comparacion logica
	if (it > vec.begin()) {
		std::cout << "Iterador ha avanzado" << std::endl;
	}

}