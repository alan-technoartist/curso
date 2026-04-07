#include <iostream>
#include <stack>

class IComando {
public:
	virtual ~IComando() = default;

	virtual void ejecutar() = 0;
	virtual void revertir() = 0;
};

class ComandoEscribir : public IComando {
	void ejecutar() override {

	}

	void revertir() override {

	}
};

// Receptor
class Documento {
	std::string texto;

	void escribir() {

	}
	void borrar(int numCaracteres) {

	}
};

// Invocador
class Editor {
	std::stack<std::shared_ptr<IComando>> comandos;

};

void testCommand() {

}