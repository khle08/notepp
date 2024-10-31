#ifndef VIEW_H
#define VIEW_H

#include <boost/beast.hpp>
#include "Model.h"

namespace http = boost::beast::http;

class View {
public:
    void render_index(http::response<http::string_body>& res, const Model& model);
};

#endif // VIEW_H
