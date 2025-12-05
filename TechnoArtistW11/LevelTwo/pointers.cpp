#include <iostream>

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
};

// New & delete
void newDelete() {
	MyClass obj1;
	MyClass* obj2 = new MyClass();
	MyClass* obj3 = new MyClass[3];

	delete obj2;
	delete[] obj3;
}
