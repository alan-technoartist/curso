#include <iostream>
#include <vector>
#include <memory>

namespace Inventario2 {

	class Producto {
	private:
		std::string nombre;
		double precio;

	public:
		long id;

		Producto(std::string n, double p) :
			nombre(n), precio(p) {

			id = 0;
		}

		std::string obtenerNombre() const {
			return this->nombre;
		}

		long obtenerId() const {
			return this->id;
		}

		double obtenerPrecio() const {
			return this->precio;
		}

	public:
		virtual void imprimirInformacion() {
			std::cout << "Id: " << this->id << std::endl;
			std::cout << "Nombre: " << this->nombre << std::endl;
			std::cout << "Precio: " << this->precio << std::endl;
		}

	};

	class ProductoElectronico : public Producto {
	private:
		int tiempoGarantia;

	public:
		ProductoElectronico(std::string n, double p, int t) :
			Producto(n, p),
			tiempoGarantia(t) {

		}

		void imprimirInformacion() override {
			// Imprime informacion de clase base
			Producto::imprimirInformacion();

			// Imprime informacion de clase propia
			std::cout << "Tiempo garantia: " << tiempoGarantia << " meses" << std::endl;
		}
	};

	class ProductoAlimenticio : public Producto {
	private:
		int anoCaducidad;

	public:
		ProductoAlimenticio(std::string n, double p, int a) :
			Producto(n, p),
			anoCaducidad(a) {

		}
		void imprimirInformacion() override {
			// Imprime informacion de clase base
			Producto::imprimirInformacion();

			// Imprime informacion de clase propia
			std::cout << "Caducidad: " << anoCaducidad << std::endl;
		}
	};

	class ExcepcionProductoNoEncontrado : public std::exception {
	private:
		std::string detalleInterno;
	public:
		ExcepcionProductoNoEncontrado(const char* detalle) {
			detalleInterno = detalle;
		}
		const char* what() const noexcept override {
			return detalleInterno.c_str();
		}
	};

	class Inventario {
	private:
		long ids;
		std::vector<std::shared_ptr<Producto>> productos;

	public:
		Inventario() {
			ids = 0;
		}

		static std::shared_ptr<Inventario> obtenerInstancia() {
			static std::shared_ptr<Inventario> instancia = std::make_shared<Inventario>();

			return instancia;
		}

		void agregarProducto(std::shared_ptr<Producto> producto) {
			producto->id = ++ids;

			productos.push_back(producto);
		}

		int buscarProducto(long id) {
			for (int i = 0; i < productos.size(); i++) {
				if (productos[i]->obtenerId() == id) {
					return i;
				}
			}
			return -1;
		}

		void quitarProducto(long id) {
			int ubicacion = buscarProducto(id);

			if (ubicacion == -1) {
				throw ExcepcionProductoNoEncontrado("Producto no encontrado");
			}

			productos.erase(productos.begin() + ubicacion);
		}

		void listarProductos() const {
			for (std::shared_ptr<Producto> p : productos) {
				p->imprimirInformacion(); // llamada polimorfica
			}
		}
	}; // class

}

using namespace Inventario2;

void mainInventario() {
	std::cout << "Iniciando sistema de control de inventario" << std::endl;

	/*
	* 1. Agregar producto
	* 2. Quitar producto
	* 3. Listar productos
	* 4. Actualizar datos de producto
	* 5. Buscar producto
	*/

	Inventario inventario;

	int opcion;

	do {
		std::cout << "Elija una opcion: " << std::endl;
		std::cout << "1 - Agregar producto" << std::endl;
		std::cout << "2 - Quitar producto" << std::endl;
		std::cout << "3 - Buscar producto" << std::endl;
		std::cout << "4 - Listar productos" << std::endl;
		std::cout << "5 - Salir" << std::endl;

		std::cin >> opcion;

		if (opcion == 1) { // Agregar producto
			std::shared_ptr<Producto> producto;

			std::cout << "Seleccione tipo de producto:" << std::endl;
			std::cout << "1 - Electronico" << std::endl;
			std::cout << "2 - Alimento" << std::endl;

			int tipoProducto;
			std::string nombre;
			double precio;

			std::cin >> tipoProducto;

			std::cout << "Nombre: ";
			std::cin >> nombre;
			std::cout << "Precio: ";
			std::cin >> precio;

			if (tipoProducto == 1) {  // Electronico
				int tiempoGarantia;

				std::cout << "Tiempo garantia: ";
				std::cin >> tiempoGarantia;

				producto = std::make_shared<ProductoElectronico>(nombre, precio, tiempoGarantia);

			} 
			else if (tipoProducto == 2) { // Alimento
				int caducidad;

				std::cout << "Año caducidad: ";
				std::cin >> caducidad;

				producto = std::make_shared<ProductoAlimenticio>(nombre, precio, caducidad);
			}

			inventario.agregarProducto(producto);
			
		}
		else if (opcion == 2) {

			try {
				inventario.quitarProducto(0);
			}
			catch (const ExcepcionProductoNoEncontrado& e) {
				std::cout << e.what() << std::endl;
			}

		}

	} while (opcion != 5);
	

	std::shared_ptr<Inventario> inventarioUnico = Inventario::obtenerInstancia();
	std::cout << inventarioUnico << std::endl;

}