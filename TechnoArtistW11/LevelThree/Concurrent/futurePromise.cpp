#include <iostream>
#include <thread>
#include <future>
#include <numeric>

void testFuturePromise() {
	std::vector<double> datos = { 1.4, 2.5, 3.3 };

	auto promedioDatos = std::async(std::launch::deferred, [&datos]() {
		
		double sumaDatos = std::accumulate(datos.begin(), datos.end(), 0.0);
		double promedioDatos = sumaDatos / static_cast<double>(datos.size());

		return promedioDatos;

		});

	std::cout << "Hilo principal sigue trabajando" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "Resultado: " << promedioDatos.get() << std::endl;
}