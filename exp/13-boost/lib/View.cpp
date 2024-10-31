#include "View.h"

void View::render_index(http::response<http::string_body>& res, const Model& model) {
    res.result(http::status::ok);
    res.set(http::field::server, "Boost.Beast");
    res.set(http::field::content_type, "text/html");

    res.body() = "<html><body><h1>Data: " + model.getData() + "</h1></body></html>";
    res.prepare_payload();
}
