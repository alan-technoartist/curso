
#include <iostream>
#include <fstream>
#include <string>

void agregarTarea() {
	std::ofstream archivo("ejemplo.txt", std::ios::app);

	if (archivo.is_open()) {
		std::string tarea;

		std::cout << "Introduzca tarea: ";
		std::cin.ignore();
		std::getline(std::cin, tarea);

		archivo << tarea << std::endl;

		archivo.close();
	}
	else {
		std::cerr << "Error al abrir el archivo" << std::endl;
	}

}

void mostrarTareas() {
	std::ifstream lectura("ejemplo.txt");
	std::string datosArchivo;

	if (lectura.is_open()) {
		while (std::getline(lectura, datosArchivo)) {
			std::cout << datosArchivo << std::endl;
		}
		lectura.close();
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