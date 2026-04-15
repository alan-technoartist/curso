#include <iostream>
#include <thread>
#include <mutex>

namespace Hilos {
	class CuentaBancaria {
	private:
		float saldo = 100.0f;
		std::mutex mtx;

	public:
		void retirar(float cantidad) {

			std::lock_guard<std::mutex> guard(mtx);

			// Zona crítica
			if (saldo >= cantidad) {
				std::cout << "Retirando..." << std::endl;
				saldo -= cantidad;
			}
			else {
				std::cout << "Saldo insuficiente" << std::endl;
			}
			// Fin de zona crítica


		}
		void verSaldo() const {
			std::cout << "Saldo: " << this->saldo << std::endl;
		}
	};
}

using namespace Hilos;

void testAtm() {
	CuentaBancaria cuenta;

	std::jthread cliente1(&CuentaBancaria::retirar, &cuenta, 100.0f);
	std::jthread cliente2(&CuentaBancaria::retirar, &cuenta, 100.0f);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	cuenta.verSaldo();
}