#include <iostream>
#include <vector>

#include "Producto.hpp"
#include "Excepciones.hpp"

namespace InventarioNuevo {

	class Inventario {
	private:
		std::vector<std::shared_ptr<Producto>> catalogo;

	public:

		// Singleton
		static std::shared_ptr<Inventario> obtenerInstancia();

		void agregarProducto(std::shared_ptr<Producto> producto);

		void eliminarProducto();

		int buscarProducto(int id);

		void listarProductos();
	};

}