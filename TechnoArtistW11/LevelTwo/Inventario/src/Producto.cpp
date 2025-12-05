#include "../include/Producto.hpp"

namespace InventarioNuevo {

	Producto::Producto(int nuevoId, std::string nuevoNombre, float nuevoPrecio) :
		id(nuevoId),
		nombre(nuevoNombre),
		precio(nuevoPrecio)
	{

	}

	void Producto::imprimirDatos() {
		std::cout << "Id: " << id << std::endl;
		std::cout << "Nombre: " << nombre << std::endl;
		std::cout << "Precio: " << precio << std::endl;
	}
}