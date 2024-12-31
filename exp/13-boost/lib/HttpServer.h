#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <unordered_map>
#include <functional>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;


class HttpServer
{
public:
    HttpServer(net::io_context& ioc, const std::string& address, unsigned short port);
    void run();

private:
    void do_accept();
    void on_accept(beast::error_code ec, tcp::socket socket);
    void handle_request(beast::tcp_stream& stream, http::request<http::string_body>& req);

    using Handler = std::function<void(http::response<http::string_body>&)>;
    std::unordered_map<std::string, Handler> routes_;

    tcp::acceptor acceptor_;
    void init_routes();
};

#endif // HTTPSERVER_H
