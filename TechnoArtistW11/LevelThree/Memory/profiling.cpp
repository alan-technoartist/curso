#include <iostream>
#include <vector>
#include <thread>

namespace Profiling {
	class Arma;

	class Personaje {
	public:
		std::shared_ptr<Arma> arma;
		double datos[10000];

	};

	class Arma {
	public:
		std::weak_ptr<Personaje> personaje;
		double datos[10000];

	};
}
using namespace Profiling;

void testProfiling() {
	auto personaje1 = std::make_shared<Personaje>();
	auto arma1 = std::make_shared<Arma>();

	personaje1->arma = arma1;
	arma1->personaje = personaje1;

	arma1->personaje.lock()->datos[2];

}
