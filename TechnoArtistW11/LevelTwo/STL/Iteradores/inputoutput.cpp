#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

void testOutput() {

	// iterador de salida (output)
	std::ostream_iterator<int> iterador(std::cout);

	std::vector<int> vect = { 2, 5, 62 };

	for (auto v : vect) {
		// escribir a la posicion actual 
		// equivale a std::cout << v
		*iterador = v;

		// avanzar a la siguiente posicion
		++iterador;
	}
}

void testInput() {
	const std::string texto = "hola mundo !";

	std::istringstream flujoEntrada(texto);

	// iterador de entrada (input)
	std::istream_iterator<std::string> iterador(flujoEntrada);
	std::istream_iterator<std::string> fin;

	// Acceso al elemento actual
	std::cout << "Palabra: " << *iterador << std::endl;

	// leer siguiente elemento
	++iterador;

	// Acceso al elemento actual
	std::cout << "Palabra: " << *iterador << std::endl;

	// Recorrer flujo
	while (iterador != fin) {
		std::cout << *iterador << std::endl;
		++iterador;
	}
}

void testInputOutputIterator() {
	//testInput();
	testOutput();

}