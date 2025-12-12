#include <iostream>
#include <unordered_map>

void testUnorderedMap() {
	// Hash maps
	std::unordered_map<std::string, float> inventario;

	inventario["1234"] = 99.0f;
	inventario["3645"] = 20.9f;
	inventario["3888"] = 5.0f;
	inventario["3434"] = 15.5f;

	for (const auto& producto : inventario) {
		std::cout << producto.first << " | " << producto.second << std::endl;
	}

	// Operacion eficiente O(1)
	auto conteoElementos = inventario.count("1234");

	// Operacion eficiente O(1)
	std::cout << inventario["3888"] << std::endl;

}
