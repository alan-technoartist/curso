#include <forward_list>
#include <iostream>

void testForwardIterator() {
	// lista ligada simple
	std::forward_list<int> listaSimple = { 2, 4, 6, 11 };

	// iterador forward (solo hacia adelante)
	auto iterador = listaSimple.begin();

	// leer el dato apuntado
	std::cout << "Primer elemento: " << *iterador << std::endl;

	// avanzar en la lista
	++iterador;

	// escribir a la casilla apuntada
	*iterador = 15;

	while (iterador != listaSimple.end()) {
		std::cout << *iterador << std::endl;
		++iterador;
	}
}
