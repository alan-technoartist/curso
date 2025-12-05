#include <iostream>
#include <array>
#include <vector>

void imprimir(std::vector<int> vecIntLocal) {

	for (auto e : vecIntLocal) {
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

void stdArray(void) {
					
	int arrInt[5] = {2, 6, 1, 0, 2};
	std::array<int, 5> arrIntC11 = { 5, 6, 2, 4, 4 };

	//std::cout << arrInt[0] << std::endl;
	//std::cout << arrIntC11.at(0) << std::endl;

	std::vector<int> vecInt = { 1, 5, 6, 2 };

	imprimir(vecInt);

	vecInt.push_back(9);

	imprimir(vecInt);

	vecInt.pop_back();

	imprimir(vecInt);

}
