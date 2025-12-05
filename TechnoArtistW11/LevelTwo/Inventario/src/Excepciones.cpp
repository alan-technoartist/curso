#include "../include/Excepciones.hpp"

namespace InventarioNuevo {
	
	NoEncontradoExcp::NoEncontradoExcp(std::string m) : mensaje(m) {
		// Constructor
	}

	const char* NoEncontradoExcp::what() const noexcept {
		return mensaje.c_str();
	}

}