#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void imprimirTexto(std::string texto) {

	mtx.lock();

	// Sección crítica
	for (auto c : texto) {
		std::cout << c;
	}

	throw;

	mtx.unlock();

}

void testMutex() {

	std::jthread hilo1(imprimirTexto, "Hola");
	std::jthread hilo2(imprimirTexto, "Mundo");
}
