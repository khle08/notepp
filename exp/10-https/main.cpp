
// ref: https://github.com/yhirose/cpp-httplib

#include <string>
#include <unistd.h>    // for "usleep"
#include <iostream>
// #include <base64.h>
#include <openssl/sha.h>

#include <httplib.h>
// #include "middlewares.h"

#define print(x) std::cout << x << std::endl;


// // Client
// int main(int argc, char const *argv[])
// {
//     httplib::Headers headers = {
//         {"Authorization", "JWT eyJhbGciOiJ..."}
//     };

//     // httplib::Client cli("http://192.168.110.180:8000");
//     // // cli.set_default_headers(headers);

//     // print("----");
//     // auto res = cli.Get("/api/system/dept/", headers);
//     // print(res->status)
//     // print(res->body);

//     // =================================================================

//     // Can not put parameters for GET method to headers
//     httplib::Params params = {
//         {"deviceid", "9620279515"},
//         {"command", "115"},
//         {"cmdvalue", "hello"}
//     };

//     httplib::Client cli("http://yg.hxinwatch.com");
//     // cli.set_default_headers(headers);

//     print("----");
//     auto res = cli.Get("/sdkapi/api/push/hjk/submitcommand.htm?deviceid=9620279515&command=115&cmdvalue=相关内容");

//     return 0;
// }


// Function to validate the authentication token
bool authenticate(const httplib::Request& req)
{
    // Extract token from headers (e.g., Authorization header)
    auto auth_header = req.get_header_value("Authorization");
    const std::string expected_token = "Bearer YOUR_SECRET_TOKEN";

    // Check if the token matches the expected one
    return auth_header == expected_token;
}


// Middleware function for authentication
void authentication_middleware(const httplib::Request& req,
                               httplib::Response& res,
                               std::function<void()> next)
{
    if (authenticate(req)) {
        // If authenticated, call the next handler
        next();
    } else {
        // If not authenticated, set 401 Unauthorized status
        res.status = 401;
        res.set_content("Unauthorized", "text/plain");
    }
}


// Server
int main(int argc, char const *argv[])
{
    using namespace httplib;
    float xxx = 3.1415926;

    httplib::Server svr;

    svr.Get("/hi", [&](const Request& req, Response& res) {
        // Wrap the actual handler with the authentication middleware
        authentication_middleware(req, res, [&]() {
            // This is the actual handler for /protected
            res.set_content("Hello World!", "text/plain");
        });
    });

    // Match the request path against a regular expression
    // and extract its captures
    svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
        std::string numbers = req.matches[1];
        res.set_content(numbers, "text/plain");
    });

    // Capture the second segment of the request path as "id" path param
    svr.Get("/users/:id", [&](const Request& req, Response& res) {
        std::string user_id = req.path_params.at("id");
        res.set_content(user_id, "text/plain");
    });

    // Extract values from HTTP headers and URL query params
    svr.Get("/body-header-param", [](const Request& req, Response& res) {
        if (req.has_header("Content-Length")) {
            std::string val = req.get_header_value("Content-Length");
        }
        if (req.has_param("key")) {
            std::string val = req.get_param_value("key");
        }
        res.set_content(req.body, "text/plain");
    });

    svr.Get("/stop", [&](const Request& req, Response& res) {
        svr.stop();
    });

    svr.listen("0.0.0.0", 1234);
}

