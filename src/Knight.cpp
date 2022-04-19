#include "include/Knight.h"
#include "include/Board.h"

#include <iostream>

const std::string white_knight_unicode = "\u265E";
const std::string black_knight_unicode = "\u2658";

Knight::Knight(PieceColor color, int c, int r) : Piece(color, PieceType::Knight, c, r)
{

}

Knight::~Knight()
{

}

void Knight::PrintPiece() const
{
	const std::string whitespace = " ";

	if (GetPieceColor() == PieceColor::White)
	{
		std::cout << white_knight_unicode << whitespace;
	}
	else if (GetPieceColor() == PieceColor::Black)
	{
		std::cout << black_knight_unicode << whitespace;
	}
}

bool Knight::IsMoveValid(const Board& chess_board, const int& new_column, const int& new_row)
{
	bool knight_move = false;
	bool knight_capture = false;
	const int delta_column = new_column - GetColumn();
	const int delta_row = new_row - GetRow();
	
	if (chess_board.GetPieceFromBoard(new_column, new_row) != nullptr)
	{
		if (chess_board.GetPieceFromBoard(new_column, new_row)->GetPieceColor() == GetPieceColor())
		{
			return knight_move;
		}
		else
		{
			knight_capture = true;
		}
	}

	if (ColumnRowWithinBounds(new_column, new_row) &&
		((AbsoluteValue(delta_column) == 1 && AbsoluteValue(delta_row) == 2) ||
			(AbsoluteValue(delta_column) == 2 && AbsoluteValue(delta_row) == 1)))
	{
		knight_move = true;
	}

	if (knight_move && knight_capture)
	{
		SetMoveType(MoveType::Capture);
	}
	else if (knight_move && !knight_capture)
	{
		SetMoveType(MoveType::Move);
	}

	return knight_move;
}

void Knight::UpdateListOfAttacks(const Board& chess_board)
{
	list_of_attacks.clear();
	const int current_column = GetColumn();
	const int current_row = GetRow();
	const int left_1 = current_column - 1;
	const int left_2 = current_column - 2;
	const int right_1 = current_column + 1;
	const int right_2 = current_column + 2;
	const int down_1 = current_row - 1;
	const int down_2 = current_row - 2;
	const int up_1 = current_row + 1;
	const int up_2 = current_row + 2;

	if (ColumnRowWithinBounds(left_1, up_2))
	{
		list_of_attacks.push_back({ left_1, up_2 });
	}
	
	if (ColumnRowWithinBounds(right_1, up_2))
	{
		list_of_attacks.push_back({ right_1, up_2 });
	}

	if (ColumnRowWithinBounds(right_2, up_1))
	{
		list_of_attacks.push_back({ right_2, up_1 });
	}

	if (ColumnRowWithinBounds(right_2, down_1))
	{
		list_of_attacks.push_back({ right_2, down_1 });
	}

	if (ColumnRowWithinBounds(right_1, down_2))
	{
		list_of_attacks.push_back({ right_1, down_2 });
	}

	if (ColumnRowWithinBounds(left_1, down_2))
	{
		list_of_attacks.push_back({ left_1, down_2 });
	}

	if (ColumnRowWithinBounds(left_2, down_1))
	{
		list_of_attacks.push_back({ left_2, down_1 });
	}

	if (ColumnRowWithinBounds(left_2, up_1))
	{
		list_of_attacks.push_back({ left_2, up_1 });
	}
}
