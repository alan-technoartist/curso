#include <iostream>

class InterfazObjetivo {
public:
	void llamarSistemaObjetivo() {

	}
};

class Adaptador : public InterfazObjetivo {
public:
	void adaptarLlamada() {
		// ...
		llamarSistemaObjetivo();
	}
};

class InterfazActual {
private:
	Adaptador adaptador;

public:
	void llamarSistema() {
		adaptador.adaptarLlamada();
	}
};

void testAdapter() {
	InterfazActual iActual;

	iActual.llamarSistema();
}