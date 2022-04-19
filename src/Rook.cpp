#include "include/Rook.h"
#include "include/Board.h"

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
	bool rook_move = false;
	bool rook_capture = false;
	const int current_column = GetColumn();
	const int current_row = GetRow();
	const int delta_column = current_column - new_column;
	const int delta_row = current_row - new_row;
	const Piece* enemy_piece = chess_board.GetPieceFromBoard(new_column, new_row);

	if ((delta_column == 0 && delta_row == 0) || (delta_column != 0 && delta_row != 0))
	{
		return rook_move;
	}

	if (enemy_piece != nullptr)
	{
		if (enemy_piece->GetPieceColor() == GetPieceColor())
		{
			return rook_move;
		}
		else
		{
			rook_capture = true;
		}
	}

	if (delta_column == 0)
	{
		const int up_or_down = (current_row < new_row) ? 1 : -1;

		for (int r = current_row + up_or_down; r != new_row; r = r + up_or_down)
		{
			const Piece* empty_square = chess_board.GetPieceFromBoard(current_column, r);

			if (empty_square != nullptr)
			{
				return rook_move;
			}
		}

		rook_move = true;
	}
	else if (delta_row == 0)
	{
		const int left_or_right = (current_column < new_column) ? 1 : -1;

		for (int c = current_column + left_or_right; c != new_column; c = c + left_or_right)
		{
			const Piece* empty_square = chess_board.GetPieceFromBoard(c, current_row);

			if (empty_square != nullptr)
			{
				return rook_move;
			}
		}

		rook_move = true;
	}

	if (rook_move && rook_capture)
	{
		SetMoveType(MoveType::Capture);
	}
	else if (rook_move && !rook_capture)
	{
		SetMoveType(MoveType::Move);
	}

	return rook_move;
}

void Rook::UpdateListOfAttacks(const Board& chess_board)
{
	list_of_attacks.clear();
	const int current_column = GetColumn();
	const int current_row = GetRow();

	for (int north_path = current_row + 1; ColumnRowWithinBounds(current_column, north_path); north_path++)
	{
		list_of_attacks.push_back({ current_column, north_path });

		if (chess_board.GetPieceFromBoard(current_column, north_path) != nullptr)
		{
			if (chess_board.GetPieceFromBoard(current_column, north_path)->GetPieceType() != PieceType::King ||
				chess_board.GetPieceFromBoard(current_column, north_path)->GetPieceColor() == GetPieceColor())
			{
				break;
			}
		}
	}

	for (int south_path = current_row - 1; ColumnRowWithinBounds(current_column, south_path); south_path--)
	{
		list_of_attacks.push_back({ current_column, south_path });

		if (chess_board.GetPieceFromBoard(current_column, south_path) != nullptr)
		{
			if (chess_board.GetPieceFromBoard(current_column, south_path)->GetPieceType() != PieceType::King ||
				chess_board.GetPieceFromBoard(current_column, south_path)->GetPieceColor() == GetPieceColor())
			{
				break;
			}
		}
	}

	for (int east_path = current_column + 1; ColumnRowWithinBounds(east_path, current_row); east_path++)
	{
		list_of_attacks.push_back({ east_path, current_row });

		if (chess_board.GetPieceFromBoard(east_path, current_row) != nullptr)
		{
			if (chess_board.GetPieceFromBoard(east_path, current_row)->GetPieceType() != PieceType::King ||
				chess_board.GetPieceFromBoard(east_path, current_row)->GetPieceColor() == GetPieceColor())
			{
				break;
			}
		}
	}

	for (int west_path = current_column - 1; ColumnRowWithinBounds(west_path, current_row); west_path--)
	{
		list_of_attacks.push_back({ west_path, current_row });

		if (chess_board.GetPieceFromBoard(west_path, current_row) != nullptr)
		{
			if (chess_board.GetPieceFromBoard(west_path, current_row)->GetPieceType() != PieceType::King ||
				chess_board.GetPieceFromBoard(west_path, current_row)->GetPieceColor() == GetPieceColor())
			{
				break;
			}
		}
	}
}
