#include <iostream>
#include <vector>

template <typename T>
void printArray(std::vector<T>& arr) {
    for (auto& e : arr)
        std::cout << e << " ";
    std::cout << std::endl;
}