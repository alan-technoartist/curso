#pragma once
#include <vector>
#include <array>

enum class estado {
	ON,
	OFF
};

// Tipos de datos
extern void autoType(void);
extern void func1(int);
extern void func1(float);

// Condicionales
extern void condicionales(void);

// Bucles
extern void rangeFor(void);

// Conversión de tipos de datos
extern void staticCast(void);
extern void dynamicCast(void);
extern void reinterpretCast(void);

// Auto
extern void autoType(void);

// Enueraciones con ámbito (scope)
extern void enumClass(void);

// Funciones
extern void imprimirCadena(std::string);
extern int multiplicar(int, int);
extern int busqueda(std::vector<int>, int);
extern bool busqueda(std::array<estado, 3>, estado);

// std::array
extern void stdArray(void);

// std::vector
extern void stdVector(void);

// Estructuras
extern void basicStruct(void);

// Clases
extern void basicClass(void);