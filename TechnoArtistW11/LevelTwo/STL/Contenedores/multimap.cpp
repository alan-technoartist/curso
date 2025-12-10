#include <iostream>
#include <map>

void testMultimap() {
	std::multimap<std::string, std::string> biblioteca;

	biblioteca.insert({ "Autor1","Libro1" });
	biblioteca.insert({ "Autor2","Libro1" });
	biblioteca.insert({ "Autor1","Libro2" });
	biblioteca.insert({ "Autor1","Libro3" });
	biblioteca.insert({ "Autor2","Libro2" });

	for (const auto& libro : biblioteca) {
		std::cout << "Autor: " << libro.first << " Titulo: " << libro.second << std::endl;
	}

	//std::cout << "Borrando libros de Autor1" << std::endl;

	//biblioteca.erase("Autor1");

	//for (const auto& libro : biblioteca) {
	//	std::cout << "Autor: " << libro.first << " Titulo: " << libro.second << std::endl;
	//}


	auto rango = biblioteca.equal_range("Autor1");

	std::cout << "Imprimiendo rango de libros de Autor1" << std::endl;

	for (auto it = rango.first; it != rango.second; it++) {

		std::cout << it->first << it->second << std::endl;

	}
}
