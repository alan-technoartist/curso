#include <iostream>
#include <vector>
#include <algorithm>

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
    std::for_each(equipo.begin(), equipo.end(),
        [](Heroe& h) {
            if (h.estado != "SANO")
                h.salud += 30;
        });

    std::cout << "Despues de entierros y curaciones: " << std::endl;
    imprimirEquipo(equipo);

    // TODO: std::transform

    // 3. ORDENAR AL EQUIPO EQUIPO POR NOMBRE (std::sort)
    std::sort(equipo.begin(), equipo.end(),
        [](Heroe& a, Heroe& b) {
            return (a.nombre < b.nombre);
        });

    std::cout << "Equipo ordenado por nombre: " << std::endl;
    imprimirEquipo(equipo);

    Heroe lider = { "Personaje5", 0, "" };

    // 4. PASAR LISTA (std::binary_search)
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
    //std::shuffle(equipo.begin(), equipo.end(), );

    // 6. ESTRATEGIA (std::rotate/std::reverse)
    std::reverse(equipo.begin(), equipo.end());

    std::cout << "Orden revertido: " << std::endl;
    imprimirEquipo(equipo);
}