#include "include/Socket.h"
#include "include/Input.h"

#include <iostream>

int main()
{
    std::cout << "Server" << std::endl;
    std::cout << "severus" << std::endl;

    Socket socket(SocketType::Server);
    Input input_server;

    while (true)
    {
        std::cout << "Message from client: " << socket.Read() << std::endl;
        socket.Send(input_server.ReadInput());
    }

    return 0;
}
