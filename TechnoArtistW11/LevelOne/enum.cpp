#include <iostream>

enum class EstadoAntena {
	ON,
	OFF
};

std::string estadoAString(EstadoAntena edo) {
	if (edo == EstadoAntena::ON)
		return "ON";
	else
		return "OFF";
}

enum class EstadoPoder {
	ON,
	OFF,
	ASLEEP
};

void pruebaEnum(void) {
	//EstadoPoder estadoPoder;  // enum clasico
	EstadoAntena estadoAntena = EstadoAntena::OFF; // enum class (con ambito)

	if (estadoAntena == EstadoAntena::ON) {
		
	}
	else if (estadoAntena == EstadoAntena::OFF) {
	
	}
	else {
		
	}
}

void enumClass(void) {
	pruebaEnum();
}

