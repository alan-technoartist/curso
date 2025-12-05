#include <iostream>

class CuentaBancaria {
private:
	std::string titular;
	double saldo;

public:
	// Construtor default
	CuentaBancaria() {
		std::cout << "Inicializando cuenta con valores default..." << std::endl;
		this->saldo = 0;
	}

	CuentaBancaria(std::string titular, double saldoInicial) {
		std::cout << "Inicializando cuenta con valores del usuario..." << std::endl;

		this->titular = titular;
		this->saldo = saldoInicial;
	}

	// Destructor
	~CuentaBancaria() {
		std::cout << "Objeto destruido" << std::endl;
	}

	void retirar(double monto) {
		if (saldo > monto)
			this->saldo -= monto;
		else
			std::cout << "Saldo insuficiente para retirar " << monto << std::endl;
	}

	void depositar(double monto) {
		this->saldo += monto;
	}

	double consultarSaldo() {
		return this->saldo;
	}
};

void basicClass() {
	CuentaBancaria cuenta;
	CuentaBancaria cuenta2("Alan", 10.0);

	double saldoCuenta;

	cuenta2.depositar(20.3);
	cuenta2.retirar(50.1);

	saldoCuenta = cuenta2.consultarSaldo();
	
	std::cout << "El saldo es: $" << saldoCuenta << std::endl;
}
