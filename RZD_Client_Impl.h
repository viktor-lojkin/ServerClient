#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
// #define DEFAULT_PORT "27015"

class Client_Impl {
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL, *ptr = NULL, hints;
    const char* sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    
    std::string port;

    std::string fileName;
    std::string fileText;

    public:

    void Set_Port    (std::string port)     { this->port = port; }
    void Set_fileName(std::string fileName) { this->fileName = fileName; }
    void Set_fileText(std::string fileText) { this->fileText = fileText; }

    int Connect() {
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            std::cout << "WSAStartup failed with error:\n" << iResult;
            return 1;
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        PCSTR port{ this->port.c_str() };
        iResult = getaddrinfo({ "127.0.0.1" }, port, &hints, &result);
        if (iResult != 0) {
            std::cout << "getaddrinfo failed with error:\n" << iResult;
            WSACleanup();
            return 1;
        }

        for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

            ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
            if (ConnectSocket == INVALID_SOCKET) {
                std::cout << "socket failed with error:\n" << WSAGetLastError();
                WSACleanup();
                return 1;
            }

            iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
                closesocket(ConnectSocket);
                ConnectSocket = INVALID_SOCKET;
                continue;
            }
            break;
        }

        freeaddrinfo(result);

        if (ConnectSocket == INVALID_SOCKET) {
            std::cout << "Unable to connect to server" << std::endl;
            WSACleanup();
            return 1;
        }

        std::cout << "Successful connection" << std::endl;
        return 0;
    }

    void Create_File() {
        std::cout << "Request sent" << std::endl;

        // Отправка и получение данных
        std::string message = fileName + "\n" + fileText;
        iResult = send(ConnectSocket, message.c_str(), message.length(), 0);
        if (iResult == SOCKET_ERROR)
        {
            std::cout << "send fail with error: " << WSAGetLastError() << std::endl;
            closesocket(ConnectSocket);
            WSACleanup();
            return;
        }
        std::cout << "Wait for answer from Server..." << std::endl;
        iResult = recv(ConnectSocket, recvbuf, sizeof(recvbuf), 0);
        if (iResult > 0)
        {
            recvbuf[iResult] = '\0';
            std::cout << "Server answer: " << recvbuf << std::endl;
        }
        else if (iResult == 0)
        {
            std::cout << "The connection is broken " << std::endl;
            Shutdown();
        }
        else
        {
            std::cout << "Recieving data error:\n" << WSAGetLastError() << std::endl;
            Shutdown();
        }
    }

    void Shutdown() {
        iResult = shutdown(ConnectSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            return;
        }
    }
};