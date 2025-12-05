#include <iostream>

namespace NuevoVehiculo {
	class Vehiculo {
	public:
		Vehiculo() {
			std::cout << "Creando vehiculo" << std::endl;

			tamano = 1;
		}
		virtual ~Vehiculo() {
			std::cout << "Destruyendo vehiculo" << std::endl;

		}

		int tamano;
		int fechaFabricacion;
		std::string modelo;

		virtual void avanzar() = 0;

		bool operator<(const Vehiculo& v) {
			return (this->tamano < v.tamano);
		}
		bool operator>(const Vehiculo& v) {
			return (this->tamano > v.tamano);
		}
		bool operator==(const Vehiculo& v) {
			return (this->tamano == v.tamano);
		}
	};

	class VehiculoTerrestre : virtual public Vehiculo {
	public:
		int cantidadRuedas;

		VehiculoTerrestre() {
			std::cout << "Creando VehiculoTerrestre" << std::endl;
		}
		~VehiculoTerrestre() {
			std::cout << "Destruyendo VehiculoTerrestre" << std::endl;

		}

		void avanzar()  {
			std::cout << "Vehiculo terrestre avanza" << std::endl;
		}
	};

	class VehiculoAcuatico : virtual public Vehiculo {
	public:
		float capacidadCarga;

		VehiculoAcuatico() {
			std::cout << "Creando VehiculoAcuatico" << std::endl;
		}
		~VehiculoAcuatico() {
			std::cout << "Destruyendo VehiculoAcuatico" << std::endl;
		}

		void avanzar()  {
			std::cout << "Vehiculo acuatico avanza" << std::endl;
		}
	};

	class VehiculoAnfibio : public VehiculoAcuatico,
							public VehiculoTerrestre {
	public:
		VehiculoAnfibio() {
			std::cout << "Creando VehiculoAnfibio" << std::endl;
		}
		~VehiculoAnfibio() {
			std::cout << "Destruyendo VehiculoAnfibio" << std::endl;
		}

		void avanzar()  {
			std::cout << "Vehiculo anfibio avanza" << std::endl;
		}
	};
}
using namespace NuevoVehiculo;

void probarHerencia() {
	/*Vehiculo vehiculo1;
	Vehiculo vehiculo2;

	vehiculo1.tamano = 14;
	vehiculo2.tamano = 11;

	if (vehiculo1 > vehiculo2) {
	//  vehiculo1.operator<(vehiculo2);
		std::cout << "Vehiculo 1 es mas pequeño que vehiculo 2" << std::endl;
	}
	else {
		std::cout << "Vehiculo 2 es mas pequeño que vehiculo 1" << std::endl;

	}*/

	std::unique_ptr<Vehiculo> vehiculo;

	vehiculo = std::make_unique<VehiculoTerrestre>();

	vehiculo->avanzar();

}