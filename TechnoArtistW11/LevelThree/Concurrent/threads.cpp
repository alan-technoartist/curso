#include <iostream>
#include <thread>

void funcionHilo(std::stop_token stop) {

	while (!stop.stop_requested()) {
		std::cout << "Ejecutando desde hilo secundario" << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	}
	std::cout << "Hilo secundario termina" << std::endl;

}

void testThread() {
	std::cout << "Lanzando hilo secundario" << std::endl;

	// Objeto RAII
	std::jthread hilo1(funcionHilo);

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	std::cout << "Fin de función, objeto hilo1 saliendo de ámbito..." << std::endl;
}