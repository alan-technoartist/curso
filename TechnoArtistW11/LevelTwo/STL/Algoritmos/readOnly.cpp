#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

struct Transaccion {
	int id;
	double monto;
	std::string estado;

	bool operator==(const Transaccion& t) {
		return (this->estado == t.estado);
	}
};

bool esCritico(const Transaccion& t) {
	return t.monto >= 10000;
}

void testAlgoritmosRO() {
	// Ejemplo: análisis de transacciones bancarias

	// Datos de prueba
	std::vector<Transaccion> transacciones = {
		{100, 800.0, "APROBADA"},
		{101, 1200.5, "EN TRANSITO"},
		{102, 1000, "RECHAZADA"},
		{103, 15000.5, "APROBADA"},
		{104, 100.4, "RECHAZADA"}
	};

	// Hay montos críticos?
	auto resultado = std::find_if(transacciones.begin(), transacciones.end(), esCritico);

	std::cout << "Transaccion critica: #" << resultado->id << ": $" << resultado->monto << std::endl;

	// Rechazos
	Transaccion tRechazada;
	tRechazada.estado = "RECHAZADA";

	resultado = std::find(transacciones.begin(), transacciones.end(), tRechazada);

	std::cout << "Transaccion rechazada: #" << resultado->id << std::endl;

	// Siguiente a revisar

	// Total

	// Mayor transacción

	// for_each
}