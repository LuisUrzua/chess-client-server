#include "include/Socket.h"
#include "include/Input.h"
#include "include/Board.h"

#include <iostream>

int main()
{
    std::cout << "Client Chess Program" << std::endl;

    Socket socket(SocketType::Client);
    Input input_client;
    Board chess_board;

    while (true)
    {
        chess_board.PrintBoard();
        socket.Send(input_client.ReadInput());
        std::cout << "Message from server: " << socket.Read() << std::endl;
    }
    
    return 0;
}
