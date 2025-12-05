#pragma once

#include <iostream>
#include <string>

namespace InventarioNuevo {
	class Producto {
	protected:
		std::string nombre;
		float precio;

	public:
		int id;

		Producto(int nuevoId, std::string nuevoNombre, float nuevoPrecio);

		// Destructor debe ser virtual para evitar fugas de memoria
		virtual ~Producto() = default;

		// El metodo imprimirDatos debe ser virtual si queremos
		// utilizar el polimorfismo dinamico
		virtual void imprimirDatos();
	};
}