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

        auto endpoint = resolver.resolve("localhost", "5000");

        std::cout << "Conectando al servidor..." << std::endl;

        boost::asio::connect(socket, endpoint);

        char buffer[128];

        socket.read_some(boost::asio::buffer(buffer));

        std::cout << "Datos del servidor: ";

        std::cout << buffer << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(5));

}