#pragma once

#include "Producto.hpp"
#include "Conexion.hpp"

namespace InventarioNuevo {

	class ProductoElectronico : public Producto {
	private:
		Conexion tipoConexion;

		std::string imprimirTipoConexion(Conexion tipo);

	public:
		ProductoElectronico(int nuevoId, std::string nuevoNombre, float nuevoPrecio, Conexion nuevoTipo);

		void imprimirDatos() override;
	};

}