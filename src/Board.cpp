#include "include/Board.h"
#include "include/Pawn.h"

#include <iostream>

#define COLUMN_A 1
#define COLUMN_B 2
#define COLUMN_C 3
#define COLUMN_D 4
#define COLUMN_E 5
#define COLUMN_F 6
#define COLUMN_G 7
#define COLUMN_H 8
#define ROW_1 1
#define ROW_2 2
#define ROW_3 3
#define ROW_4 4
#define ROW_5 5
#define ROW_6 6
#define ROW_7 7
#define ROW_8 8

Board::Board()
{
	for (int column = COLUMN_A; column <= COLUMN_H; column += COLUMN_A)
	{
		for (int row = ROW_1; row <= ROW_8; row += ROW_1)
		{
			squares_on_board.insert({ { column, row }, Square(column, row) });
		}
	}

	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_A, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_B, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_D, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::Black, COLUMN_A, ROW_7));
	pieces_on_board.push_back(new Pawn(PieceColor::Black, COLUMN_H, ROW_7));

	for (const auto& piece : pieces_on_board)
	{
		squares_on_board.at({ piece->GetColumn(), piece->GetRow() }).InsertPiece(piece);
	}
}

void Board::PrintBoard() const
{
	std::cout << "   ";
	std::cout << " A ";
	std::cout << " B ";
	std::cout << " C ";
	std::cout << " D ";
	std::cout << " E ";
	std::cout << " F ";
	std::cout << " G ";
	std::cout << " H " << std::endl;
	std::cout << "   ";
	std::cout << std::string(8*3, '-') << std::endl;

	for (int row = ROW_8; row >= ROW_1; row -= ROW_1)
	{
		std::cout << row << " |";

		for (int column = COLUMN_A; column <= COLUMN_H; column += COLUMN_A)
		{
			squares_on_board.at({ column, row }).PrintSquare();
		}

		std::cout << row << std::endl;
		std::cout << "   ";
		std::cout << std::string(8 * 3, '-') << std::endl;
	}

	std::cout << "   ";
	std::cout << " A ";
	std::cout << " B ";
	std::cout << " C ";
	std::cout << " D ";
	std::cout << " E ";
	std::cout << " F ";
	std::cout << " G ";
	std::cout << " H " << std::endl;
}
