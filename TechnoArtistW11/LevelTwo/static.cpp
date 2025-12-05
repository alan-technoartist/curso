#include <iostream>

class MiClase {
public:
	std::string cadena;
	static int estatico;
	int miembro;

	MiClase() {
	}

	int incrementarEntero() {
		static int entero = 0;

		entero += 1;

		return entero;
	}

	static void metodo() {
		std::cout << "Ejecutando metodo" << std::endl;
	}
};

class Matematica {
public:
	static int sumar() {

	}
	static int multiplicar() {

	}
};

void staticExample() {
	MiClase instancia;
	MiClase instancia2;

	std::cout << instancia.incrementarEntero() << std::endl;

	std::cout << instancia2.incrementarEntero() << std::endl;

	//MiClase::metodo();
	//MiClase::estatico = 0;
}