#include "udpserver.hpp"
#include <iostream>
#include <string>

#include <vector>
#include <cerrno>
#include <stdlib.h>

#include "led.h"
#include "buzzer.h"
#include "strcvt.hpp"

#define print(x) std::cout << x << std::endl;

using namespace std;

int main()
{
    vector<string> ipVec;
    vector<uint16_t> ptVec;
    // string ip;
    // uint16_t pt;

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

        if (find(ipVec.begin(), ipVec.end(), ipv4) == ipVec.end()) {
            ipVec.push_back(ipv4);
        }
        if (find(ptVec.begin(), ptVec.end(), port) == ptVec.end()) {
            ptVec.push_back(port);
        }
        // ip = ipv4;
        // pt = port;

        // Echo to client:
        udpServer.SendTo(message, length, ipv4, port);
    };
    

    // Bind the server to a port.
    udpServer.Bind(19999, [](int errorCode, string errorMessage) {
        // BINDING FAILED:
        cout << errorCode << " : " << errorMessage << endl;
    });

    // You should do an input loop, so the program won't terminate immediately
    string input;
    getline(cin, input);
    while (input != "exit")
    {
        BUFFER_INFO b = interCodeBuffer(168111100, input.c_str(), "chi");
        BUFFER_INFO bzon = buzzer_on();
        BUFFER_INFO bzof = buzzer_off();

        for (int i = 0; i < ipVec.size(); i++) {
            udpServer.SendTo(input, ipVec[i], ptVec[i]);            
        }

        // // Corner
        // udpServer.SendTo(b.arrchBuffer, b.nLen, "192.168.110.64", 8800);

        // udpServer.SendTo(bzon.arrchBuffer, bzon.nLen, "192.168.111.62", 19999);
        // usleep(2.0 * 1000 * 1000);
        // udpServer.SendTo(bzof.arrchBuffer, bzof.nLen, "192.168.111.62", 19999);
        // usleep(0.2 * 1000 * 1000);
        // udpServer.SendTo(bzof.arrchBuffer, bzof.nLen, "192.168.111.62", 19999);
        // usleep(0.2 * 1000 * 1000);
        // udpServer.SendTo(bzof.arrchBuffer, bzof.nLen, "192.168.111.62", 19999);
        // usleep(0.2 * 1000 * 1000);
        // udpServer.SendTo(bzof.arrchBuffer, bzof.nLen, "192.168.111.62", 19999);

        // // Side wall
        // udpServer.SendTo(b.arrchBuffer, b.nLen, "192.168.111.102", 8800);

        // udpServer.SendTo(bzon.arrchBuffer, bzon.nLen, "192.168.111.63", 19999);
        // usleep(2.0 * 1000 * 1000);
        // udpServer.SendTo(bzof.arrchBuffer, bzof.nLen, "192.168.111.63", 19999);
        // usleep(0.2 * 1000 * 1000);
        // udpServer.SendTo(bzof.arrchBuffer, bzof.nLen, "192.168.111.63", 19999);
        // usleep(0.2 * 1000 * 1000);
        // udpServer.SendTo(bzof.arrchBuffer, bzof.nLen, "192.168.111.63", 19999);
        // usleep(0.2 * 1000 * 1000);
        // udpServer.SendTo(bzof.arrchBuffer, bzof.nLen, "192.168.111.63", 19999);

        getline(cin, input);
    }

    udpServer.Close();

    return 0;
}
