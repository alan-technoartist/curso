
#include <iostream>
#include <fstream>
#include <string>

struct Tarea {
	int id;
	char descripcion[50];
	bool realizada;
};

void agregarTarea() {
	std::ofstream archivo("ejemplo.bin", std::ios::binary | std::ios::app);

	if (archivo.is_open()) {
		Tarea tarea;

		std::cout << "Introduzca ID: ";
		std::cin >> tarea.id;

		std::cout << "Introduzca descripcion: ";
		std::cin.ignore();
		std::cin.getline(tarea.descripcion, 50);

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
	Tarea tarea;

	if (archivo.is_open()) {
		while (archivo.read(reinterpret_cast<char*>(&tarea), sizeof(Tarea))) {
			std::cout << tarea.realizada << " " << tarea.id << "\t" << tarea.descripcion << std::endl;
		}
		archivo.close();
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
		std::cout << "3 - Salir" << std::endl;
		std::cout << "> ";

		std::cin >> opcion;

		if (opcion == 1)
			agregarTarea();
		else if (opcion == 2)
			mostrarTareas();

	} while (opcion != 3);

}