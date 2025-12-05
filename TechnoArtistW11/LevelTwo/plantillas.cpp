#include <iostream>
#include <sstream>
#include <vector>

class ClasePrueba {
	int c;

	bool operator>(ClasePrueba b) {
		return (this->c > b.c) ? true : false;
	}
};

// std::max()
template <typename T, typename U>
T maximo(T a, U b) {
	return (a > b) ? a : b;
}

template <typename T>
T suma(T a, T b) {
	return a + b;
}

template <typename T, typename U>
std::string concatenarElementos(T a, U b) {
	std::ostringstream oss;

	oss << a << b;

	return oss.str();
}

template <typename T>
class ContenedorSimple {
private:
	T datoPrivado;
public:
	ContenedorSimple(T dato) : datoPrivado(dato) { }

	T obtenerDato() const {
		return datoPrivado;
	}

	void escribirDato(T nuevoDato) {
		datoPrivado = nuevoDato;
	}
};

// std::pair<>
template <typename U, typename V>
class Par {
public:
	U primero;
	V segundo;

	Par (U p, V s) : primero(p), segundo(s) {}

};

template <typename T>
class Mostrar {
public:
	void imprimir(T datos) {
		std::cout << datos << std::endl;
	}
};

template <>
class Mostrar<bool> {
public:
	void imprimir(bool datos) {
		std::cout << ((datos) ? "true" : "false") << std::endl;
	}
};

template <>
class Mostrar<std::vector<int>> {
public:
	void imprimir(std::vector<int> datos) {
		for (int elemento : datos) {
			std::cout << elemento << " ";
		}
		std::cout << std::endl;
	}
};

// std::stack
template <typename T>
class Pila {
private:
	std::vector<T> datos;
public:
	void push(T elemento) {
		datos.push_back(elemento);
	}

	void pop() {
		if (datos.empty())
			throw std::runtime_error("Estructura esta vacia");

		datos.pop_back();
	}

	T top() {
		return datos.back();
	}
};


// std::array
template <typename T, int N>
class Arreglo {
private:
	T datos[N];

public:
	T at(int indice) {

		if (indice >= N) {
			throw std::out_of_range("Indice fuera de rango");
		}

		return datos[indice];
	}

	// []
	// print()
	// fill()
	// size()
	// empty()
};

void pruebaPlantillas() {
	Pila<int> pilaEnteros;
	Pila<ContenedorSimple<int>> pilaContenedor;

	Arreglo<int, 10> arreglo;

	//arreglo.at(4);
	//arreglo[4];


	try {
		pilaEnteros.push(3);
		pilaEnteros.push(1);
		pilaEnteros.push(4);

		std::cout << pilaEnteros.top() << std::endl;

		pilaEnteros.pop();

		std::cout << pilaEnteros.top() << std::endl;

		pilaEnteros.pop();
		pilaEnteros.pop();
		pilaEnteros.pop();
	}
	catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}

}