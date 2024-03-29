
#include <iostream>
#include <cstring>
#include <unistd.h>    // for "usleep"
#include <arpa/inet.h>
#include <sys/socket.h>


int client_receiver() {
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Set up server address
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Failed to convert IP address." << std::endl;
        return 1;
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to connect to server." << std::endl;
        return 1;
    }

    while (true) {
        // Receive a message from the server
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead == -1) {
            std::cerr << "Failed to receive message from server." << std::endl;
            return 1;
        }

        std::cout << "Received message from server: " << buffer << std::endl;
        usleep(1 * 1000 * 1000);
    }
        
    // Close the socket
    close(clientSocket);

    return 0;
}


int client_sender() {
    // TCP: SOCK_STREAM ; UDP: SOCK_DGRAM

    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Set up server address
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8888);

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Failed to convert IP address." << std::endl;
        return 1;
    }

    // // Connect to the server (TCP only)
    // if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
    //     std::cerr << "Failed to connect to server." << std::endl;
    //     return 1;
    // }

    // // Send a message to the server (TCP)
    // const char *message = "Hello, server!";
    // if (send(clientSocket, message, strlen(message), 0) == -1) {
    //     std::cerr << "Failed to send message to server." << std::endl;
    // }

    // Send a message to the server (UDP)
    uint8_t msg[] = {0xFF, 0xAA};
    size_t length = sizeof(msg);

    if (sendto(clientSocket, msg, length, 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to send message to server." << std::endl;
    }

    // Close the socket
    close(clientSocket);

    return 0;
}


int main()
{
    // client_receiver();
    client_sender();

    return 0;
}

