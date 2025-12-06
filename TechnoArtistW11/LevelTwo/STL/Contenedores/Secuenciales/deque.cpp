#include <iostream>
#include <deque>

enum class Prioridad {
	NORMAL,
	ALTA
};

class Proceso {
public:
	int pid; // id del proceso
	std::string nombre;
	Prioridad prioridad;

	void ejecutar() {
		std::cout << "Ejecutando proceso " << this->pid << std::endl;
	}
};

class Planificador {
private:
	std::deque<Proceso> colaProcesos;
public:
	void agendarProceso(Proceso& proceso) {
		if (proceso.prioridad == Prioridad::NORMAL) {
			colaProcesos.push_back(proceso);
		}
		else if (proceso.prioridad == Prioridad::ALTA) {
			colaProcesos.push_front(proceso);
		}
	}

	void despachar() {
		while (!colaProcesos.empty()) {
			Proceso p = colaProcesos.front();
			p.ejecutar();
			colaProcesos.pop_front();
		}
	}
};

void testDeque() {
	Planificador planificador;

	Proceso proceso1;
	proceso1.pid = 1;
	proceso1.prioridad = Prioridad::NORMAL;
	proceso1.nombre = "Navegador de internet";

	Proceso proceso2;
	proceso2.pid = 2;
	proceso2.prioridad = Prioridad::ALTA;
	proceso2.nombre = "Lectura de disco";

	Proceso proceso3;
	proceso3.pid = 3;
	proceso3.prioridad = Prioridad::NORMAL;
	proceso3.nombre = "Monitor del sistema";

	planificador.agendarProceso(proceso1);
	planificador.agendarProceso(proceso2);
	planificador.agendarProceso(proceso3);

	planificador.despachar();
}