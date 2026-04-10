#include <iostream>
#include <thread>

void funcionHilo(std::stop_token stop) {

	while (!stop.stop_requested()) {
		std::cout << "Ejecutando desde hilo secundario" << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	}
	std::cout << "Hilo secundario termina" << std::endl;

}

void testThread() {
	std::cout << "Ejecutando hilo principal" << std::endl;

	for (int i = 0; i < 5; i++) {
		std::jthread hilo1(funcionHilo);

		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
	
	std::cout << "Hilo principal termina" << std::endl;
}