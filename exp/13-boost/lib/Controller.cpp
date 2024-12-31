#include "Controller.h"

void Controller::process_request(http::request<http::string_body>& req, http::response<http::string_body>& res) {
    if (req.method() == http::verb::get && req.target() == "/") {
        view_.render_index(res, model_);
    } else {
        res.result(http::status::not_found);
        res.body() = "404 - Not Found";
        res.prepare_payload();
    }
}
