#include <iostream>

namespace Videojuego {

	enum class TipoPersonaje {
		GUERRERO,
		HECHICERO,
		ENEMIGO
	};

	class Personaje {
	public:
		Personaje() {
		//	std::cout << "Creando personaje base" << std::endl;
		}

		virtual ~Personaje() {
		//	std::cout << "Destruyendo personaje base" << std::endl;
		}

		TipoPersonaje tipo;
		float nivelVida;
		std::string nombre;

		virtual void atacar() = 0;

	};

	class PersonajeGuerrero : public Personaje {
	public:
		PersonajeGuerrero() {
		//	std::cout << "Creando guerrero" << std::endl;

		}

		~PersonajeGuerrero() {
		//	std::cout << "Destruyendo guerrero" << std::endl;

		}

		void atacar() override {
			std::cout << "Guerrero ataca!" << std::endl;
		}

	};

	class PersonajeHechicero : public Personaje {
	public:
		void atacar() override {
			std::cout << "Hechicero lanza hechizo!" << std::endl;
		}

	};

	class PersonajeEnemigo : public Personaje {
	public:
		void atacar() override {
			std::cout << "Enemigo ataca!" << std::endl;
		}

	};

	class FabricaPersonaje {
	public:
		virtual ~FabricaPersonaje() = default;
		virtual std::shared_ptr<Personaje> crearPersonaje() = 0;
	};

	class FabricaPersonajeGuerrero : public FabricaPersonaje {
	public:
		std::shared_ptr<Personaje> crearPersonaje() override {
			return std::make_shared<PersonajeGuerrero>();
		}
	};

	class FabricaPersonajeHechicero : public FabricaPersonaje {
	public:
		std::shared_ptr<Personaje> crearPersonaje() override {
			return std::make_shared<PersonajeHechicero>();
		}
	};

	class FabricaPersonajeEnemigo : public FabricaPersonaje {
	public:
		std::shared_ptr<Personaje> crearPersonaje() override {
			return std::make_shared<PersonajeEnemigo>();
		}
	};

}
using namespace Videojuego;

void mainVideojuego() {
	int opcionPersonaje;

	std::cout << "Seleccione personaje: " << std::endl;
	std::cout << "1 - Guerrero" << std::endl;
	std::cout << "2 - Hechicero" << std::endl;

	std::cin >> opcionPersonaje;

	std::shared_ptr<Personaje> personaje;
	std::shared_ptr<FabricaPersonaje> fabrica;

	if (opcionPersonaje == 1) {
		// Guerrero
		fabrica = std::make_shared<FabricaPersonajeGuerrero>();
		personaje = fabrica->crearPersonaje();
	}
	else if (opcionPersonaje == 2) {
		// Hechicero
		fabrica = std::make_shared<FabricaPersonajeHechicero>();
		personaje = fabrica->crearPersonaje();
	}

	std::shared_ptr<PersonajeEnemigo> enemigo1 = std::make_shared<PersonajeEnemigo>();

	// Enemigo ataca
	enemigo1->atacar();

	// Atacar
	personaje->atacar();
}