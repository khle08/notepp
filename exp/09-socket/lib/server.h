#ifndef _SERVER_H_
#define _SERVER_H_

#include <iostream>
#include <cstring>
#include <unistd.h>    // for "usleep"
#include <arpa/inet.h>
#include <sys/socket.h>

int server_sender() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Set up server address
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    // Bind the socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket to address." << std::endl;
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Failed to listen on socket." << std::endl;
        return 1;
    }

    std::cout << "Server is listening for incoming connections..." << std::endl;

    // Accept a client connection
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
    if (clientSocket == -1) {
        std::cerr << "Failed to accept client connection." << std::endl;
        return 1;
    }

    std::cout << "Client connected." << std::endl;

    // Send a message to the client
    const char *message = "Hello, client!";
    if (send(clientSocket, message, strlen(message), 0) == -1) {
        std::cerr << "Failed to send message to client." << std::endl;
    }

    // Close the sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}


int server_receiver() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Set up server address
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    // Bind the socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket to address." << std::endl;
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Failed to listen on socket." << std::endl;
        return 1;
    }

    std::cout << "Server is listening for incoming connections..." << std::endl;

    // Accept a client connection
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
    if (clientSocket == -1) {
        std::cerr << "Failed to accept client connection." << std::endl;
        return 1;
    }

    std::cout << "Client connected." << std::endl;

    // Receive a message from the client
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead == -1) {
        std::cerr << "Failed to receive message from client." << std::endl;
        return 1;
    }

    std::cout << "Received message from client: " << buffer << std::endl;

    // Close the sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}


#endif
