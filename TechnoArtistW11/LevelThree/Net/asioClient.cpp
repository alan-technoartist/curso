#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

boost::asio::awaitable<void> comunicarCliente(io_context& io_context) {

    // Socket TCP
    ip::tcp::socket socket(io_context);

    // "Resolutor" traduce (resuelve) a direcciones IP + puerto
    ip::tcp::resolver resolutor(io_context);

    std::cout << "Resolviendo ruta al servidor en \"segundo plano\"..." << std::endl;

    auto endpoint = co_await resolutor.async_resolve("192.168.0.134", "9090");

    std::cout << "Conectando al servidor \"segundo plano\"..." << std::endl;

    co_await boost::asio::async_connect(socket, endpoint);

    std::cout << "Leyendo datos \"segundo plano\"..." << std::endl;

    char buffer[128];

    co_await socket.async_read_some(boost::asio::buffer(buffer));

    std::cout << "Datos del servidor: ";

    std::cout << buffer << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));

}

void testAsioClient() {
        // Objeto para despacho de eventos asíncronos
        io_context io_context;

        boost::asio::co_spawn(io_context, comunicarCliente(io_context), detached);

        std::cout << "Encendiendo motor de ASIO" << std::endl;

        // Encender motor de eventos asíncronos
        io_context.run();
}