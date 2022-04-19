#include "include/Queen.h"
#include "include/Board.h"

#include <iostream>

const std::string white_queen_unicode = "\u265B";
const std::string black_queen_unicode = "\u2655";

Queen::Queen(PieceColor color, int c, int r) : Piece(color, PieceType::Queen, c, r)
{

}

Queen::~Queen()
{

}

void Queen::PrintPiece() const
{
	const std::string whitespace = " ";

	if (GetPieceColor() == PieceColor::White)
	{
		std::cout << white_queen_unicode << whitespace;
	}
	else if (GetPieceColor() == PieceColor::Black)
	{
		std::cout << black_queen_unicode << whitespace;
	}
}

bool Queen::IsMoveValid(const Board& chess_board, const int& new_column, const int& new_row)
{
	return false;
}

void Queen::UpdateListOfAttacks(const Board& chess_board)
{

}
