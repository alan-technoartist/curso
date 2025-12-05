#include <iostream>
#include <vector>

// Funcion para calcular el maximo de dos valores
// std::max()
template <typename T>
T maximo(T a, T b) {
	return (a >= b) ? a : b;
}

// Funcion para concatenar dos elementos genericos
template <typename T1, typename T2>
std::string concatenar(T1 a, T2 b) {
	std::ostringstream oss;

	oss << a;
	oss << b;

	return oss.str();
}

// Ejemplo de template de clase
template <typename T>
class Contenedor {
private:
	T dato;

public:
	Contenedor(T d) : dato(d) {}

	T obtenerDato() {
		return dato;
	}
};

//std::pair
template <typename T1, typename T2>
class Par {
public:
	T1 primero;
	T2 segundo;

	Par(T1 p, T2 s) : primero(p), segundo(s) {

	}
};

// std::stack
template <typename T>
class Pila {
private:
	std::vector<T> datos;
public:
	// Remover elemento del tope
	void pop() {
		if (!datos.empty())
			datos.pop_back();
		else
			throw std::runtime_error("Vector vacio");
	}
	// Insertar elemento del tope
	void push(T dato) {
		datos.push_back(dato);
	}
	// Obtener elemento del tope
	T top() {
		return datos.back();
	}
};

template <typename T>
class Mostrar {
public:
	void imprimir(T dato) {
		std::cout << dato << std::endl;
	}
};

template <>
class Mostrar<bool> {
public:
	void imprimir(bool dato) {
		std::cout << ((dato) ? "Verdadero" : "Falso") << std::endl;
	}
};

template <>
class Mostrar<std::vector<int>> {
public:
	void imprimir(const std::vector<int>& dato) {
		for (auto elemento : dato) {
			std::cout << elemento << " ";
		}
		std::cout << std::endl;
	}
};

// std::array<>
template<typename T, int N>
class Arreglo {
private:
	T datos[N];
public:
	Arreglo(std::initializer_list<int> il) {
		int i = 0;
		for (auto e : il) {
			datos[i++] = e;
		}
	}

	// Acceso seguro
	T& at(int indice) {
		if (indice < 0 || indice >= N) {
			throw std::out_of_range("Indice fuera de rango");
		}

		return datos[indice];
	}

	// Acceso rapido
	T& operator[](int indice) {
		return datos[indice];
	}

	// Tamano
	float size() const {
		return 0.1f;
	}

	// Llenar
	void fill(T valor) {
		for (auto& elemento : datos) {
			elemento = valor;
		}
	}

	// Imprimir
	void print() const {
		for (auto& elemento : datos) {
			std::cout << elemento << " ";
		}
		std::cout << std::endl;
	}
};

 