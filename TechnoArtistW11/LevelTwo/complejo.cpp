#include <iostream>
class NumComplejo {
public:
	double real;
	double imaginaria;

	NumComplejo() {

	}

	NumComplejo(double r, double i) : real(r), imaginaria(i) {

	}

	NumComplejo operator+(const NumComplejo& n) {
		NumComplejo temp;
		temp.real = this->real + n.real;
		temp.imaginaria = this->imaginaria + n.imaginaria;

		return temp;
	}

};

void numerosComplejos() {
	NumComplejo num1(1.3, 2.1);
	NumComplejo num2(2.4, 1.1);

	NumComplejo num3 = num1 + num2;
					// num1.operator+(num2);

	std::cout << num3.real << " " << num3.imaginaria << std::endl;

}