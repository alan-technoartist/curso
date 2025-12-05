 #include <iostream>

enum class Traccion {
	DELANTERA,
	TRASERA
};

enum class MetodoAvance {
	TERRESTRE,
	AEREO
};

class Vehiculo {
public:
	Vehiculo() {
		std::cout << "Creando vehiculo" << std::endl;
	}
	virtual ~Vehiculo() {
		std::cout << "Destruyendo vehiculo" << std::endl;

	}

	std::string color;
	int modelo;
	float tamano;

	virtual void avanzar() = 0;

	int obtenerModelo() {
		return modelo;
	}

	bool operator>(const Vehiculo& otro) {
		if (this->tamano > otro.tamano)
			return true;
		else
			return false;
	}

};

class VehiculoTerrestre : virtual public Vehiculo {
public:
	VehiculoTerrestre()  {
		std::cout << "Creando vehiculo terrestre" << std::endl;

	}
	~VehiculoTerrestre() {
		std::cout << "Destruyendo vehiculo terrestre" << std::endl;

	}

	Traccion traccion;

	void avanzar() override {
		std::cout << "Vehiculo terrestre avanza" << std::endl;
	}

};

class VehiculoAereo : virtual public Vehiculo {
public:
	float alturaMaxima;

	VehiculoAereo() {
		std::cout << "Creando vehiculo aereo" << std::endl;

	}
	~VehiculoAereo() {
		std::cout << "Destruyendo vehiculo aereo" << std::endl;

	}

	void avanzar() override {
		std::cout << "Vehiculo aereo avanza" << std::endl;
	}

};

class VehiculoAnfibio : public VehiculoTerrestre,
						public VehiculoAereo {
public:
	VehiculoAnfibio() : tipoAvance(MetodoAvance::TERRESTRE) {
		std::cout << "Creando vehiculo anfibio" << std::endl;

	}
	~VehiculoAnfibio() {
		std::cout << "Destruyendo vehiculo anfibio" << std::endl;

	}

	MetodoAvance tipoAvance;

	void establecerTipo(MetodoAvance tipo) {
		tipoAvance = tipo;
	}
	
	void avanzar() override {
		if (tipoAvance == MetodoAvance::TERRESTRE) {
			VehiculoTerrestre::avanzar();
		}
		else {
			VehiculoAereo::avanzar();
		}
	}

};

void testInheritance(void) {
	VehiculoAnfibio vehiculo;

	VehiculoAnfibio* vehiculo2 = new VehiculoAnfibio();

	vehiculo.avanzar();
	vehiculo.establecerTipo(MetodoAvance::AEREO);
	vehiculo.avanzar();

	vehiculo2->avanzar();

}