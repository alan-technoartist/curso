#include <iostream>
#include <fstream>

void testBMP() {
    const int ancho = 256;
    const int alto = 256;
    const int tamanoCabecera = 54;
    const int tamanoArchivo = tamanoCabecera + (ancho * alto * 3);

    // Cabecera estándar de 54 bytes para un BMP de 24 bits
    unsigned char cabecera[54] = {
        'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0, 40,0,0,0,
        0,0,0,0, 0,0,0,0, 1,0, 24,0, 0,0,0,0, 0,0,0,0,
        0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
    };

    // Configurar tamaño y dimensiones en la cabecera
    cabecera[2] = (unsigned char)(tamanoArchivo);
    cabecera[3] = (unsigned char)(tamanoArchivo >> 8);
    cabecera[4] = (unsigned char)(tamanoArchivo >> 16);
    cabecera[5] = (unsigned char)(tamanoArchivo >> 24);

    cabecera[18] = (unsigned char)(ancho);
    cabecera[19] = (unsigned char)(ancho >> 8);
    cabecera[22] = (unsigned char)(alto);
    cabecera[23] = (unsigned char)(alto >> 8);

    std::ofstream archivo("imagen.bmp", std::ios::binary);

    if (archivo) {
        // 1. Escribir la cabecera (los metadatos)
        archivo.write(reinterpret_cast<char*>(cabecera), 54);

        // 2. Escribir los píxeles (el color)
        // Definimos el color Verde (B=0, G=255, R=0)
        unsigned char azul = 0;
        unsigned char verde = 255;
        unsigned char rojo = 0;

        for (int i = 0; i < (ancho * alto); i++) {
            archivo.put(azul);
            archivo.put(verde);
            archivo.put(rojo);
        }

        archivo.close();
        std::cout << "Imagen BMP creada!" << std::endl;
    }
    else {
        std::cerr << "Error al crear el archivo" << std::endl;
    }
}