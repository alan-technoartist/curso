#include <iostream>

namespace espacio1 {
	namespace espacio2 {
		int variableEspacio = 1;

		void miembroEspacio() {
			std::cout << "df";
		}
	}
	int variableEspacio;
}

namespace espacio2 {

	int variableEspacio = 1;

	void miembroEspacio() {

	}

}

//using namespace espacio2;

void nameSpace() {
	espacio2::variableEspacio = 3;
	espacio1::variableEspacio = 2;
	espacio1::espacio2::variableEspacio = 3;
}