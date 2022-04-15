#include "include/Pawn.h"

#include <iostream>

const std::string white_pawn_unicode = "\u265F";
const std::string black_pawn_unicode = "\u2659";

Pawn::Pawn(PieceColor color, int c, int r) : Piece(color, PieceType::Pawn, c, r)
{
	
}

void Pawn::PrintPiece() const
{
	const std::string whitespace = " ";

	if (GetPieceColor() == PieceColor::White)
	{
		std::cout << white_pawn_unicode << whitespace;
	}
	else if (GetPieceColor() == PieceColor::Black)
	{
		std::cout << black_pawn_unicode << whitespace;
	}
}
