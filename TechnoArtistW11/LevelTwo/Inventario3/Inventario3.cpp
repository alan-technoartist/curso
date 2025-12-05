#include <iostream>
#include <vector>
#include "Inventario3.hpp"

namespace Inventario3 {

	Producto::Producto(TipoProducto t, std::string m, float p, long i) :
		tipo(t),
		marca(m),
		precio(p),
		id(i)
	{

	}

	ProductoElectronico::ProductoElectronico(TipoProducto t, std::string m, float p, long i, int v) :
		Producto(t, m, p, i),
		voltajeOperacion(v)
	{

	}

	ProductoAbarrotes::ProductoAbarrotes(TipoProducto t, std::string m, float p, long i, std::string f) :
		Producto(t, m, p, i),
		fechaCaducidad(f)
	{

	}

	std::string Producto::convertirTipoProducto(TipoProducto producto) {
		switch (producto) {
		case TipoProducto::ELECTRONICO:
			return "Electronico";
		case TipoProducto::ABARROTES:
			return "Abarrotes";
		case TipoProducto::FERRETERIA:
			return "Ferreteria";
		default:
			return "";
		}
	}

	void Producto::imprimirInformacion() {
		std::cout << "Id: " << this->id << std::endl;
		std::cout << "Tipo: " << convertirTipoProducto(this->tipo) << std::endl;
		std::cout << "Marca: " << this->marca << std::endl;
		std::cout << "Precio: " << this->precio << std::endl;
	}

	// =======================================================================================

	// 1. Agregar producto
	void Inventario::agregarProducto(std::shared_ptr<Producto> producto) {
		productos.push_back(producto);
	}
	// 
	// 2. Quitar producto
	void Inventario::quitarProducto(long id) {
		int posicion = buscarProducto(id);

		if (posicion == -1) {
			std::cout << "Producto no valido" << std::endl;
			return;
		}

		productos.erase(productos.begin() + posicion);
	}

	// 3. Buscar producto
	int Inventario::buscarProducto(long id) {

		for (int i = 0; i < productos.size(); i++) {
			if (productos[i]->id == id)
				return i;
		}

		return -1;
	}

	// 4. Actualizar producto
	//
	// 5. Listar productos existentes
	void Inventario::listarProductos() {
		for (auto producto : productos) {
			producto->imprimirInformacion();
		}
	}


}