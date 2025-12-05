#include <iostream>
#include <fstream>
#include <stdexcept>

void leerArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + nombreArchivo);
    }

    archivo.close();
}

void testFileException() {
    try {
        leerArchivo("datos.txt");
        std::cout << "Lectura completada correctamente.\n";
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error de ejecución: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error general: " << e.what() << std::endl;
    }

}
