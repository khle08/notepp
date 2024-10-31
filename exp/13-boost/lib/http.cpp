
#include "http.h"


http::response<http::string_body> handle_request(http::request<http::string_body> const& req)
{
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, "Boost.Beast HTTP Server");
    res.set(http::field::content_type, "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = "<html><body><h1>Hello, World!</h1></body></html>";
    res.prepare_payload();
    return res;
}


void Session::start()
{
    read_request();
}


void Session::read_request()
{
    auto self = shared_from_this();
    http::async_read(socket_, buffer_, req_,
        [self](beast::error_code ec, std::size_t bytes_transferred) {
            if(!ec) self->write_response();
        });
}


void Session::write_response()
{
    auto response = handle_request(req_);
    auto self = shared_from_this();
    http::async_write(socket_, response,
        [self](beast::error_code ec, std::size_t) {
            self->socket_.shutdown(tcp::socket::shutdown_send, ec);
        });
}


Listener::Listener(net::io_context& ioc, tcp::endpoint endpoint)
    : acceptor_(ioc), socket_(ioc)
{
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(net::socket_base::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();
}


void Listener::start()
{
    accept();
}


void Listener::accept()
{
    acceptor_.async_accept(socket_, [&](beast::error_code ec) {
        if (!ec) std::make_shared<Session>(std::move(socket_))->start();
        accept();
    }
}

