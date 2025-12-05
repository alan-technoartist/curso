#include "../include/ProductoFarmacia.hpp"

namespace InventarioNuevo {

		ProductoFarmacia::ProductoFarmacia(int nuevoId, std::string nuevoNombre, float nuevoPrecio, bool nuevoControl) :
			Producto(nuevoId, nuevoNombre, nuevoPrecio),
			controlado(nuevoControl) {
		}

		void ProductoFarmacia::imprimirDatos() {
			Producto::imprimirDatos();

			std::cout << "Controlado: " << ((controlado) ? "si" : "no") << std::endl;
		}
	
}