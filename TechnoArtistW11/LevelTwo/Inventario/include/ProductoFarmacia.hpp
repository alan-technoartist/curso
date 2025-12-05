#pragma once

#include "Producto.hpp"

namespace InventarioNuevo {
	class ProductoFarmacia : public Producto {
	private:
		bool controlado;

	public:
		ProductoFarmacia(int nuevoId, std::string nuevoNombre, float nuevoPrecio, bool nuevoControl);

		void imprimirDatos() override;
	};
}