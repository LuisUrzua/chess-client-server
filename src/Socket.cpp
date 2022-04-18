#include "include/Socket.h"

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <cstring>
#include <errno.h>
#include <stdlib.h>

#define PORT 8080
#define DESKTOP_SERVER_ADDRESS "10.15.2.3"
#define LAPTOP_SERVER_ADDRESS "10.10.10.4"

struct sockaddr_in address;

Socket::Socket(SocketType client_or_server)
{
	socket_type = client_or_server;

    CreateSocket();
    Connect();
}

void Socket::CreateSocket()
{
    int error;
    if (socket_type == SocketType::Client)
    {
        /* AF_INET = IPv4 Internet protocols */
        /* SOCK_STREAM = Full duplex byte stream */
        if ((socket_int = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            error = errno;
            PrintError(error);
            std::cout << "Socket creating error." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else if (socket_type == SocketType::Server)
    {
        /* create an endpoint for communication */
        if ((socket_int = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            error = errno;
            PrintError(error);
            std::cout << "Socket creating error." << std::endl;
            exit(EXIT_FAILURE);
        }

        int opt = 1;

        /* set the socket options */
        if (setsockopt(socket_int, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
            error = errno;
            PrintError(error);
            std::cout << "setsockopt error." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

void Socket::Connect()
{
    int error;

    if (socket_type == SocketType::Client)
    {
        /* IPv4 Internet protocol */
        address.sin_family = AF_INET;
        /* Converts the unsigned short integer hostshort from host byte order to network byte order */
        address.sin_port = htons(PORT);

        std::cout << "Connecting to server..." << std::endl;

        /* Convert IPv4 addresse from text to binary form */
        if ((inet_pton(AF_INET, LAPTOP_SERVER_ADDRESS, &address.sin_addr)) <= 0)
        {
            error = errno;
            PrintError(error);
            std::cout << "Invalid address. Address is not supported." << std::endl;
            exit(EXIT_FAILURE);
        }

        /* Initiate a connection on a socket */
        if ((connect(socket_int, (struct sockaddr*)&address, sizeof(address))) < 0)
        {
            error = errno;
            PrintError(error);
            std::cout << "Connection Failed." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else if (socket_type == SocketType::Server)
    {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);
        int address_length = sizeof(address);
        /* backlog is the maximum number of pending connection requests on socket_int */
        const int backlog = 3;

        std::cout << "Waiting for client to connect..." << std::endl;

        /* bind a name to a socket */
        if (bind(socket_int, (struct sockaddr*)&address, sizeof(address)) < 0)
        {
            error = errno;
            PrintError(error);
            exit(EXIT_FAILURE);
        }
        /* listen for connections on a socket */
        if (listen(socket_int, backlog) < 0)
        {
            error = errno;
            PrintError(error);
            exit(EXIT_FAILURE);
        }
        /* accept a connection on a socket */
        if ((socket_new = accept(socket_int, (struct sockaddr*)&address, (socklen_t*)&address_length)) < 0)
        {
            error = errno;
            PrintError(error);
            exit(EXIT_FAILURE);
        }
    }

}

std::string Socket::Read()
{
    if (socket_type == SocketType::Client)
    {
        read(socket_int, read_buffer, BYTES_PER_MESSAGE);
    }
    else if (socket_type == SocketType::Server)
    {
        read(socket_new, read_buffer, BYTES_PER_MESSAGE);
    }

    return std::string(read_buffer);
}

void Socket::Send(const std::string& string_to_send)
{
    const int flags = 0;

    if (socket_type == SocketType::Client)
    {
        std::strcpy(send_buffer, string_to_send.c_str());
        send(socket_int, send_buffer, strlen(send_buffer), flags);
    }
    else if (socket_type == SocketType::Server)
    {
        std::strcpy(send_buffer, string_to_send.c_str());
        send(socket_new, send_buffer, strlen(send_buffer), flags);
    }
}

void Socket::PrintError(const int& error)
{
    if (error == EISCONN)
    {
        std::cout << "errno: " << error << ", socket is connected." << std::endl;
    }
    else if (error == ENOTCONN)
    {
        std::cout << "errno: " << error << ", socket is not connected." << std::endl;
    }
    else if (error == ENOTSOCK)
    {
        std::cout << "errno: " << error << ", not a socket." << std::endl;
    }
    else
    {
        std::cout << "errno: " << error << ", error undefined." << std::endl;
    }
}
