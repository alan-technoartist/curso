#include <iostream>
#include <memory>

namespace EstructurasDatos {

	struct Nodo {
		std::shared_ptr<Nodo> anterior;
		int dato;
		std::shared_ptr<Nodo> siguiente;
	};

	class ListaSimple {
	public:
		std::shared_ptr<Nodo> head;

		ListaSimple() : head(nullptr) {
		}

		void agregarNodo(int nuevoDato) {
			// Crear nodo e inicializarlo
			std::shared_ptr<Nodo> nuevo = std::make_shared<Nodo>();
			nuevo->dato = nuevoDato;
			nuevo->siguiente = nullptr;
			nuevo->anterior = nullptr;

			if (head == nullptr)
				head = nuevo;

			head->siguiente = nuevo;
			nuevo->anterior = head;

		}
	};
}
using namespace EstructurasDatos;

void operarListaSimple() {
	ListaSimple lista;

	lista.agregarNodo(5);
	//lista.agregarNodo(8);
}