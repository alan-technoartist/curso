#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

void testOutput() {

	// iterador de salida
	std::ostream_iterator<int> iterador(std::cout);

	std::vector<int> vect = { 2, 5, 62 };

	for (auto v : vect) {
		*iterador = v;
		++iterador;
	}
}

void testInput() {
	const std::string texto = "hola mundo !";

	std::istringstream flujoEntrada(texto);

	// iterador de entrada
	std::istream_iterator<std::string> iterador(flujoEntrada);
	std::istream_iterator<std::string> fin;

	std::cout << "Palabra: " << *iterador << std::endl;

	++iterador;

	std::cout << "Palabra: " << *iterador << std::endl;

	while (iterador != fin) {
		std::cout << *iterador << std::endl;
		++iterador;
	}
}

void testInputOutputIterator() {
	//testInput();
	testOutput();

}