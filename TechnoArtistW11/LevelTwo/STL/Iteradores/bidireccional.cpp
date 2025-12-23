#include <iostream>
#include <list>

void testBidireccional() {
	std::list<std::string> lista = { "Cuadro1", "Cuadro2", "Cuadro3" };

	// iterador bidireccional
	//std::list<std::string>::iterator it = lista.begin();
	auto it = lista.begin();

	std::cout << *it << std::endl;

	// avanzar iterador
	++it;

	// acceder al elemento actual
	std::cout << *it << std::endl;

	// retroceder iterador
	--it;

	// acceder al elemento actual
	std::cout << *it << std::endl;

	// recorrer lista
	while (it != lista.end()) {
		std::cout << *it << std::endl;
		++it;
	}
}