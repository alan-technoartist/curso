#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void imprimirTexto(std::string texto) {

	// Objeto RAII
	std::unique_lock<std::mutex> lock(mtx);

	// Sección crítica
	for (auto c : texto) {
		std::cout << c;
	}

}

void testMutex() {

	std::jthread hilo1(imprimirTexto, "Hola");
	std::jthread hilo2(imprimirTexto, "Mundo");

	std::cout << "Fin de ambito de hilos" << std::endl;
}
