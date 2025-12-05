#include <iostream>

class Complejo {
public:
	double real;
	double imaginario;

	Complejo() : real(0.0), imaginario(0.0) {

	}

	Complejo(double r, double i) : real(r), imaginario(i) {

	}

	Complejo operator+(const Complejo& c) {
		Complejo resultado;
		resultado.real = this->real + c.real;
		resultado.imaginario = this->imaginario + c.imaginario;

		return resultado;
	}

};

std::ostream& operator<<(std::ostream& os, const Complejo& c) {

	return (std::cout << c.real << " + " << c.imaginario << "i");

}

void operatorOverload() {
	Complejo a(1.0, 2.9);
	Complejo b(2.2, 1);

	Complejo c = a + b; // a + b

	std::cout << c << " es un numero complejo" << std::endl;


}