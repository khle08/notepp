#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <boost/beast.hpp>
#include "Model.h"
#include "View.h"

namespace http = boost::beast::http;

class Controller {
public:
    void process_request(http::request<http::string_body>& req, http::response<http::string_body>& res);

private:
    Model model_{1, "Sample data from Model"};
    View view_;
};

#endif // CONTROLLER_H
