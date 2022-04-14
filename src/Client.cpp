#include "include/Socket.h"
#include "include/Input.h"

#include <iostream>

int main()
{
    std::cout << "Client" << std::endl;

    Socket socket(SocketType::Client);
    Input input_client;

    while (true)
    {
        socket.Send(input_client.ReadInput());
        std::cout << "Message from server: " << socket.Read() << std::endl;
    }
    
    return 0;
}
