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
	std::list<std::shared_ptr<IObserver>> observadores;

	void registrarSuscriptor(std::shared_ptr<IObserver> obs) {
		observadores.push_back(obs);
	}

	void desregistrarSuscriptor(std::shared_ptr<IObserver> obs) {

		observadores.remove_if([&obs](std::shared_ptr<IObserver> actual) {
			if (obs == actual)
				return true;
			return false;
		});
	}

	void notificarSuscriptores() {

		// Notificar observadores
		for (auto& observador : observadores) {
			observador->recibirNotificacion();
		}
	}
};

void testObserver() {
	Fuente fuente;

	std::shared_ptr<IObserver> observador1 = std::make_shared<ObservadorTipo1>();
	std::shared_ptr<IObserver> observador2 = std::make_shared<ObservadorTipo2>();

	fuente.registrarSuscriptor(observador1);

	fuente.registrarSuscriptor(observador2);

	fuente.notificarSuscriptores();

	fuente.desregistrarSuscriptor(observador1);

	fuente.notificarSuscriptores();

}