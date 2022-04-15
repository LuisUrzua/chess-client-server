#include "include/Socket.h"
#include "include/Input.h"
#include "include/Board.h"

#include <iostream>

int main()
{
    std::cout << "Server Chess Program" << std::endl;

    Socket socket(SocketType::Server);
    Input input_server("Black");
    Board chess_board;

    while (true)
    {
        std::string server_move;
        std::string client_move;

        chess_board.PrintBoard();
        
        client_move = socket.Read();
        std::cout << "Message from client: " << client_move << std::endl;
        chess_board.MovePiece(client_move);
        chess_board.PrintBoard();
        
        server_move = input_server.ReadInput(chess_board);
        socket.Send(server_move);
        chess_board.MovePiece(server_move);
    }

    return 0;
}
