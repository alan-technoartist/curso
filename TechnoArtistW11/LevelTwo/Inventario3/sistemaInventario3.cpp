#include <iostream>
#include "Inventario3.hpp"

using namespace Inventario3;

void inventarioPrincipal() {
	std::cout << "Iniciando sistema de control de inventario" << std::endl;

	// Imprimir menu de usuario
	// 1. Agregar producto
	// 2. Quitar producto
	// 3. Buscar producto
	// 4. Actualizar producto

	Inventario inventario;

	std::shared_ptr<ProductoElectronico> electronico1
		= std::make_shared<ProductoElectronico>(TipoProducto::ELECTRONICO, "MarcaGenerica", 20.0, 0, 120);


	std::shared_ptr<ProductoAbarrotes> abarrotes1
		= std::make_shared<ProductoAbarrotes>(TipoProducto::ABARROTES, "MarcaAbarrotes", 10.2, 1, "Febrero 2026");

	inventario.agregarProducto(electronico1);
	inventario.agregarProducto(abarrotes1);

	inventario.listarProductos();

}