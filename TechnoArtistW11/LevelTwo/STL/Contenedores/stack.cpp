#include <iostream>
#include <stack>

void testStack() {
	std::stack<std::string> historialPaginas;

	historialPaginas.push("www.google.com");
	historialPaginas.push("www.amazon.com");
	historialPaginas.push("www.vendedor.com");

	std::cout << "Pagina actual: " << historialPaginas.top() << std::endl;

	std::cout << "Usuario hace click en atrás" << std::endl;
	historialPaginas.pop();

	std::cout << "Pagina actual: " << historialPaginas.top() << std::endl;
}