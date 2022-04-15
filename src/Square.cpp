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

/* columns and rows start at index 1, offset by 1*/
const char column_chars[] =
{
	'@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
};
const char row_chars[] =
{
	'@', '1', '2', '3', '4', '5', '6', '7', '8',
};

void Square::PrintSquare() const
{
	if (piece_on_square == nullptr)
	{
		/* square is empty */
		
		if (column == LAST_COLUMN)
		{
			/* column H */
			//std::cout << column_chars[column] << row_chars[row] << "| ";
			std::cout << "  | ";
		}
		else
		{
			/* columns A through G */
			//std::cout << column_chars[column] << row_chars[row] << whitespace;
			std::cout << "  |";
		}
	}
	else
	{
		/* square has a piece */
		
		if (column == LAST_COLUMN)
		{
			/* column H */
			piece_on_square->PrintPiece();
			std::cout << "| ";
		}
		else
		{
			/* columns A through G */
			piece_on_square->PrintPiece();
			std::cout << "|";
		}
	}
}

Piece* Square::GetPieceOnSquare() const
{
	return piece_on_square;
}
