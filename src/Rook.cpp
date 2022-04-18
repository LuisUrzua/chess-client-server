#include "include/Rook.h"

#include <iostream>

const std::string white_rook_unicode = "\u265C";
const std::string black_rook_unicode = "\u2656";

Rook::Rook(PieceColor color, int c, int r) : Piece(color, PieceType::Rook, c, r)
{

}

Rook::~Rook()
{

}

void Rook::PrintPiece() const
{
	const std::string whitespace = " ";

	if (GetPieceColor() == PieceColor::White)
	{
		std::cout << white_rook_unicode << whitespace;
	}
	else if (GetPieceColor() == PieceColor::Black)
	{
		std::cout << black_rook_unicode << whitespace;
	}
}

bool Rook::IsMoveValid(const Board& chess_board, const int& new_column, const int& new_row)
{
	return false;
}

void Rook::UpdateListOfAttacks(const Board& chess_board)
{

}
