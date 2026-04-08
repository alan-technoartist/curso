#include <iostream>
#include <stack>

// Comando abstracto
class IComando {
public:
	virtual ~IComando() = default;

	virtual void ejecutar() = 0;
	virtual void revertir() = 0;
};

// Receptor (implementa la lógica)
class Documento {
	std::string texto;

public:
	Documento() {
		texto = "";
	}

	void escribir(std::string& nuevoTexto) {
		texto += nuevoTexto;

		std::cout << texto << std::endl;
	}
	void borrar(int numCaracteres) {
		texto.erase(texto.size() - numCaracteres);

		std::cout << texto << std::endl;

	}
};

// Comando concreto
class ComandoEscribir : public IComando {
private:
	Documento& documento;
	std::string texto;

public:
	ComandoEscribir(Documento& d, std::string t) : documento(d), texto(t) {

	}

	void ejecutar() override {
		documento.escribir(texto);
	}

	void revertir() override {
		documento.borrar(texto.size());
	}
};

// Invocador (registra y lanza los comandos)
class Editor {
private:
	std::stack<std::shared_ptr<IComando>> historialComandos;
public:
	void ejecutarComando(std::shared_ptr<IComando> cmd) {
		cmd->ejecutar();
		historialComandos.push(cmd);
	}

	void deshacerUltimo() {
		(historialComandos.top())->revertir();
		historialComandos.pop();
	}

};

// Cliente
void testCommand() {
	// Invocador
	Editor editor;

	// Receptor
	Documento documento;

	// Comando concreto
	std::shared_ptr<IComando> comandoEscribir = std::make_shared<ComandoEscribir>(documento, "Hola");
	std::shared_ptr<IComando> comandoEscribir2 = std::make_shared<ComandoEscribir>(documento, "Mundo");


	editor.ejecutarComando(comandoEscribir);
	editor.ejecutarComando(comandoEscribir2);
	editor.deshacerUltimo();

}