#include <iostream>
#include <thread>
#include <mutex>

class Dispositivo {
private:
	std::mutex mtx;
	std::string nombre;

public:
	Dispositivo(std::string s) : nombre(s) {}

	std::mutex& getMutex() {
		return mtx;
	}
};

void tareaOficina(Dispositivo& escaner, Dispositivo& impresora, std::string nombrePersona) {
	std::cout << nombrePersona << "Va a ejectuar tareaOficina" << std::endl;

	std::scoped_lock<std::mutex, std::mutex> lock(escaner.getMutex(), impresora.getMutex());

	std::cout << nombrePersona << "Obtuvo los dispositivos" << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void testDeadlock() {
	Dispositivo escaner("Escaner");
	Dispositivo impresora("Impresora");

	std::jthread persona1(tareaOficina, std::ref(escaner), std::ref(impresora), "Alan");
	std::jthread persoan2(tareaOficina, std::ref(escaner), std::ref(impresora), "Armando");
}