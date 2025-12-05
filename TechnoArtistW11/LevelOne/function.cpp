#include <vector>
#include <array>
#include <iostream>

enum class estado {
	ON,
	OFF
};

/* Busca el valor val en el vector data y regresa la primer ocurrencia */
int busqueda(std::vector<int> data, int val) {

	for (int i = 0; i < data.size(); i++) {
		if (val == data.at(i)) {
			return i;
		}
	}
	return -1;

}

/* Busca el valor val y regresa true si lo encuentra, false en caso contrario*/
bool busqueda(std::array<estado,3> data, estado val) {

	for (int i = 0; i < data.size(); i++) {
		if (val == data.at(i)) {
			return true;
		}
	}

	return false;
}

void imprimirCadena(std::string cadena) {
	std::cout << cadena << std::endl;

}

int multiplicar(int a, int b) {
	int resultado = a * b;

	return resultado;
}