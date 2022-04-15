#include "include/Socket.h"
#include "include/Input.h"
#include "include/Board.h"

#include <iostream>

int main()
{
    std::cout << "Server Chess Program" << std::endl;

    Socket socket(SocketType::Server);
    Input input_server;
    Board chess_board;

    while (true)
    {
        chess_board.PrintBoard();
        std::cout << "Message from client: " << socket.Read() << std::endl;
        socket.Send(input_server.ReadInput());
    }

    return 0;
}
