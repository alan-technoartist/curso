#pragma once

#include "../include/ProductoElectronico.hpp"

namespace InventarioNuevo {

		std::string ProductoElectronico::imprimirTipoConexion(Conexion tipo) {
			switch (tipo) {
			case Conexion::ALAMBRICA:
				return "Alambrica";
			case Conexion::INALAMBRICA:
				return "Inalambrica";
			}
			return "";
		}


		ProductoElectronico::ProductoElectronico(int nuevoId, std::string nuevoNombre, float nuevoPrecio, Conexion nuevoTipo) :
			Producto(nuevoId, nuevoNombre, nuevoPrecio),
			tipoConexion(nuevoTipo) {

		}

		void ProductoElectronico::imprimirDatos() {

			Producto::imprimirDatos();

			std::cout << imprimirTipoConexion(tipoConexion) << std::endl;
		}

}
