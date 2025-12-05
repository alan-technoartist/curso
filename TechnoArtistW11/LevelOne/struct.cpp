#include <iostream>

namespace nuevoAnimal {
	enum class TipoAnimal {
		MAMIFERO,
		REPTIL,
		AVE
	};

	class Animal {
	private:
		long id;
		int hijos;
	public:
		std::string nombre;
		int edad;
		TipoAnimal tipo;

		void establecerId(long id) {
			this->id = id;
		}

		void hacerRuido() {
			std::cout << "Animal haciendo ruido" << std::endl;
		}
	};
}
using namespace nuevoAnimal;

void basicStruct(void) {
	struct Direccion {
		std::string calle;
		int numero;
	};
	struct Alumno {
		std::string nombre;
		float calificacion;
		int edad;

		Direccion direccion;
	};

	Alumno alan;
	alan.nombre = "Alan Bautista";
	alan.edad = 34;
	alan.direccion.calle = "Calle";
	alan.direccion.numero = 0;
	std::cout << alan.edad << std::endl;

	Animal animal;
	animal.nombre = "Perro";
	animal.tipo = TipoAnimal::MAMIFERO;
	animal.hacerRuido();
	animal.establecerId(1);
}