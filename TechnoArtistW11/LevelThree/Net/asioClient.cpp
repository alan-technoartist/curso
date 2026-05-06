#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

void testAsioClient() {
        // Objeto para despacho de eventos asíncronos
        io_context io_context;

        // Socket TCP
        ip::tcp::socket socket(io_context);

        // "Resolutor" traduce (resuelve) a direcciones IP + puerto
        ip::tcp::resolver resolver(io_context);

        resolver.async_resolve("localhost", "5000",
            [&socket](boost::system::error_code ec, ip::tcp::resolver::results_type results) {
                if (ec) return;

                std::cout << "Conectando al servidor..." << std::endl;

                boost::asio::async_connect(socket, results,
                    [&socket](boost::system::error_code ec, const ip::tcp::endpoint& endpoint) {
                        if (ec) return;

                        std::cout << "Leyendo datos..." << std::endl;

                        // Usamos shared_ptr para que el buffer viva lo suficiente
                        auto buffer = std::make_shared<std::array<char, 128>>();

                        socket.async_read_some(boost::asio::buffer(*buffer),
                            [buffer](boost::system::error_code ec, std::size_t bytes_transferred) {
                                if (!ec) {
                                    std::cout << "Datos del servidor: ";
                                    // Escribimos solo los bytes recibidos para evitar basura
                                    std::cout.write(buffer->data(), bytes_transferred);
                                    std::cout << std::endl;
                                }
                            });
                    });

            });

        std::cout << "Encendiendo motor de ASIO" << std::endl;

        // Encender motor de eventos asíncronos
        io_context.run();
}