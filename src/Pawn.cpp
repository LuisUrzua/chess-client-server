#include "include/Pawn.h"
#include "include/Board.h"

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

bool Pawn::IsMoveValid(const Board& board_current, const int& column_destination, const int& row_destination)
{
	bool pawn_move = false;

	if (OneSquareForward(board_current, column_destination, row_destination))
	{
		pawn_move = true;
	}

	return pawn_move;
}

bool Pawn::OneSquareForward(const Board& board_current, const int& column_destination, const int& row_destination)
{
	bool move_one_square = false;
	const int current_column = GetColumn();
	const int current_row = GetRow();
	const int delta_column = column_destination - current_column;
	const int delta_row = row_destination - current_row;
	const PieceColor color = GetPieceColor();
	const int row_forward = (color == PieceColor::White) ? 1 : -1;
	const int column_no_movement = 0;

	const Piece* piece_on_destination = board_current.GetPieceFromBoard(column_destination, row_destination);

	if (piece_on_destination == nullptr && delta_column == column_no_movement && delta_row == row_forward)
	{
		move_one_square = true;
	}

	return move_one_square;
}
