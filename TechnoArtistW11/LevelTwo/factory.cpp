#include <iostream>

namespace Juego {
	class Personaje {
	protected:
		int energia;
	public:
		virtual ~Personaje() = default;
		virtual void atacar() = 0;
	};

	class Guerrero : public Personaje {
		void atacar() override {
			std::cout << "Guerrero ataca" << std::endl;
		}
	};

	class Hechicero : public Personaje {
		void atacar() override {
			std::cout << "Hechicero ataca" << std::endl;

		}
	};
	class Monstruo : public Personaje {
		void atacar() override {
			std::cout << "Monstruo ataca" << std::endl;

		}
	};

	class FabricaPersonaje {
	public:
		virtual ~FabricaPersonaje() = default;
		virtual std::shared_ptr<Personaje> crearPersonaje() = 0;
	};

	class FabricaGuerrero : public FabricaPersonaje {

		std::shared_ptr<Personaje> crearPersonaje() override {
			return std::make_shared<Guerrero>();
		}
	};
	class FabricaHechicero : public FabricaPersonaje {

		std::shared_ptr<Personaje> crearPersonaje() override {
			return std::make_shared<Hechicero>();
		}
	};
	class FabricaMonstruo : public FabricaPersonaje {

		std::shared_ptr<Personaje> crearPersonaje() override {
			return std::make_shared<Monstruo>();
		}
	};
}

using namespace Juego;

void testFactory() {
	int tipoPersonaje;

	std::cout << "Elija personaje 1/2: ";
	std::cin >> tipoPersonaje;

	std::shared_ptr<Personaje> personaje;
	std::shared_ptr<FabricaPersonaje> fabricaPersonaje;

	if (tipoPersonaje == 1) {
		fabricaPersonaje = std::make_shared<FabricaGuerrero>();
	}
	else if (tipoPersonaje == 2) {
		fabricaPersonaje = std::make_shared<FabricaHechicero>();
	}
	else {
		std::cerr << "Personaje no valido" << std::endl;
	}

	if (fabricaPersonaje != nullptr)
		personaje = fabricaPersonaje->crearPersonaje(); // llamada polimorfica

	if (personaje != nullptr)
		personaje->atacar(); // llamada polimorfica
	else
		std::cerr << "Falla en la creacion del personaje" << std::endl;

}