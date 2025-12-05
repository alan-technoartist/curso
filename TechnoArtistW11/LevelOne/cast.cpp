#include <iostream>

void staticCast(void) {
	int intVar = 4;
	float floatVar = static_cast<float>(intVar);
}

void dynamicCast(void) {
}

void reinterpretCast(void) {
}

int func1(int p1) {
	return p1 + 3;
}

float func1(float p1) {
	return p1 + 0.5;
}