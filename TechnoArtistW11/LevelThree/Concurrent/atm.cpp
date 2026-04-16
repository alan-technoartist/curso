#include <iostream>
#include <thread>
#include <mutex>

namespace Hilos {
	class CuentaBancaria {
	private:
		float saldo = 100.0f;
		std::timed_mutex mtx;

	public:
		void retirar(float cantidad) {

			std::unique_lock<std::timed_mutex> lock(mtx, std::defer_lock);

			// Proceso fuera de la zona crítica
			std::cout << "Iniciando comunicación" << std::endl;

			if (lock.try_lock_for(std::chrono::seconds(3))) {

				// Zona crítica
				if (saldo >= cantidad) {
					std::cout << "Retirando " << cantidad << std::endl;
					std::this_thread::sleep_for(std::chrono::seconds(10));
					saldo -= cantidad;
				}
				else {
					std::cout << "Saldo insuficiente " << this->saldo << std::endl;
				}
				// Fin de zona crítica

				lock.unlock();

				std::cout << "Imprimiendo recibo..." << std::endl;
			}
			else {
				std::cout << "Sistema no respondió en 3 segundos" << std::endl;
			}
		}
		void verSaldo() const {
			std::cout << "Saldo: " << this->saldo << std::endl;
		}
	};
}

using namespace Hilos;

void testAtm() {
	CuentaBancaria cuenta;

	std::jthread procesoB([]() {
		std::cout << "Proceso ejecutandose en background" << std::endl;
	});

	std::jthread cliente1(&CuentaBancaria::retirar, &cuenta, 50.0f);
	std::jthread cliente2(&CuentaBancaria::retirar, &cuenta, 10.0f);
	std::jthread cliente3(&CuentaBancaria::retirar, &cuenta, 10.0f);
	std::jthread cliente4(&CuentaBancaria::retirar, &cuenta, 10.0f);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	cuenta.verSaldo();
}