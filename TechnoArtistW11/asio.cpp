// 
// Instalación de boost:
// 
// Instalar vcpkg:
// https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd
// Instalar boost:
// 1. vcpkg install boost-asio
// 2. vcpkg integrate install

#include <boost/asio.hpp>

using namespace boost::asio;

void testAsio() {
	// Objeto para despacho de eventos asíncronos
	io_context io_context;

	// Socket TCP
	ip::tcp::socket socket(io_context);

	// "Aceptador" escucha en un puerto a la espera de clientes
	ip::tcp::acceptor aceptador(io_context, ip::tcp::endpoint(ip::tcp::v4(), 5000));

	// "Listen", el programa espera la conexión de un cliente
	aceptador.accept(socket);

	boost::asio::write(socket, boost::asio::buffer("Hola"));
}