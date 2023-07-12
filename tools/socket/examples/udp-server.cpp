#include "udpserver.hpp"
#include <iostream>
#include <string>

#include <vector>
#include <cerrno>
#include <stdlib.h>

#include "led.h"
#include "strcvt.hpp"

#define print(x) std::cout << x << std::endl;

using namespace std;

int main()
{
    string ip;
    uint16_t pt;

    // Initialize server socket..
    UDPServer<> udpServer;

    // onMessageReceived will run when a message received with information of ip & port of sender:
    /*udpServer.onMessageReceived = [&](string message, string ipv4, uint16_t port) {
        //cout << ipv4 << ":" << port << " => " << message << endl;

        // Echo to client:
        udpServer.SendTo("A!", ipv4, port);
    };*/

    // If you want to use raw byte arrays:
    udpServer.onRawMessageReceived = [&](const char* message, int length, string ipv4, uint16_t port) {
        cout << ipv4 << ":" << port << " => " << message << "(" << length << ")" << endl;

        ip = ipv4;
        pt = port;
        // Echo to client:
        udpServer.SendTo(message, length, ipv4, port);
    };
    

    // Bind the server to a port.
    udpServer.Bind(8888, [](int errorCode, string errorMessage) {
        // BINDING FAILED:
        cout << errorCode << " : " << errorMessage << endl;
    });

    BUFFER_INFO b = interCodeBuffer(1, "testing", "eng");

    // You should do an input loop, so the program won't terminate immediately
    string input;
    getline(cin, input);
    while (input != "exit")
    {
        // udpServer.SendTo(input, ip, pt);
        udpServer.SendTo(b.arrchBuffer, b.nLen, ip, pt);
        getline(cin, input);
    }

    udpServer.Close();

    return 0;
}
