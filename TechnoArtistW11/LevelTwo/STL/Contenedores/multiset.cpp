#include <iostream>
#include <set>

void testMultiset() {
	std::multiset<int> billetera;

	billetera.insert(20);
	billetera.insert(20);
	billetera.insert(50);
	billetera.insert(20);
	billetera.insert(50);
	billetera.insert(100);

	for (const auto& billete : billetera) {
		std::cout << billete << std::endl;
	}

	auto numElementos = billetera.count(20); // 20 = llave

	std::cout << "Elementos: " << numElementos << std::endl;

	//billetera.erase(20);

	//for (const auto& billete : billetera) {
	//	std::cout << billete << std::endl;
	//}

	auto elemento = billetera.find(20);

	if (elemento != billetera.end())
		billetera.erase(elemento);
	else
		std::cout << "Elemento no encontrado" << std::endl;

	for (const auto& billete : billetera) {
		std::cout << billete << std::endl;
	}

}