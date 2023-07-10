#pragma once

#include <map>
#include <thread>
#include <vector>

#include "tcpsocket.hpp"

using IP_MAP = std::map<std::pair<std::string, int>, int>;


template <uint16_t BUFFER_SIZE = AS_DEFAULT_BUFFER_SIZE>
class TCPServer : public BaseSocket
{
public:
    // Event Listeners:
    std::function<void(TCPSocket<BUFFER_SIZE>*)> onNewConnection = [](TCPSocket<BUFFER_SIZE>* sock){FDR_UNUSED(sock)};

    explicit TCPServer(FDR_ON_ERROR): BaseSocket(onError, SocketType::TCP)
    {
        int opt = 1;
        setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
        setsockopt(this->sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(int));
    }

    // =================================================================
    // Send raw bytes
    ssize_t Send(std::string ip, int port, const char* bytes, size_t byteslength)
    {
        int ns = ipPortMap[std::make_pair(ip, port)];
        return send(ns, bytes, byteslength, 0);
    }
    // Send std::string
    ssize_t Send(std::string ip, int port, const std::string& message)
    {
        return this->Send(ip, port, message.c_str(), message.length());
    }

    // Send raw bytes
    bool SendAll(const char* bytes, size_t byteslength)
    {
        for (IP_MAP::iterator it = ipPortMap.begin(); it != ipPortMap.end(); it++) {
            send(it->second, bytes, byteslength, 0);
            // std::cout << it->second << std::endl;
        }
        return true;
    }
    // Send std::string
    bool SendAll(const std::string& message)
    {
        return this->SendAll(message.c_str(), message.length());
    }
    // =================================================================

    // Bind the custom address & port of the server.
    void Bind(const char* address, uint16_t port, FDR_ON_ERROR)
    {
        int status = inet_pton(AF_INET, address, &this->address.sin_addr);
        switch (status) {
            case -1:
                onError(errno, "Invalid address. Address type not supported.");
                return;
            case 0:
                onError(errno, "AF_INET is not supported. Please send message to developer.");
                return;
            default:
                break;
        }

        this->address.sin_family = AF_INET;
        this->address.sin_addr.s_addr = INADDR_ANY;
        this->address.sin_port = htons(port);

        if (bind(this->sock, (const sockaddr*)&this->address, sizeof(this->address)) == -1)
        {
            onError(errno, "Cannot bind the socket.");
            return;
        }
    }
    // Bind the address(0.0.0.0) & port of the server.
    void Bind(uint16_t port, FDR_ON_ERROR) { this->Bind("0.0.0.0", port, onError); }

    // Start listening incoming connections.
    void Listen(FDR_ON_ERROR)
    {
        if (listen(this->sock, 20) == -1)
        {
            onError(errno, "Error: Server can't listen the socket.");
            return;
        }

        // =============================================================
        // Both ways works
        // std::thread t(Accept, this, std::ref(TCPServer::ipPortMap), onError);
        std::thread t(Accept, this, std::ref(this->ipPortMap), onError);
        // =============================================================
        t.detach();
    }

private:
    // =================================================================
    IP_MAP ipPortMap;
    // =================================================================

    static void Accept(TCPServer<BUFFER_SIZE>* server, IP_MAP& ipm, FDR_ON_ERROR)
    {
        sockaddr_in newSocketInfo;
        socklen_t newSocketInfoLength = sizeof(newSocketInfo);

        int newSocketFileDescriptor = -1;
        while (true)
        {
            newSocketFileDescriptor = accept(server->sock, (sockaddr*)&newSocketInfo, &newSocketInfoLength);
            if (newSocketFileDescriptor == -1)
            {
                if (errno == EBADF || errno == EINVAL) {
                    return;
                }

                onError(errno, "Error while accepting a new connection.");
                return;
            }

            TCPSocket<BUFFER_SIZE>* newSocket = new TCPSocket<BUFFER_SIZE>(onError, newSocketFileDescriptor);
            newSocket->deleteAfterClosed = true;
            newSocket->setAddressStruct(newSocketInfo);

            server->onNewConnection(newSocket);
            newSocket->Listen();

            // =========================================================
            std::pair<std::string, int> p = std::make_pair(newSocket->remoteAddress(),
                                                           newSocket->remotePort());
            ipm[p] = newSocketFileDescriptor;
            // std::cout << p.first << ":" << p.second << std::endl;
            // =========================================================
        }
    }
};

