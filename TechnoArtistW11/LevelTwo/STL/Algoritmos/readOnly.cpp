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

void testAlgoritmosRO() {
	// Ejemplo: análisis de transacciones bancarias

	// Datos de prueba
	std::list<Transaccion> transacciones = {
		{100, 800.0,	"APROBADA"},
		{101, 1200.5,	"EN TRANSITO"},
		{102, 1000,		"RECHAZADA"},
		{103, 15000.5,	"APROBADA"},
		{104, 100.4,	"RECHAZADA"}
	};

	//for (const auto& d : container)

	// Hay montos críticos? (any_of ?)
	bool resultado = std::any_of(transacciones.begin(), transacciones.end(),
		[](const auto& t) {	return (t.monto > 20000); } );

	if (resultado == true)
		std::cout << "Transaccion critica encontrada!" << std::endl;

	// Rechazos (count_if)
	auto rechazos = std::count_if(transacciones.begin(), transacciones.end(),
		[](const auto& t) { return (t.estado == "RECHAZADA"); });

	std::cout << "Transacciones rechazadas: " << rechazos << std::endl;

	//resultado = std::find(transacciones.begin(), transacciones.end(), tRechazada);

	//std::cout << "Transaccion rechazada: #" << resultado->id << std::endl;

	// Siguiente a revisar (find_if)

	// Total (accumulate)

	// Mayor transacción (max_element)

	// Imprimir transacciones (for_each)
}