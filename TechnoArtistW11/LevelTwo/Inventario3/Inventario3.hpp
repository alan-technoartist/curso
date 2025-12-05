#include <iostream>
#include <vector>
#include <memory>

namespace Inventario3 {

	enum class TipoProducto {
		ELECTRONICO,
		ABARROTES,
		FERRETERIA
	};

	class Producto {
	private:
		TipoProducto tipo;
		std::string marca;
		float precio;

		std::string convertirTipoProducto(TipoProducto producto);

	public:
		Producto(TipoProducto tipo, std::string marca, float precio, long id);

		long id; // identificador unico

		void imprimirInformacion();
	};

	class ProductoElectronico : public Producto {
	public:
		ProductoElectronico(TipoProducto t, std::string m, float p, long i, int v);

		int voltajeOperacion;
	};

	class ProductoAbarrotes : public Producto {
	public:
		ProductoAbarrotes(TipoProducto t, std::string m, float p, long i, std::string f);

		std::string fechaCaducidad;
	};

	class Inventario {
	private:
		std::vector<std::shared_ptr<Producto>> productos;

	public:
		// 1. Agregar producto
		void agregarProducto(std::shared_ptr<Producto> producto);

		// 2. Quitar producto
		void quitarProducto(long id);

		// 3. Buscar producto
		int buscarProducto(long id);

		// 4. Actualizar producto

		// 5. Listar productos existentes
		void listarProductos();
	

	};

};