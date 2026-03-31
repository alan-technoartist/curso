#include <iostream>
#include <list>

class IObserver {
public:
	long id;

	virtual ~IObserver() {}

	virtual void recibirNotificacion() = 0;
};

class ObservadorTipo1 : public IObserver {
public:
	void recibirNotificacion() override {
		std::cout << "Notificación recibida por observador 1!" << std::endl;
	}
};

class ObservadorTipo2 : public IObserver {
public:
	void recibirNotificacion() override {
		std::cout << "Notificación recibida por observador 2!" << std::endl;

	}
};

class Fuente {
public:
	std::list<IObserver*> observadores;

	void registrarSuscriptor(IObserver* o) {
		observadores.push_back(o);
	}

	void desregistrarSuscriptor() {
		//observadores.remove_if();
	}

	void notificarSuscriptores() {

		// Notificar observadores
		for (IObserver* observador : observadores) {
			observador->recibirNotificacion();
		}
	}
};

void testObserver() {
	Fuente fuente;

	ObservadorTipo1 observador1;
	ObservadorTipo2 observador2;

	fuente.registrarSuscriptor(&observador1);
	fuente.registrarSuscriptor(&observador2);

	fuente.notificarSuscriptores();

}