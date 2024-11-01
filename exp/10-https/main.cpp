
// ref: https://github.com/yhirose/cpp-httplib

#include <string>
#include <unistd.h>    // for "usleep"
#include <iostream>
// #include <base64.h>
#include <openssl/sha.h>

#include <httplib.h>

#include "routers.h"

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


// Server
int main(int argc, char const *argv[])
{
    float xxx = 3.1415926;

    httplib::Server server;

    router(server);

    server.listen("0.0.0.0", 1234);
}

