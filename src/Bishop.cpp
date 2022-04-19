#include "include/Bishop.h"
#include "include/Board.h"

#include <iostream>

const std::string white_bishop_unicode = "\u265D";
const std::string black_bishop_unicode = "\u2657";

Bishop::Bishop(PieceColor color, int c, int r) : Piece(color, PieceType::Bishop, c, r)
{

}

Bishop::~Bishop()
{

}

void Bishop::PrintPiece() const
{
	const std::string whitespace = " ";

	if (GetPieceColor() == PieceColor::White)
	{
		std::cout << white_bishop_unicode << whitespace;
	}
	else if (GetPieceColor() == PieceColor::Black)
	{
		std::cout << black_bishop_unicode << whitespace;
	}
}

bool Bishop::IsMoveValid(const Board& chess_board, const int& new_column, const int& new_row)
{
	bool bishop_move = false;
	bool bishop_capture = false;
	const int current_column = GetColumn();
	const int current_row = GetRow();
	const int delta_column = new_column - current_column;
	const int delta_row = new_row - current_row;
	const Piece* enemy_piece = chess_board.GetPieceFromBoard(new_column, new_row);

	if (AbsoluteValue(delta_column) != AbsoluteValue(delta_row))
	{
		return bishop_move;
	}

	if (enemy_piece != nullptr)
	{
		if (enemy_piece->GetPieceColor() == GetPieceColor())
		{
			return bishop_move;
		}
		else
		{
			bishop_capture = true;
		}
	}

	if (delta_column > 0 && delta_row > 0)
	{
		for (int c = current_column + 1, r = current_row + 1; c != new_column && r != new_row; c++, r++)
		{
			const Piece* empty_square = chess_board.GetPieceFromBoard(c, r);

			if (empty_square != nullptr)
			{
				return bishop_move;
			}
		}

		bishop_move = true;
	}
	else if (delta_column > 0 && delta_row < 0)
	{
		for (int c = current_column + 1, r = current_row - 1; c != new_column && r != new_row; c++, r--)
		{
			const Piece* empty_square = chess_board.GetPieceFromBoard(c, r);

			if (empty_square != nullptr)
			{
				return bishop_move;
			}
		}

		bishop_move = true;
	}
	else if (delta_column < 0 && delta_row < 0)
	{
		for (int c = current_column - 1, r = current_row - 1; c != new_column && r != new_row; c--, r--)
		{
			const Piece* empty_square = chess_board.GetPieceFromBoard(c, r);

			if (empty_square != nullptr)
			{
				return bishop_move;
			}
		}

		bishop_move = true;
	}
	else if (delta_column < 0 && delta_row > 0)
	{
		for (int c = current_column - 1, r = current_row + 1; c != new_column && r != new_row; c--, r++)
		{
			const Piece* empty_square = chess_board.GetPieceFromBoard(c, r);

			if (empty_square != nullptr)
			{
				return bishop_move;
			}
		}

		bishop_move = true;
	}

	if (bishop_move && bishop_capture)
	{
		SetMoveType(MoveType::Capture);
	}
	else if (bishop_move && !bishop_capture)
	{
		SetMoveType(MoveType::Move);
	}

	return bishop_move;
}

void Bishop::UpdateListOfAttacks(const Board& chess_board)
{
	list_of_attacks.clear();

	const int current_column = GetColumn();
	const int current_row = GetRow();

	for (int east = current_column + 1, north = current_row + 1; ColumnRowWithinBounds(east, north); east++, north++)
	{
		list_of_attacks.push_back({ east, north });

		if (chess_board.GetPieceFromBoard(east, north) != nullptr)
		{
			if (chess_board.GetPieceFromBoard(east, north)->GetPieceType() != PieceType::King ||
				chess_board.GetPieceFromBoard(east, north)->GetPieceColor() == GetPieceColor())
			{
				break;
			}
		}
	}

	for (int east = current_column + 1, south = current_row - 1; ColumnRowWithinBounds(east, south); east++, south--)
	{
		list_of_attacks.push_back({ east, south });

		if (chess_board.GetPieceFromBoard(east, south) != nullptr)
		{
			if (chess_board.GetPieceFromBoard(east, south)->GetPieceType() != PieceType::King ||
				chess_board.GetPieceFromBoard(east, south)->GetPieceColor() == GetPieceColor())
			{
				break;
			}
		}
	}

	for (int west = current_column - 1, south = current_row - 1; ColumnRowWithinBounds(west, south); west--, south--)
	{
		list_of_attacks.push_back({ west, south });

		if (chess_board.GetPieceFromBoard(west, south) != nullptr)
		{
			if (chess_board.GetPieceFromBoard(west, south)->GetPieceType() != PieceType::King ||
				chess_board.GetPieceFromBoard(west, south)->GetPieceColor() == GetPieceColor())
			{
				break;
			}
		}
	}

	for (int west = current_column - 1, north = current_row + 1; ColumnRowWithinBounds(west, north); west--, north--)
	{
		list_of_attacks.push_back({ west, north });

		if (chess_board.GetPieceFromBoard(west, north) != nullptr)
		{
			if (chess_board.GetPieceFromBoard(west, north)->GetPieceType() != PieceType::King ||
				chess_board.GetPieceFromBoard(west, north)->GetPieceColor() == GetPieceColor())
			{
				break;
			}
		}
	}
}
