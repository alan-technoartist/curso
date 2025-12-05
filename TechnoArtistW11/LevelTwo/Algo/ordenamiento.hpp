#include <vector>
#include <concepts>

enum class MetodoOrdenamiento {
	BURBUJA,
	SELECCION,
	INSERCION,
	QUICKSORT,
	MERGESORT
};

//template <typename T>
//concept Numerico = std::integral<T> || std::floating_point<T>;

template <typename T>
concept Ordenable = requires (T a, T b) {
	{ a < b  } -> std::convertible_to<bool>;
	{ a <= b } -> std::convertible_to<bool>;
	{ a > b  } -> std::convertible_to<bool>;
	{ a >= b } -> std::convertible_to<bool>;
	{ a == b } -> std::convertible_to<bool>;
	{ a != b } -> std::convertible_to<bool>;
};

template <Ordenable T>
void ordenar(std::vector<T>& datos, MetodoOrdenamiento metodo);

template <Ordenable T>
void imprimirVector(std::vector<T>& datos);