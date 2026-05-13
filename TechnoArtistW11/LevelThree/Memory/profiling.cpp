#include <iostream>
#include <vector>

// gprof
// Valgrind

class BaseDatos {
	std::vector<std::vector<double>> datos;

public:
	void insertarDatos(std::vector<double> registro) {
		datos.push_back(std::move(registro));
	}
};

void testProfiling() {
	std::unique_ptr<BaseDatos> bd = std::make_unique<BaseDatos>();

	std::vector<double> fuenteDatos(10000, 2.2);

	bd->insertarDatos(fuenteDatos);
}
