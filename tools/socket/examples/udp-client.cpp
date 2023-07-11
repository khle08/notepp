#include "udpsocket.hpp"
#include <iostream>
#include <string>

#include <vector>
#include <cerrno>
#include <stdlib.h>

#include "strcvt.hpp"

#define print(x) std::cout << x << std::endl;

using namespace std;


int main()
{
    // Our constants:
    constexpr const char* IP = "192.168.110.64";
    constexpr uint16_t PORT = 8888;

    // Initialize socket.
    UDPSocket<100> udpSocket(true); // "true" to use Connection on UDP. Default is "false".
    udpSocket.Connect(IP, PORT);

    // Send String:
    udpSocket.Send("ABCDEFGH");
    //udpSocket.SendTo("ABCDEFGH", IP, PORT); // If you want to connectless

    udpSocket.onRawMessageReceived = [&](const char* message, int length, string ipv4, uint16_t port) {
        cout << ipv4 << ":" << port << " => " << message << "(" << length << ")" << endl;
    };
    
    // If you want to use std::string:
    /*
    udpSocket.onMessageReceived = [&](string message, string ipv4, uint16_t port) {
        cout << ipv4 << ":" << port << " => " << message << endl;
    };
    */

    // std::vector<uint8_t> v = {0xFe, 0xAB};
    // uint8_t msg[v.size()];
    // for (int i = 0; i < v.size(); i++) {
    //     msg[i] = v[i];
    // }
    // ==========
    unsigned char ii = 0;
    char msg[11];// = { 0 };
    msg[ii++] = (char)0xFF;
    msg[ii++] = 0x5c;
    msg[ii++] = 0x4B;


    const char *in_utf8 = "静态模式";
    print(strlen(in_utf8));
    char out[16];
    int rc = u2g(in_utf8, strlen(in_utf8), out, 16);
    for (int i = 0; i < 8; i++) {
        msg[ii++] = out[i];
    }


    // uint8_t data[v.size() + 16];
    // for (int i = 0; i < v.size() + 16; i++) {
    //     if (i < v.size()) {
    //         data[i] = v[i];
    //     } else {
    //     data[i] = (uint8_t)out[i];
    //     }
    // }

    // You should do an input loop, so the program won't terminate immediately
    string input;
    getline(cin, input);
    while (input != "exit")
    {
        // print_bytes(input);
        

        // uint8_t msg[3000] = {0xFe, 0x5c, 93, 0, 0, 0};
        size_t length = sizeof(msg);
        print(length);

        udpSocket.Send(msg, length);
        getline(cin, input);
    }

    // Close the socket.
    udpSocket.Close();

    return 0;
}
