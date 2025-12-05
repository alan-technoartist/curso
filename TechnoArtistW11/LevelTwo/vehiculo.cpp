
#include <iostream>

class VehiculoB {
private:
	double nivelCombustible;
public:
	int tamano;

	VehiculoB() : tamano(0) { }

	VehiculoB(int t) : tamano(t) {
		
	}
	virtual ~VehiculoB() { }

	// sobrecarga del operador >
	bool operator>(const VehiculoB& otro) {
		return (this->tamano > otro.tamano);
	}

	virtual void avanza() = 0;

	double obtenerNivelCombustible() {
		return nivelCombustible;
	}

};

class VehiculoTerrestreD : virtual public VehiculoB {
public:
	void avanza() override {
		std::cout << "Vehiculo terrestre avanza" << std::endl;
	}
};

class VehiculoAcuaticoD : virtual public VehiculoB {
public:
	void avanza() override {
		std::cout << "Vehiculo acuatico avanza" << std::endl;
	}
};

class VehiculoAnfibioD : public VehiculoAcuaticoD, public VehiculoTerrestreD {
public:
	void avanza() override {
		std::cout << "Vehiculo anfibio avanza" << std::endl;
	}
};

void probarVehiculo() {

	std::unique_ptr<VehiculoB> vehiculo;
	
	vehiculo = std::make_unique<VehiculoTerrestreD>();

	vehiculo->avanza();

	vehiculo = std::make_unique<VehiculoAcuaticoD>();

	vehiculo->avanza();

}