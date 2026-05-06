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

void aceptarConexion(ip::tcp::acceptor& aceptador, io_context& io_context) {
	std::cout << "Servidor escuchando..." << std::endl;

	// Crear socket
	auto socket = std::make_shared<ip::tcp::socket>(io_context);

	// "Listen", el programa espera la conexión de un cliente
	aceptador.async_accept(*socket, [&aceptador, socket, &io_context](boost::system::error_code error) {

		std::cout << "Cliente conectado!" << std::endl;

		boost::asio::async_write(*socket, boost::asio::buffer("Hola!"),
			[socket](boost::system::error_code error, std::size_t tamano) {

				std::cout << "Escribiendo datos: " << tamano << std::endl;

			});

		std::cout << "Aceptando nuevo cliente..." << std::endl;

		aceptarConexion(aceptador, io_context);

		});

	std::cout << "Saliendo de funcion..." << std::endl;


}

void testAsio() {
	// Objeto para despacho de eventos asíncronos
	io_context io_context;

	// "Aceptador" escucha en un puerto a la espera de clientes
	ip::tcp::acceptor aceptador(io_context, ip::tcp::endpoint(ip::tcp::v4(), 5000));

	aceptarConexion(aceptador, io_context);

	std::cout << "Encendiendo io_context..." << std::endl;

	// Encender motor de eventos asíncronos
	io_context.run();

	std::cout << "Después de run" << std::endl;

}