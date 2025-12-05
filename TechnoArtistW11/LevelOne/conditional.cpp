#include <iostream>
#include <vector>

void gotoTest() {

}

void loop(void) {
	int opcion = 0;
	int arr[7] = { 2, 4, 0, 1, 9, 3, 5 };

	int val = 1;

	for (int i = 0; i < 7; i++) {

		if (arr[i] == 0) {
			continue;
		}
		std::cout << "Iteracion " << val/arr[i] << std::endl;
	}

}

void condicionales() {
	int opcion = 4;

	//loop();
	gotoTest();
	/*
	switch (opcion) {
	case 4:
		std::cout << "Opcion 4" << std::endl;
		break;
	case 5:
		std::cout << "Opcion 5" << std::endl;
		break;
	default:
		std::cout << "Opcion invalida" << std::endl;
		break;
	}

	if (opcion == 4) {
		std::cout << "Opcion 4" << std::endl;
	}
	else if (opcion == 5) {
		std::cout << "Opcion 5" << std::endl;
	}
	else {
		std::cout << "Opcion invalida" << std::endl;
	}
	*/
}
