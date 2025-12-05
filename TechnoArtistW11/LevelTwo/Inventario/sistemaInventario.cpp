#include <iostream>
#include <vector>

//#include "Producto.hpp"
#include "include/ProductoElectronico.hpp"
#include "include/ProductoFarmacia.hpp"
#include "include/Conexion.hpp"
#include "include/Inventario.hpp"

using namespace InventarioNuevo;

void menuAgregar() {
	int id;
	std::string nombre;
	float precio;

	int tipoProducto;

	auto inventario = Inventario::obtenerInstancia();

	std::cout << "Seleccione tipo:" << std::endl;
	std::cout << "1 - Electronico" << std::endl;
	std::cout << "2 - Farmacia" << std::endl;
	std::cin >> tipoProducto;

	std::cout << "Id: ";
	std::cin >> id;
	std::cout << "Nombre: ";
	std::cin >> nombre;
	std::cout << "Precio: ";
	std::cin >> precio;

	if (tipoProducto == 1) {
		// Producto electronico

		int opcionConexion;

		std::cout << "Seleccione tipo de conexion:" << std::endl;
		std::cout << "1 - Alambrica" << std::endl;
		std::cout << "2 - Inalambrica" << std::endl;
		std::cin >> opcionConexion;

		std::shared_ptr<ProductoElectronico> productoNuevo;

		if (opcionConexion == 1) {
			productoNuevo = std::make_shared<ProductoElectronico>(id, nombre, precio, Conexion::ALAMBRICA);
		}
		else if (opcionConexion == 2) {
			productoNuevo = std::make_shared<ProductoElectronico>(id, nombre, precio, Conexion::INALAMBRICA);
		}

		inventario->agregarProducto(productoNuevo);

	}
	else if (tipoProducto == 2) {
		int opcionControlado;

		std::cout << "Producto controlado?:" << std::endl;
		std::cout << "1 - Si" << std::endl;
		std::cout << "2 - No" << std::endl;
		std::cin >> opcionControlado;

		std::shared_ptr<ProductoFarmacia> productoNuevo;

		if (opcionControlado == 1) {
			productoNuevo = std::make_shared<ProductoFarmacia>(id, nombre, precio, true);
		}
		else if (opcionControlado == 2) {
			productoNuevo = std::make_shared<ProductoFarmacia>(id, nombre, precio, false);
		}

		inventario->agregarProducto(productoNuevo);
	}

}

void testInventario() {

	std::shared_ptr<Inventario> inventario = Inventario::obtenerInstancia();

	std::cout << inventario << std::endl;

	int opcion;

	do {
		std::cout << "Seleccione opcion:" << std::endl;
		std::cout << "1 - Agregar producto" << std::endl;
		std::cout << "2 - Listar productos" << std::endl;
		std::cout << "3 - Buscar producto" << std::endl;
		std::cout << "4 - Salir" << std::endl;

		std::cin >> opcion;

		if (opcion == 1) {
			// Agregar producto
			menuAgregar();
		}
		else if (opcion == 2) {
			// Listar productos
			inventario->listarProductos();
		}
		else if (opcion == 3) {
			// Buscar productos
			int id;
			std::cout << "Id: ";
			std::cin >> id;

			try {
				int ubicacion = inventario->buscarProducto(id);

				std::cout << "Producto con id " << id << " se encuentra en: " << ubicacion << std::endl;
			}
			catch (const NoEncontradoExcp& e) {
				std::cerr << e.what() << std::endl;
			}

		}
		

	} while (opcion != 4);
	
}