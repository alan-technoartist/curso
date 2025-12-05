#include <iostream>

namespace NuevoVehiculo2 {
	class Vehiculo {
	public:
		int numeroSerie;
		int tamano;

	public:
		Vehiculo() {
			std::cout << "Creando vehiculo" << std::endl;
		}
		virtual ~Vehiculo() {
			std::cout << "Destruyendo vehiculo" << std::endl;
		}

		bool operator<(const Vehiculo& v) {
			if (this->tamano < v.tamano)
				return true;
			else
				return false;
		}

		virtual void avanzar() = 0;

	};

	class VehiculoTerrestre : virtual public Vehiculo {
	private:
		int numRuedas;

	public:
		VehiculoTerrestre() {
			std::cout << "Creando vehiculo terrestre" << std::endl;
		}
		~VehiculoTerrestre() {
			std::cout << "Destruyendo vehiculo terrestre" << std::endl;
		}

		void avanzar() override {
			std::cout << "Vehiculo terrestre avanza" << std::endl;

		}

	};

	class VehiculoAcuatico : virtual public Vehiculo {
	private:
		double profundidadMaxima;

	public:
		VehiculoAcuatico() {
			std::cout << "Creando vehiculo acuatico" << std::endl;
		}
		~VehiculoAcuatico() {
			std::cout << "Destruyendo vehiculo acuatico" << std::endl;
		}
		void avanzar() override  {
			std::cout << "Vehiculo acuatico avanza" << std::endl;

		}
	};

	class VehiculoAnfibio : public VehiculoTerrestre,
							public VehiculoAcuatico {
	public:
		VehiculoAnfibio() {
			std::cout << "Creando vehiculo anfibio. # serie: " << numeroSerie << std::endl;
		}
		~VehiculoAnfibio() {
			std::cout << "Destruyendo vehiculo anfibio" << std::endl;
		}

		void avanzar() override {
			std::cout << "Vehiculo anfibio avanza" << std::endl;

		}
	};
}
using namespace NuevoVehiculo2;

void probarHerenciaSimple() {
	/*VehiculoAnfibio vehiculoAnfibio;
	VehiculoAnfibio vehiculoAnfibio2;

	vehiculoAnfibio.tamano = 34;
	vehiculoAnfibio2.tamano = 52;

	if (vehiculoAnfibio < vehiculoAnfibio2) {
		std::cout << "vehiculoAnfibio es mas pequeño que vehiculoAnfibio2" << std::endl;
	}
	else {
		std::cout << "vehiculoAnfibio2 es mas pequeño que vehiculoAnfibio" << std::endl;

	}*/

	//Vehiculo vehiculo1;
	//vehiculo1.avanzar();

	//Vehiculo* vehiculo2; // puntero a clase base

	//vehiculo2 = new Vehiculo();
	//vehiculo2->avanzar();

	auto vehiculo2 = std::make_unique<VehiculoTerrestre>(); // instancia clase derivada
	vehiculo2->avanzar(); // metodo virtual

	//vehiculo2 = new VehiculoAcuatico(); // instancia de clase derivada
	//vehiculo2->avanzar(); // metodo virtual
}