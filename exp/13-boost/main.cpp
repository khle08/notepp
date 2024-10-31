
#include <string>
#include <iostream>

#include <boost/beast/core.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <boost/beast/websocket.hpp>

#include "http.h"

namespace beast = boost::beast;            // boost/beast.hpp
namespace websocket = beast::websocket;    // boost/beast/websocket.hpp
namespace net = boost::asio;               // boost/asio.hpp
using tcp = net::ip::tcp;                  // boost/asio/ip/tcp.hpp


void websocket_client(const std::string& host, const std::string& port, const std::string& router) {
    try {
        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        websocket::stream<tcp::socket> ws(ioc);

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        net::connect(ws.next_layer(), results.begin(), results.end());

        // Perform the WebSocket handshake
        ws.handshake(host, router);

        // Send a message
        std::string text = "Hello from WebSocket client";
        ws.write(net::buffer(text));

        while (true) {
            // Buffer to hold the incoming message
            beast::flat_buffer buffer;

            // Receive WebSocket response
            ws.read(buffer);
            std::cout << "Received: " << beast::make_printable(buffer.data()) << std::endl;
            
            std::string result(static_cast<const char*>(buffer.data().data()), buffer.size());
            if (result == "quit" || result == "exit") {
                break;
            }
        }

        // Close the WebSocket connection
        ws.close(websocket::close_code::normal);
    }
    catch (const beast::system_error& se) {
        std::cerr << "Error: " << se.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    // std::string host = "192.168.110.50";  // Change to your server's IP/hostname
    // std::string port = "8000";            // Change to your server's port
    websocket_client("192.168.110.50", "8000", "/ws/abcd");

    // BUG ?????
    // try {
    //     // Setup the I/O context and listener
    //     auto const address = net::ip::make_address("0.0.0.0");
    //     unsigned short port = 8002;

    //     net::io_context ioc{1};

    //     // Create and start the listener
    //     std::make_shared<Listener>(ioc, tcp::endpoint{address, port})->start();

    //     // Run the I/O service
    //     ioc.run();
    // } catch (std::exception const& e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    //     return EXIT_FAILURE;
    // }

    return 0;
}
