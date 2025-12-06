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

	//operator<
};

void testSet() {
	//std::set<Alumno> alumnos = {
	//	Alumno("Alan Bautista", 6.0),
	//	Alumno("Armando Cruz", 9.0)
	//};

	//alumnos.insert();
	//alumnos.insert();

}