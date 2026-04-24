#include <iostream>
#include <thread>
#include <future>

int funcionSecundaria() {
	std::cout << "Ejecutando funcion en hilo secundario... " << std::endl;

	for (int i = 0; i < 5; i++) {
		std::cout << "Hilo secundario calculando... " << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	
	std::cout << "Terminando hilo secundario... " << std::endl;

	return 22;
}

void testFuturePromise() {
	// El objeto promise es manejado automáticamente por std::async
	auto resultado = std::async(std::launch::async, funcionSecundaria);

	std::cout << "Hilo 1 comienza trabajo..." << std::endl;

	while (resultado.wait_for(std::chrono::seconds(1)) != std::future_status::ready) {

		std::cout << "Hilo 1 sigue trabajando..." << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(3));

	}

	// get() bloquea al hilo actual
	int resultadoHilo2 = resultado.get();

	std::cout << "Resultado del hilo 2: " << resultadoHilo2 << std::endl;
}