#include <iostream>
#include <thread>
#include <mutex>

struct Cubierto {
	std::mutex mtx;
	std::string nombre;

	Cubierto(std::string s) : nombre(s) {}
};

void testDeadlock() {
	Cubierto cuchillo("Cuchillo");
	Cubierto tenedor("Tenedor");

	std::jthread persona1([&]() {
		std::scoped_lock<std::mutex, std::mutex> lock1(cuchillo.mtx, tenedor.mtx);

		std::cout << "Persona 1 obtuvo cubiertos" << std::endl;

		//std::this_thread::sleep_for(std::chrono::seconds(1));

		});

	std::jthread persona2([&]() {
		std::scoped_lock<std::mutex, std::mutex> lock1(tenedor.mtx, cuchillo.mtx);

		std::cout << "Persona 2 obtuvo cubiertos" << std::endl;

		//std::this_thread::sleep_for(std::chrono::seconds(1));

		});
}