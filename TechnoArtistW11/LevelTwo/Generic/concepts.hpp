#include <iostream>
#include <concepts>

// Documentacion:
// https://en.cppreference.com/w/cpp/header/concepts.html

template<typename T>
concept Numero = std::integral<T> || std::floating_point<T>;

template <Numero T1, Numero T2>
T1 sumarNumeros(T1 a, T2 b) {
	return a + b;
}

template<typename T>
concept ConTamano = requires(T a) {
	{ a.size() } -> std::convertible_to<int>;
};

template<typename T>
concept AritmeticoEspecifico = requires(T a, T b) {
	{ a + b } -> std::same_as<T>;
	{ a - b } -> std::same_as<T>;
};

template <ConTamano T>
void imprimeTamano(T obj) {
	std::cout << obj.size() << std::endl;
}

template <AritmeticoEspecifico T>
T algoritmoGenerico(T a, T b) {
	T c = a + b;
	c -= a;

	return c;
}

template <typename T>
concept Comparable = requires(T a, T b) {
	{ a < b } -> std::same_as<bool>;
	{ a > b } -> std::same_as<bool>;
	{ a == b } -> std::same_as<bool>;
};

template <Comparable T>
T menor(T a, T b) {
	return (a < b) ? a : b;
}

void imprimirCaracter() {
	char caracter = 50;

	std::cout << caracter << std::endl;
}