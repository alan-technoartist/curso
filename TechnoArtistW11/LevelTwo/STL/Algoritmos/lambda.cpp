#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

double desviacionEstandar(const std::vector<double>& datos) {

    // 1. Calcular la suma total
    double suma = std::accumulate(datos.begin(), datos.end(), 0.0);

    // 2. Calcular la media
    double media = suma / datos.size();

    // 3. Calcular la suma del cuadrado de las diferencias
    // Usamos una función Lambda: [media](acumulador, valor)
    double sumaDiferencias = std::accumulate(datos.begin(), datos.end(), 0.0,
        [media](double acc, double val) {
            return acc + std::pow(val - media, 2);
        });

    // 4. Desviación
    return std::sqrt(sumaDiferencias / (datos.size() - 1));
}

void testLambda() {
    int entero = 10;
    int x = 2;
    int y = 8;

    std::vector<double> muestras = { 2.6, 1.5, 1.7, 9.0, 7.3, 4000.1 };

    auto imprimirEntero = [=, &entero](int p) {
        std::cout << entero << " " << x+p << " " << y << " " << std::endl;
    };

    entero += 10;

    imprimirEntero(1);

    std::cout << "Desviacion estandar de la muestra: " << desviacionEstandar(muestras) << std::endl;
}