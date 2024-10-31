
#include "HttpServer.h"


HttpServer::HttpServer(net::io_context& ioc, const std::string& address, unsigned short port)
    : acceptor_(ioc, tcp::endpoint(net::ip::make_address(address), port))
{
    init_routes();
}


void HttpServer::run()
{
    do_accept();
}


void HttpServer::do_accept()
{
    acceptor_.async_accept([this](beast::error_code ec, tcp::socket socket) {
        on_accept(ec, std::move(socket));
    });
}


void HttpServer::on_accept(beast::error_code ec, tcp::socket socket)
{
    if (!ec) {
        beast::tcp_stream stream(std::move(socket));
        beast::flat_buffer buffer;  // Add a buffer to hold incoming data
        http::request<http::string_body> req;
        
        // Now pass both the stream and buffer to `http::read`
        http::read(stream, buffer, req);
        handle_request(stream, req);
    }
    do_accept();
}


void HttpServer::init_routes()
{
    routes_["/"] = [](http::response<http::string_body>& res) {
        res.body() = "<html><body><h1>Welcome to Home Page</h1></body></html>";
    };
    routes_["/data"] = [](http::response<http::string_body>& res) {
        res.body() = "<html><body><h1>Data: Sample data from Model</h1></body></html>";
    };
    routes_["/about"] = [](http::response<http::string_body>& res) {
        res.body() = "<html><body><h1>About: Information about this server</h1></body></html>";
    };
}


void HttpServer::handle_request(beast::tcp_stream& stream, http::request<http::string_body>& req)
{
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, "Boost.Beast");
    res.set(http::field::content_type, "text/html");

    auto it = routes_.find(std::string(req.target()));
    if (it != routes_.end()) {
        it->second(res);
    } else {
        res.result(http::status::not_found);
        res.body() = "<html><body><h1>404 - Page Not Found</h1></body></html>";
    }

    res.prepare_payload();
    http::write(stream, res);
    stream.socket().shutdown(tcp::socket::shutdown_send);
}
jc
