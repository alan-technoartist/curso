#include <iostream>
#include <vector>

void stdVector(void) {
    std::vector<int> numbers = { 10, 20, 30, 40, 50 };

    numbers.push_back(60);

    std::cout << "Elemento 2: " << numbers.at(2) << std::endl;
    numbers[0] = 5;

    std::cout << "Tamano: " << numbers.size() << std::endl;

    for (int num : numbers) {
        std::cout << num << " ";
    }

    numbers.pop_back();

    for (int num : numbers) {
        std::cout << num << " ";
    }
}