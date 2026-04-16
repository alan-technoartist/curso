#include <iostream>
#include <thread>
#include <mutex>


void testDeadlock() {

	std::mutex mutex1;
	std::mutex mutex2;

	std::jthread hilo1([&]() {
		std::lock_guard<std::mutex> lock1(mutex1);
		// Zona crítica aquí
		// ...

		std::lock_guard<std::mutex> lock2(mutex2);
		});

	std::jthread hilo2([&]() {
		std::lock_guard<std::mutex> lock1(mutex2);
		// Zona crítica aquí

		// ...

		std::lock_guard<std::mutex> lock2(mutex1);

		});
}