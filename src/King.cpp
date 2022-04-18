#include "include/King.h"
#include "include/Board.h"

#include <iostream>

const std::string white_king_unicode = "\u265A";
const std::string black_king_unicode = "\u2654";

King::King(PieceColor color, int c, int r) : Piece(color, PieceType::King, c, r)
{

}

King::~King()
{

}

void King::PrintPiece() const
{
	const std::string whitespace = " ";

	if (GetPieceColor() == PieceColor::White)
	{
		std::cout << white_king_unicode << whitespace;
	}
	else if (GetPieceColor() == PieceColor::Black)
	{
		std::cout << black_king_unicode << whitespace;
	}
}

bool King::IsMoveValid(const Board& chess_board, const int& new_column, const int& new_row)
{
	bool king_move = false;

	if (MoveOrCapture(chess_board, new_column, new_row))
	{
		king_move = true;
	}

	return king_move;
}

bool King::MoveOrCapture(const Board& chess_board, const int& new_column, const int& new_row)
{
	bool move_or_capture = false;
	bool capture_enemy_piece = false;
	const int current_column = GetColumn();
	const int current_row = GetRow();
	const int delta_column = new_column - current_column;
	const int delta_row = new_row - current_row;
	const PieceColor color = GetPieceColor();
	const Piece* piece_on_destination = chess_board.GetPieceFromBoard(new_column, new_row);

	if (piece_on_destination != nullptr)
	{
		if (piece_on_destination->GetPieceColor() == color)
		{
			return move_or_capture;
		}
		else
		{
			capture_enemy_piece = true;
		}
	}

	/* TODO: check that the new_square is not attacked by an enemy piece */
	if (AbsoluteValue(delta_column) == 1 && AbsoluteValue(delta_row) == 1)
	{
		/* north-east, south-east, south-west, north-west */
		move_or_capture = true;
		SetMoveType((capture_enemy_piece) ? MoveType::Capture : MoveType::Move);
	}
	else if (AbsoluteValue(delta_column) == 1 && AbsoluteValue(delta_row) == 0)
	{
		/* east, west */
		move_or_capture = true;
		SetMoveType((capture_enemy_piece) ? MoveType::Capture : MoveType::Move);
	}
	else if (AbsoluteValue(delta_column) == 0 && AbsoluteValue(delta_row) == 1)
	{
		/* north, south */
		move_or_capture = true;
		SetMoveType((capture_enemy_piece) ? MoveType::Capture : MoveType::Move);
	}

	return move_or_capture;
}

bool CastleQueenside(const Board&, const int&, const int&)
{
	return false;
}

bool CastleKingside(const Board&, const int&, const int&)
{
	return false;
}

int King::AbsoluteValue(const int& delta_column_or_row) const
{
	if (delta_column_or_row < 0)
	{
		return delta_column_or_row * -1;
	}
	else
	{
		return delta_column_or_row;
	}
}
