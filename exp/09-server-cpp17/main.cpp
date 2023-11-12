
#include <iostream>
#define print(x) std::cout << x << std::endl;

// ======================================================================

/* We simply call the root header file "App.h", giving you uWS::App and uWS::SSLApp */
#include "App.h"

/* This is a simple WebSocket echo server example.
 * You may compile it with "WITH_OPENSSL=1 make" or with "make" */


int main() {
    struct UserData {

    };

    // ref: https://stackoverflow.com/questions/67298358/error-no-matching-function-for-call-to-uwstemplatedappfalsewsmainus
    // tip -> true: for "SSLApp" ; false: for "App"
    uWS::TemplatedApp<true>::WebSocketBehavior<UserData> wsb = {
        /* Just a few of the available handlers */
        .open = [](auto *ws) {
            /* MQTT syntax */
            ws->subscribe("sensors/+/house");
        },
        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
            ws->send(message, opCode);
            // print(opCode);  // 1
        }
    };

    uWS::SSLApp({
        .key_file_name = "misc/key.pem",
        .cert_file_name = "misc/cert.pem",
        // .passphrase = "1234"

    }).get("/hello", [](auto *res, auto *req) {
        res->end("Hello!");

    }).ws<UserData>("/ws", std::move(wsb)).listen(9001, [](auto *listenSocket) {
        if (listenSocket) {
            std::cout << "Listening on port " << 9001 << std::endl;
        }
    }).run();

    std::cout << "Failed to listen on port 9001" << std::endl;
}


// ======================================================================


// #include "App.h"

// /* Note that uWS::SSLApp({options}) is the same as uWS::App() when compiled without SSL support */

// int main() {
//     /* Overly simple hello world app */

//     uWS::SSLApp({
//         .key_file_name = "misc/key.pem",
//         .cert_file_name = "misc/cert.pem",
//         .passphrase = "1234"

//     }).get("/*", [](auto *res, auto *req) {
//         res->end("Hello world!");

//     }).listen(3000, [](auto *listen_socket) {
//         if (listen_socket) {
//             std::cout << "Listening on port " << 3000 << std::endl;
//         }
//         print("get");

//     }).run();

//     std::cout << "Failed to listen on port 3000" << std::endl;
// }


