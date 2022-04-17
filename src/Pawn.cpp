#include "include/Pawn.h"
#include "include/Board.h"

#include <iostream>

#define COLUMN_LIMIT_RIGHT 8
#define COLUMN_LIMIT_LEFT 8
#define ROW_LIMIT_UP 8
#define ROW_LIMIT_DOWN 8

const std::string white_pawn_unicode = "\u265F";
const std::string black_pawn_unicode = "\u2659";

Pawn::Pawn(PieceColor color, int c, int r) : Piece(color, PieceType::Pawn, c, r)
{
	
}

Pawn::~Pawn()
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

	if (OneSquareForward(board_current, column_destination, row_destination) ||
		TwoSquaresForward(board_current, column_destination, row_destination) ||
		CaptureLeft(board_current, column_destination, row_destination) ||
		CaptureRight(board_current, column_destination, row_destination))
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
		this->SetMoveType(MoveType::Move);
		std::cout << "SetMoveType(): Move" << std::endl;
	}

	return move_one_square;
}

bool Pawn::TwoSquaresForward(const Board& board_current, const int& column_destination, const int& row_destination)
{
	bool move_two_squares = false;
	const int current_column = GetColumn();
	const int current_row = GetRow();
	const int delta_column = column_destination - current_column;
	const int delta_row = row_destination - current_row;
	const PieceColor color = GetPieceColor();
	const int row_one_square_forward = (color == PieceColor::White) ? 1 : -1;
	const int row_two_squares_forward = (color == PieceColor::White) ? 2 : -2;
	const int column_no_movement = 0;
	const Piece* piece_in_front_square = board_current.GetPieceFromBoard(column_destination, current_row + row_one_square_forward);
	const Piece* piece_on_destination = board_current.GetPieceFromBoard(column_destination, row_destination);
	const int starting_row = (color == PieceColor::White) ? 2 : 7;

	if (piece_in_front_square == nullptr && piece_on_destination == nullptr && delta_column == column_no_movement && delta_row == row_two_squares_forward && current_row == starting_row)
	{
		move_two_squares = true;
		std::cout << "SetMoveType(): Move" << std::endl;
		this->SetMoveType(MoveType::Move);
	}

	return move_two_squares;
}

bool Pawn::CaptureLeft(const Board& board_current, const int& column_destination, const int& row_destination)
{
	bool capture_left = false;
	const int current_column = GetColumn();
	const int current_row = GetRow();
	const int delta_column = column_destination - current_column;
	const int delta_row = row_destination - current_row;
	const PieceColor color = GetPieceColor();
	const int row_forward = (color == PieceColor::White) ? 1 : -1;
	const int column_left = -1;
	const Piece* piece_on_destination = board_current.GetPieceFromBoard(column_destination, row_destination);

	if (piece_on_destination == nullptr)
	{
		return capture_left;
	}
	else if (piece_on_destination->GetPieceColor() == color)
	{
		return capture_left;
	}

	if (delta_column == column_left && delta_row == row_forward)
	{
		capture_left = true;
		this->SetMoveType(MoveType::Capture);
	}

	return capture_left;
}

bool Pawn::CaptureRight(const Board& board_current, const int& column_destination, const int& row_destination)
{
	bool capture_right = false;
	const int current_column = GetColumn();
	const int current_row = GetRow();
	const int delta_column = column_destination - current_column;
	const int delta_row = row_destination - current_row;
	const PieceColor color = GetPieceColor();
	const int row_forward = (color == PieceColor::White) ? 1 : -1;
	const int column_right = 1;
	const Piece* piece_on_destination = board_current.GetPieceFromBoard(column_destination, row_destination);

	if (piece_on_destination == nullptr)
	{
		return capture_right;
	}
	else if (piece_on_destination->GetPieceColor() == color)
	{
		return capture_right;
	}

	if (delta_column == column_right && delta_row == row_forward)
	{
		capture_right = true;
		this->SetMoveType(MoveType::Capture);
	}

	return capture_right;
}
