#include <iostream>
#include <set>

class Alumno {
public:
	Alumno (std::string n, float c) : 
		nombre(n),
		calificacion(c)
	{ }

	std::string nombre;
	float calificacion;

};

struct ComparadorAlumnos {
	bool operator()(const Alumno& a1, const Alumno& a2) const {
		return (a1.nombre < a2.nombre);
	}
};

void testSet() {
	std::set<Alumno, ComparadorAlumnos> alumnos;

	const Alumno& alumno1 = Alumno("Alan Bautista", 6.0);
	const Alumno& alumno2 = Alumno("Aarmando Cruz", 9.0);
	const Alumno& alumno3 = Alumno("Julian Ramirez", 8.0);
	const Alumno& alumno4 = Alumno("Julian Ramirez", 5.0);

	// Alumno1 < Alumno2 => true/false
	// Alumno1.operator<(Alumno2) => true/false

	auto resultado = alumnos.insert(alumno1);

	if (resultado.second == false) {
		std::cout << "Alumno 1 no pudo insertarse" << std::endl;
	}

	alumnos.insert(alumno2);
	alumnos.insert(alumno3);

	resultado = alumnos.insert(alumno4);

	if (resultado.second == false) {
		std::cout << "Alumno 4 no pudo insertarse" << std::endl;
	}

	for (const auto& alumno : alumnos) {
		std::cout << alumno.calificacion << std::endl;
	}

}