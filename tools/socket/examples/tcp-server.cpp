#include <iostream>

#include "tcpserver.hpp"


int server(int port)
{
    // Initialize server socket..
    TCPServer<> tcpServer;

    // When a new client connected:
    tcpServer.onNewConnection = [&](TCPSocket<> *newClient) {
        std::cout << "[O] New client <= ";
        std::cout << newClient->remoteAddress() << ":" << newClient->remotePort() << std::endl;

        newClient->onMessageReceived = [newClient](std::string msg) {
            std::cout << "[MSG] " << newClient->remoteAddress() << ":" << newClient->remotePort() << " => " << msg << std::endl;
            newClient->Send("OK!");
        };
        
        // // If you want to use raw bytes
        // newClient->onRawMessageReceived = [newClient](const char* msg, int length) {
        //     std::cout << "[MSG] " << newClient->remoteAddress() << ":" << newClient->remotePort() << " => " << msg << "(" << length << ")" << std::endl;
        //     newClient->Send("OK!");
        // };

        newClient->onSocketClosed = [newClient](int errorCode) {
            std::cout << "[X] Disconnected: " << newClient->remoteAddress() << ":" << newClient->remotePort() << " => " << errorCode << std::endl;
            std::cout << std::flush;
        };
    };

    // Bind the server to a port.
    tcpServer.Bind(port, [](int errorCode, std::string errorMessage) {
        // BINDING FAILED:
        std::cout << errorCode << " : " << errorMessage << std::endl;
    });

    // Start Listening the server.
    tcpServer.Listen([](int errorCode, std::string errorMessage) {
        // LISTENING FAILED:
        std::cout << errorCode << " : " << errorMessage << std::endl;
    });

    std::string input;
    getline(std::cin, input);
    while (input != "exit")
    {
        tcpServer.SendAll(input);
        getline(std::cin, input);
    }

    // Close the server before exiting the program.
    tcpServer.Close();
    return 0;
}


int main()
{

    server(8888);
    return 0;
}
