#include "include/Square.h"
#include "include/Piece.h"

#include <iostream>

#define LAST_COLUMN 8

Square::Square(int c, int r)
{
	column = c;
	row = r;
	piece_on_square = nullptr;
}

void Square::InsertPiece(Piece* piece)
{
	piece_on_square = piece;
}

void Square::PrintSquare() const
{
	const std::string whitespace = " ";
	const std::string border = "|";

	if (piece_on_square == nullptr)
	{
		/* square is empty */
		
		if (column == LAST_COLUMN)
		{
			/* column H */
			std::cout << whitespace << whitespace << border << whitespace;
		}
		else
		{
			/* columns A through G */
			std::cout << whitespace << whitespace << border;
		}
	}
	else
	{
		/* square has a piece */
		
		if (column == LAST_COLUMN)
		{
			/* column H */
			piece_on_square->PrintPiece();
			std::cout << border << whitespace;
		}
		else
		{
			/* columns A through G */
			piece_on_square->PrintPiece();
			std::cout << border;
		}
	}
}

Piece* Square::GetPieceOnSquare() const
{
	return piece_on_square;
}

void Square::RemovePieceOnSquare()
{
	piece_on_square = nullptr;
}
