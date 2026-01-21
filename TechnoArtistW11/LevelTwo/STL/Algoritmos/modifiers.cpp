#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

struct Heroe {
    std::string nombre;
    int salud;
    std::string estado;
};

void imprimirEquipo(const std::vector<Heroe>& heroes) {
    for (const auto& h : heroes) {
        std::cout << h.nombre << " | " << h.salud << " | " << h.estado << std::endl;
    }
}

void testModifiers() {

    std::vector<Heroe> equipo = {
        { "Personaje3", 10,  "HERIDO"},
        { "Personaje5", 0,   "FALLECIDO"},
        { "Personaje1", 0,   "FALLECIDO"},
        { "Personaje4", 100, "SANO"},
        { "Personaje2", 50,  "HERIDO"}
    };

    std::cout << "Estado del equipo: " << std::endl;
    imprimirEquipo(equipo);

    // 1. ENTIERRO (std::erase_if)
    std::erase_if(equipo, [](Heroe& e) { return (e.estado == "FALLECIDO"); });

    // 2. CURA (std::for_each actuando como replace lógico)
    //    std::for_each puede trabajar en paralelo y basado en rangos del contenedor
    std::for_each(equipo.begin(), equipo.end(),
        [](Heroe& h) {
            // realizar operación
            if (h.estado != "SANO")
                h.salud += 30;

            if (h.salud > 100)
                h.salud = 100;
        });

    std::cout << "Despues de entierros y curaciones: " << std::endl;
    imprimirEquipo(equipo);

    // 3. ORDENAR AL EQUIPO EQUIPO POR NOMBRE (std::sort)
    std::sort(equipo.begin(), equipo.end(),
        [](Heroe& a, Heroe& b) {
            return (a.nombre < b.nombre);
        });

    std::cout << "Equipo ordenado por nombre: " << std::endl;
    imprimirEquipo(equipo);

    Heroe lider = { "Personaje5", 0, "" };

    // 4. PASAR LISTA (std::binary_search) O(log n)
    bool existeLider = std::binary_search(equipo.begin(), equipo.end(), lider,
        [](const Heroe& a, const Heroe& b) {
            return (a.nombre < b.nombre);
        });

    if (existeLider) {
        std::cout << "Lider esta vivo!" << std::endl;
    }
    else {
        std::cout << "Lider no encontrado" << std::endl;
    }

    // 5. INICIATIVA (std::shuffle)
    std::random_device rd;
    std::mt19937 motor(rd());
    std::shuffle(equipo.begin(), equipo.end(), motor);

    std::cout << "Equipo barajeado: " << std::endl;
    imprimirEquipo(equipo);

    // 6. ESTRATEGIA (std::rotate/std::reverse)
    std::reverse(equipo.begin(), equipo.end());

    std::cout << "Orden invertido: " << std::endl;
    imprimirEquipo(equipo);

    // 7. CALCULAR PUNTAJES
    std::vector<int> puntajes_combate;

    std::transform(equipo.begin(), equipo.end(), std::back_inserter(puntajes_combate),
        [](const Heroe& h) {
            int score = h.salud * 10;
            if (h.estado == "HERIDO") {
                score /= 2; // Penalización
            }
            return score;
        }
    );

    std::cout << "Puntajes: " << std::endl;
    for (int i = 0; i < equipo.size(); i++) {
        std::cout << equipo[i].nombre << " -> Score: " << puntajes_combate[i] << std::endl;
    }
}