
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


void websocket_client(const std::string& host, const std::string& port)
{
    try {
        net::io_context ioc;
    }
}

int main(int argc, char const *argv[])
{
    // ...

    return 0;
}
