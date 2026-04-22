#include <iostream>
#include <thread>
#include <future>

void funcionSecundaria(std::promise<int> promesa) {
	std::cout << "Ejecutando funcion en hilo secundario... " << std::endl;

	for (int i = 0; i < 5; i++) {
		std::cout << "Hilo secundario calculando... " << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	

	promesa.set_value(22);

	std::cout << "Terminando hilo secundario... " << std::endl;

}

void testFuturePromise() {
	std::promise<int> promesa;
	std::future<int> futuro = promesa.get_future();

	std::jthread hilo2(funcionSecundaria, std::move(promesa));

	std::cout << "Hilo 1 comienza trabajo..." << std::endl;

	while (futuro.wait_for(std::chrono::seconds(1)) != std::future_status::ready) {

		std::cout << "Hilo 1 sigue trabajando..." << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(3));

	}

	int resultadoHilo2 = futuro.get();

	std::cout << "Resultado del hilo 2: " << resultadoHilo2 << std::endl;
}