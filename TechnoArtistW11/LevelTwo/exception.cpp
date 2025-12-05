#include <iostream>
#include <vector>
#include <exception>

namespace Excepciones {
	class MyClass {
	public:
		MyClass() {
			std::cout << "Construyendo objeto" << std::endl;
		}
		~MyClass() {
			std::cout << "Destruyendo objeto" << std::endl;
		}
	};

	class IndiceNegativo: public std::exception {
	public:
		const char* what() const noexcept override {
			return "Indice de acceso negativo";
		}
	};

}
using namespace Excepciones;

int obtenerValorVector(int indice) {
	std::vector<int> vec = {1, 0, 3};
	int valor = 0;

	if (indice < 0) {
		throw IndiceNegativo();
	}

	try {
		valor = vec.at(indice);
	}
	catch (const std::out_of_range& e) {
		throw;
	}

	return valor;
}

void testException() {
	try {
		std::cout << obtenerValorVector(-1) << std::endl;

		std::cout << "Codigo adicional" << std::endl;

	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (const IndiceNegativo& e) {
		std::cerr << e.what() << std::endl;

	}
	catch (...) {
		std::cerr << "Excepcion desconocida" << std::endl;
	}

	std::cout << "Programa ha finalizado" << std::endl;

}
