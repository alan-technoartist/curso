#include <iostream>
#include <sstream>
#include <vector>
#include <array>

#include "Generic/templates.hpp"
#include "Generic/concepts.hpp"

void testTemplates() {
	//std::cout << maximo(3, 2) << std::endl;
	//std::cout << maximo(4.5, 2.1) << std::endl;
	//std::cout << maximo("4.55", "2.1f") << std::endl;

	//std::cout << concatenar(2.9, 2.1) << std::endl;
	//std::cout << concatenar(5, 2.9f) << std::endl;
	//std::cout << concatenar("5.2", 2) << std::endl;
	//std::cout << concatenar("5.2", "2") << std::endl;

	//Contenedor<int> contenedor1(9);
	//Contenedor<std::string> contenedor2("texto");

	//Par<int, std::string> par(1, "Hola");

	//par.primero = 1;
	//par.segundo = "";

	//Pila<int> pilaEnteros;

	/*try {

		pilaEnteros.push(3);
		pilaEnteros.push(2);
		pilaEnteros.push(4);

		std::cout << pilaEnteros.top() << std::endl;

		pilaEnteros.pop();

		std::cout << pilaEnteros.top() << std::endl;

		pilaEnteros.pop();

		std::cout << pilaEnteros.top() << std::endl;

		pilaEnteros.pop();
		pilaEnteros.pop();

		std::cout << "Finalizo procesamiento de pila" << std::endl;

	}
	catch (const std::runtime_error& e) {
		std::cout << "runtime_error: " << e.what() << std::endl;
	}

	Arreglo<std::string, 4> arr;

	std::cout << "Programa terminado" << std::endl;*/

	/*Mostrar<std::string> mostrar;
	mostrar.imprimir("Hola");
	mostrar.imprimir(std::string("Hola"));

	Mostrar<bool> mostrarBool;
	mostrarBool.imprimir(true);

	std::vector<int> vector = { 2, 4, 5, 0 };

	Mostrar<std::vector<int>> mostrarVector;

	mostrarVector.imprimir(vector);*/

	//Arreglo<std::string, 5> arreglo;

	//arreglo.fill("3");
	//arreglo.print();

	//std::cout << sumarNumeros(1.0f, "1") << std::endl;

	//Arreglo<int, 4> variable = { 1, 3, 4, 3 };

	//variable.print();

	//imprimeTamano(variable);

	std::cout << algoritmoGenerico(2, 5) << std::endl;
	std::cout << menor(2.0, 1.0) << std::endl;

	imprimirCaracter();
}