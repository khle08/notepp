
#include <string>
#include <iostream>

#include <boost/beast/core.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <boost/beast/websocket.hpp>

namespace beast = boost::beast;            // boost/beast.hpp
namespace websocket = beast::websocket;    // boost/beast/websocket.hpp
namespace net = boost::asio;               // boost/asio.hpp
using tcp = net::ip::tcp;                  // boost/asio/ip/tcp.hpp


void websocket_client(const std::string& host, const std::string& port) {
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
        ws.handshake(host, "/ws/abcd");

        // Send a message
        std::string text = "Hello from WebSocket client";
        ws.write(net::buffer(text));

        // Buffer to hold the incoming message
        beast::flat_buffer buffer;

        // Receive WebSocket response
        ws.read(buffer);
        std::cout << "Received: " << beast::make_printable(buffer.data()) << std::endl;

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
    std::string host = "localhost";  // Change to your server's IP/hostname
    std::string port = "8000";       // Change to your server's port

    websocket_client(host, port);

    return 0;
}
