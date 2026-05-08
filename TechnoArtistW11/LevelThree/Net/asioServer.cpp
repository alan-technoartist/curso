// 
// Instalación de boost:
// 
// Instalar vcpkg:
// https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd
// Instalar boost:
// 1. vcpkg install boost-asio
// 2. vcpkg integrate install

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

boost::asio::awaitable<void> escribirDatos(std::shared_ptr<ip::tcp::socket> socket) {
	std::cout << "Enviando datos al cliente..." << std::endl;

	co_await boost::asio::async_write(*socket, boost::asio::buffer("Hola!"));

}

boost::asio::awaitable<void> aceptarConexion(ip::tcp::acceptor& aceptador, io_context& io_context) {
	std::cout << "Servidor escuchando..." << std::endl;

	while (true) {
		// Crear socket
		auto socket = std::make_shared<ip::tcp::socket>(io_context);

		std::cout << "Esperar por nuevo cliente..." << std::endl;

		// "Listen", el programa espera la conexión de un cliente
		co_await aceptador.async_accept(*socket);

		std::cout << "Cliente conectado!" << std::endl;

		boost::asio::co_spawn(io_context, escribirDatos(socket), detached);

	}

	std::cout << "Saliendo de funcion..." << std::endl;
}

void testAsio() {
	// Objeto para despacho de eventos asíncronos
	io_context io_context;

	// "Aceptador" escucha en un puerto a la espera de clientes
	ip::tcp::acceptor aceptador(io_context, ip::tcp::endpoint(ip::tcp::v4(), 5000));

	boost::asio::co_spawn(io_context, aceptarConexion(aceptador, io_context), detached);

	std::cout << "Encendiendo io_context..." << std::endl;

	// Encender motor de eventos asíncronos
	io_context.run();

	std::cout << "Después de run" << std::endl;

}