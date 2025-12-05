#include <iostream>
#include <vector>
#include <exception>

class ExcepcionMenorCero : public std::exception {
private:
	std::string detalleInterno;
public:
	ExcepcionMenorCero(const char* detalle) {
		detalleInterno = detalle;
	}

	const char* what() const noexcept override {
		return detalleInterno.c_str();
	}

};

class MyClass2 {
public:
	MyClass2() {
		std::cout << "Construyendo MyClass" << std::endl;
	}
	~MyClass2() {
		std::cout << "Destruyendo MyClass" << std::endl;
	}
	// ...
};

int leerVector(int indice) {
	std::vector<int> vect = { 4, 1, 0, 1 };

	if (indice >= static_cast<int>(vect.size())) {
		throw std::out_of_range("Indice igual o mayor al tamano del arreglo");
	}
	if (indice < 0) {
		throw ExcepcionMenorCero("Indice menor a cero");
	}

	std::cout << "Terminando leeerVector" << std::endl;

	return vect[indice];
}

int calcularValor(int indice) {
	int v = 0;

	std::unique_ptr<MyClass2> myClass = std::make_unique<MyClass2>();

	// myClass->

	try {
		v = leerVector(indice);

	}
	catch (const std::out_of_range& e) {
		throw;
	}
	catch (const ExcepcionMenorCero& e) {
		throw;
	}

	std::cout << "Terminando calcularValor" << std::endl;

	return v + 1;
}

void pruebaExcepciones() {

	try {
		int resultado = calcularValor(-1);
		resultado += 2;

		std::cout << resultado << std::endl;

	}
	catch (const std::out_of_range& e) {
		std::cout << "Excepcion std::out_of_range en funcion principal " << e.what() << std::endl;
	}
	catch (const ExcepcionMenorCero& e) {
		std::cout << "ExcepcionMenorCero en funcion principal " << e.what() << std::endl;
	}

	std::cout << "Terminando pruebaExcepciones" << std::endl;

}