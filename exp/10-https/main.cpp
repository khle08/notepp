
// ref: https://github.com/yhirose/cpp-httplib

#include <iostream>
#include <httplib.h>

#define print(x) std::cout << x << std::endl;


// Client
int main(int argc, char const *argv[])
{
    httplib::Headers headers = {
        {"Authorization", "JWT eyJhbGciOiJ..."}
    };

    // httplib::Client cli("http://192.168.110.180:8000");
    // // cli.set_default_headers(headers);

    // print("----");
    // auto res = cli.Get("/api/system/dept/", headers);
    // print(res->status)
    // print(res->body);

    // =================================================================

    // Can not put parameters for GET method to headers
    httplib::Params params = {
        {"deviceid", "9620279515"},
        {"command", "115"},
        {"cmdvalue", "hello"}
    };

    httplib::Client cli("http://yg.hxinwatch.com");
    // cli.set_default_headers(headers);

    print("----");
    auto res = cli.Get("/sdkapi/api/push/hjk/submitcommand.htm?deviceid=9620279515&command=115&cmdvalue=相关内容");

    return 0;
}


// // Server
// int main(int argc, char const *argv[])
// {
//     using namespace httplib;

//     Server svr;

//     svr.Get("/hi", [](const Request& req, Response& res) {
//         res.set_content("Hello World!", "text/plain");
//     });

//     // Match the request path against a regular expression
//     // and extract its captures
//     svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
//         auto numbers = req.matches[1];
//         res.set_content(numbers, "text/plain");
//     });

//     // Capture the second segment of the request path as "id" path param
//     svr.Get("/users/:id", [&](const Request& req, Response& res) {
//         auto user_id = req.path_params.at("id");
//         res.set_content(user_id, "text/plain");
//     });

//     // Extract values from HTTP headers and URL query params
//     svr.Get("/body-header-param", [](const Request& req, Response& res) {
//         if (req.has_header("Content-Length")) {
//             auto val = req.get_header_value("Content-Length");
//         }
//         if (req.has_param("key")) {
//             auto val = req.get_param_value("key");
//         }
//         res.set_content(req.body, "text/plain");
//     });

//     svr.Get("/stop", [&](const Request& req, Response& res) {
//         svr.stop();
//     });

//     svr.listen("localhost", 1234);
// }

