#ifndef _HTTP_H_
#define _HTTP_H_

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

// For convenience
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = net::ip::tcp;               // from <boost/asio/ip/tcp.hpp>


// This function produces an HTTP response for the given request.
http::response<http::string_body> handle_request(http::request<http::string_body> const& req);


// Session to handle a single connection.
class Session : public std::enable_shared_from_this<Session>
{
public:
    explicit Session(tcp::socket socket) : socket_(std::move(socket)) {}

    void start();

private:
    tcp::socket socket_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;

    void read_request();
    void write_response();
};


// Listener to accept incoming connections.
class Listener : public std::enable_shared_from_this<Listener>
{
public:
    Listener(net::io_context& ioc, tcp::endpoint endpoint);

    void start();

private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;

    void accept();
};


#endif
