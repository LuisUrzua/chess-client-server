#include "include/Socket.h"
#include "include/Input.h"
#include "include/Board.h"

#include <iostream>

int main()
{
    std::cout << "Client Chess Program" << std::endl;

    Socket socket(SocketType::Client);
    Input input_client("White");
    Board chess_board;

    while (true)
    {
        std::string client_move;
        std::string server_move;

        chess_board.PrintBoard();
        
        client_move = input_client.ReadInput(chess_board);
        socket.Send(client_move);
        chess_board.MovePiece(client_move);
        chess_board.PrintBoard();
        
        server_move = socket.Read();
        std::cout << "Message from server: " << server_move << std::endl;
        chess_board.MovePiece(server_move);
    }
    
    return 0;
}
