#include "../include/Inventario.hpp"

namespace InventarioNuevo {

		std::shared_ptr<Inventario> Inventario::obtenerInstancia() {
			static std::shared_ptr<Inventario> instanciaUnica = nullptr;

			if (instanciaUnica == nullptr) {
				instanciaUnica = std::make_shared<Inventario>();
			}
			return instanciaUnica;
		}

		void Inventario::agregarProducto(std::shared_ptr<Producto> producto) {

			catalogo.push_back(producto);
		}

		void Inventario::eliminarProducto() {

		}

		int Inventario::buscarProducto(int id) {

			for (int i = 0; i < catalogo.size(); i++) {
				if (catalogo[i]->id == id) {
					return i;
				}
			}

			//return -1;
			throw NoEncontradoExcp("Producto no encontrado!");

		}

		void Inventario::listarProductos() {
			std::cout << "Productos disponibles: " << std::endl;

			for (int i = 0; i < catalogo.size(); i++) {
				catalogo[i]->imprimirDatos(); // llamada polimorfica
				std::cout << std::endl;
			}
		}


}