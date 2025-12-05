#include <iostream>
#include <memory>

namespace SP {
	class MyClass {
	public:
		MyClass() {
			std::cout << "Creando objeto MyClass" << std::endl;
		}
		~MyClass() {
			std::cout << "Destruyendo objeto MyClass" << std::endl;
		}

		int miembro1;
		std::string miembro2;

		void metodoPublico() {
			std::cout << "Ejecutando metodo publico" << std::endl;
		}
	};
}
using namespace SP;

void testSmartPointers() {
	std::unique_ptr<MyClass> objeto2 = std::make_unique<MyClass>();

	std::shared_ptr<MyClass> objeto3 = std::make_shared<MyClass>();
	std::shared_ptr<MyClass> objeto4 = objeto3;

	objeto4->metodoPublico();
}