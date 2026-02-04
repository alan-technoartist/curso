
#include <iostream>
#include <fstream>
#include <string>

struct Tarea {
	int id;
	char descripcion[32];
	bool realizada;
};

int calcularNuevoId(std::fstream& archivo) {
	Tarea tarea;
	int id;

	archivo.seekg(0, std::ios::end);
	int tamano = archivo.tellg();

	if (tamano == 0) {
		// Archivo vacio
		return 0;
	}

	int posicionInicial = (static_cast<int>(sizeof(Tarea)));

	// Retroceder cursor de lectura al inicio de la ultima tarea
	archivo.seekg(-posicionInicial, std::ios::end);

	// Leer archivo
	archivo.read(reinterpret_cast<char*>(&tarea), sizeof(Tarea));

	id = tarea.id + 1;

	return id;
}

void agregarTarea() {
	std::fstream archivo("ejemplo.bin", std::ios::binary |
										std::ios::in |
										std::ios::app);

	if (archivo.is_open()) {
		Tarea tarea;

		tarea.id = calcularNuevoId(archivo);

		std::cout << "Nuevo Id: " << tarea.id << std::endl;

		std::cout << "Introduzca descripcion: ";
		std::cin.ignore();
		std::cin.getline(tarea.descripcion, 32);

		tarea.realizada = false;

		archivo.write(reinterpret_cast<char*>(&tarea), sizeof(tarea));

		archivo.close();
	}
	else {
		std::cerr << "Error al abrir el archivo" << std::endl;
	}

}

void mostrarTareas() {
	std::ifstream archivo("ejemplo.bin", std::ios::binary);

	if (archivo.is_open()) {
		Tarea tarea;

		std::cout << std::endl << "Lista de pendientes: " << std::endl;

		while (archivo.read(reinterpret_cast<char*>(&tarea), sizeof(Tarea))) {

			std::cout << tarea.id << " - " << "[" << ((tarea.realizada) ? "*" : " ") << "] "
				<< tarea.descripcion << std::endl;
		}

		std::cout << std::endl;
		archivo.close();
	}
	else {
		std::cerr << "Error al abrir el archivo" << std::endl;
	}

}

void marcarTerminada() {
	std::fstream archivo("ejemplo.bin", std::ios::binary | std::ios::in | std::ios::out);

	if (archivo.is_open()) {
		Tarea tarea;

		int id;

		std::cout << "Introduzca ID: ";
		std::cin >> id;

		// Pre-condicion para que el calculo de la posicion sea correcto:
		// 1. Id debe comenzar en cero
		// 2. Ids deben ser consecutivos
		std::streampos posicion = id * sizeof(Tarea);
		archivo.seekg(posicion); // Acceso aleatorio

		if (archivo.read(reinterpret_cast<char*>(&tarea), sizeof(Tarea))) {

			tarea.realizada = true;

			archivo.seekp(posicion);
			archivo.write(reinterpret_cast<char*>(&tarea), sizeof(Tarea));
		}
		else {
			std::cerr << "No se leyeron datos" << std::endl;
		}

		archivo.close();
	}
	else {
		std::cerr << "Error al abrir el archivo" << std::endl;
	}

}

void modificarTarea() {
	// Crear el objeto fstream
	std::fstream archivo("ejemplo.bin", std::ios::binary | std::ios::in | std::ios::out);

	if (archivo.is_open()) {
		Tarea tarea;
		int id;

		std::cout << "Introduzca ID: ";
		std::cin >> id;

		std::streampos posicion = id * sizeof(Tarea);
		// Mover cursor para lectura
		archivo.seekg(posicion);

		// Leer del archivo
		archivo.read(reinterpret_cast<char*>(&tarea), sizeof(Tarea));

		std::cout << "Introduzca nueva descripcion: ";

		std::cin.ignore();
		std::cin.getline(tarea.descripcion, 32);

		// Mover cursor para escritura
		archivo.seekp(posicion);
		// Escribir al archivo
		archivo.write(reinterpret_cast<char*>(&tarea), sizeof(Tarea));

		archivo.close();
	}
	else {
		std::cerr << "Error al abrir el archivo" << std::endl;
	}
}

void borrarTarea() {
	std::ifstream archivoOriginal("ejemplo.bin", std::ios::binary);
	std::ofstream archivoTemporal("temp.bin", std::ios::binary);

	if (archivoOriginal.is_open() && archivoTemporal.is_open()) {
		Tarea tarea;
		int id;

		std::cout << "Introduzca ID: ";
		std::cin >> id;

		while (archivoOriginal.read(reinterpret_cast<char*>(&tarea), sizeof(Tarea))) {

			if (id != tarea.id) {
				// Escribir al archivo temporal
				archivoTemporal.write(reinterpret_cast<char*>(&tarea), sizeof(Tarea));
			}
			else {
				
			}

		}
		archivoOriginal.close();
		archivoTemporal.close();

		std::remove("ejemplo.bin");
		std::rename("temp.bin", "ejemplo.bin");
	}
	else {
		std::cerr << "Error al abrir el archivo" << std::endl;
	}
}

void testFiles() {
	int opcion;

	do {
		std::cout << "1 - Agregar tarea" << std::endl;
		std::cout << "2 - Mostrar tareas" << std::endl;
		std::cout << "3 - Marcar terminada" << std::endl;
		std::cout << "4 - Modificar tarea" << std::endl;
		std::cout << "5 - Borrar tarea" << std::endl;
		std::cout << "6 - Salir" << std::endl;
		std::cout << "> ";

		std::cin >> opcion;

		if (opcion == 1)
			agregarTarea();
		else if (opcion == 2)
			mostrarTareas();
		else if (opcion == 3)
			marcarTerminada();
		else if (opcion == 4)
			modificarTarea();
		else if (opcion == 5)
			borrarTarea();

	} while (opcion != 6);

}