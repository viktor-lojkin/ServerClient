#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <future>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

void Wait_for_Exit(std::string& in) {
    do { std::cin >> in; } while (in != "Exit");
    exit(0);
}

int StartServer() {

    std::string in{};
    auto f = std::async(std::launch::async, [&](std::string in) {Wait_for_Exit(in); }, in);
    
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    //std::string in{};
    do {

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            recvbuf[iResult] = '\0';
            std::cout << "Data from the Client: " << recvbuf << std::endl;

            // recvbuf[iResult] = '\0';
            std::string message(recvbuf);

            size_t pos = message.find("\n");
            if (pos != std::string::npos)
            {
                std::string fileName = message.substr(0, pos);
                std::string fileData = message.substr(pos + 1);
                std::ofstream file(fileName);
                if (file.is_open())
                {
                    file << fileData;
                    file.close();
                    std::cout << "File " << fileName << " created" << std::endl;
                    message = "File created";
                }
                else
                {
                    std::cout << "File openning error: " << fileName << std::endl;
                    message = "File openning error";
                }
            }
            else
            {
                std::cout << "Incorrect data format" << std::endl;
                message = "Incorrect data format";
            }
            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, message.c_str(), message.length(), 0);
            if (iSendResult == SOCKET_ERROR) {
                std::cout << "Sending with error:\n" << WSAGetLastError() << std::endl;
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            else {
                std::cout << "Answer sent to the Client" << std::endl;
            }
        }
        else if (iResult == 0)
            std::cout << "Closing connection..." << std::endl;
        else {
            std::cout << "Recieving with error: " << WSAGetLastError() << std::endl;
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        std::cout << "Disconnection error:\n" << WSAGetLastError() << std::endl;
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "Connection closed" << std::endl;

    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}