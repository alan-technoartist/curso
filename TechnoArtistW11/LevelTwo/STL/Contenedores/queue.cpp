#include <iostream>
#include <queue>

void testQueue() {
	std::queue<std::string> colaImpresion;

	colaImpresion.push("Documento1.doc");
	colaImpresion.push("Foto.jpg");
	colaImpresion.push("Reporte.pdf");

	while (!colaImpresion.empty()) {
		std::cout << "Imprimiendo: " << colaImpresion.front() << std::endl;

		colaImpresion.pop();
	}

}