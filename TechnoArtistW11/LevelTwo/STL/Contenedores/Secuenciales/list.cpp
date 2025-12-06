#include <iostream>
#include <list>

struct Cancion {
	std::string nombre;
	std::string artista;
};

void testList() {
	std::list<Cancion> listaReproduccion = {
		{ "Let it be", "The Beatles" },
		{ "Querida", "Juan Gabriel" },
		{ "La media vuelta", "Luis Miguel" }
	};

	std::list<Cancion> favoritos;

	auto iteradorFav = favoritos.begin();
	auto iteradorLista = listaReproduccion.begin();

	favoritos.splice(iteradorFav, listaReproduccion, iteradorLista);

	for (auto it = listaReproduccion.begin(); it != listaReproduccion.end(); it++) {
		std::cout << it->nombre << std::endl;
	}
	
	std::cout << "============================" << std::endl;

	for (auto c : favoritos) {
		std::cout << c.nombre << std::endl;
	}
}