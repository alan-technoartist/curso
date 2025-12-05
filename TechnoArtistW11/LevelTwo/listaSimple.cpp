#include <iostream>
#include <memory>

struct Nodo {
	std::string nombre;
	int edad;

	std::unique_ptr<Nodo> sig;
};

class ListaSimple {
public:
	std::unique_ptr<Nodo> head;

	ListaSimple() : head(nullptr) {
	}
	~ListaSimple() {

	}

	void imprimirLista(void) {
		Nodo* iterador = head.get();

		while (iterador != nullptr) {
			std::cout << iterador->nombre << " " << iterador->edad << std::endl;
			iterador = iterador->sig.get();
		}
	}

	void agregarNodo(const std::string nuevoNombre, const int nuevaEdad) {
		std::unique_ptr<Nodo> nuevo = std::make_unique<Nodo>();	
		nuevo->edad = nuevaEdad;
		nuevo->nombre = nuevoNombre;
		nuevo->sig = nullptr;

		if (head != nullptr) {
			// existe al menos un nodo en la lista
			nuevo->sig = std::move(head);
		}
		head = std::move(nuevo);

	}
};

void listaSimple(void) {
	ListaSimple lista;

	lista.agregarNodo("Alan", 15);
	lista.agregarNodo("Julian", 5);
	lista.imprimirLista();
	//lista.agregarNodo(nuevoNodo);
	//lista.imprimirLista();

	// Crear un par de nodos
	// Imprimir lista
	// Agregar nuevo nodo
	// Imprimir lista
}