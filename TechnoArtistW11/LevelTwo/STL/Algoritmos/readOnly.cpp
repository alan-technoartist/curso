#include <iostream>
#include <algorithm>
#include <numeric>
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

	std::cout << "Transacciones:" << std::endl;
	for (auto t : transacciones) {
		std::cout << t.id << " | $" << t.monto << std::endl;
	}

	// Hay montos críticos? (any_of ?)
	bool resultado = std::any_of(transacciones.begin(), transacciones.end(),
		[](const auto& t) {	return (t.monto > 20000); });

	if (resultado == true)
		std::cout << "Transaccion critica detectada!" << std::endl;

	// Rechazos (count_if)
	auto rechazos = std::count_if(transacciones.begin(), transacciones.end(),
		[](const auto& t) { return (t.estado == "RECHAZADA"); });

	std::cout << "# Transacciones rechazadas: " << rechazos << std::endl;

	// Detalle de rechazados (copy_if)
	std::list<Transaccion> tRechazadas;

	std::copy_if(transacciones.begin(), transacciones.end(), std::back_inserter(tRechazadas),
		[](const auto& t) { return (t.estado == "RECHAZADA"); });

	for (const auto& t : tRechazadas) {
		std::cout << t.id << " | $" << t.monto << std::endl;
	}

	// Siguiente a revisar (find_if)
	auto res = std::find_if(transacciones.begin(), transacciones.end(),
		[](const auto& t) { return (t.estado == "EN TRANSITO"); });

	if (res != transacciones.end())
		std::cout << "Siguiente transaccion en transito: " << res->id << std::endl;


	// lambda para acumular sumas
	auto sumaAcumulada = [](const double& x, const Transaccion& y) {
		return (x + y.monto);
		};

	// Total (accumulate)
	double total = std::accumulate(transacciones.begin(), transacciones.end(), 0.0, sumaAcumulada);

	std::cout << "Total: $" << total << std::endl;

	// Mayor transacción (max_element)
	auto maximoValor = std::max_element(transacciones.begin(), transacciones.end(),
		[](const auto& a, const auto& b) { return (a.monto < b.monto); });

	std::cout << "Transaccion maxima: $" << maximoValor->monto << std::endl;

	// Imprimir transacciones (for_each)
	std::for_each(transacciones.begin(), transacciones.end(),
		[](Transaccion& t) { t.monto *= 1.16; });

	std::cout << "Transacciones + IVA:" << std::endl;
	for (auto t : transacciones) {
		std::cout << t.id << " | $" << t.monto << std::endl;
	}
}
