#include "include/Queen.h"
#include "include/Board.h"

#include <iostream>

const std::string white_queen_unicode = "\u265B";
const std::string black_queen_unicode = "\u2655";

Queen::Queen(PieceColor color, int c, int r) : Piece(color, PieceType::Queen, c, r)
{

}

Queen::~Queen()
{

}

void Queen::PrintPiece() const
{
	const std::string whitespace = " ";

	if (GetPieceColor() == PieceColor::White)
	{
		std::cout << white_queen_unicode << whitespace;
	}
	else if (GetPieceColor() == PieceColor::Black)
	{
		std::cout << black_queen_unicode << whitespace;
	}
}

bool Queen::IsMoveValid(const Board& chess_board, const int& new_column, const int& new_row)
{
	bool queen_move = false;

	if (MoveLikeBishop(chess_board, new_column, new_row) || MoveLikeRook(chess_board, new_column, new_row))
	{
		queen_move = true;
	}

	return queen_move;
}

void Queen::UpdateListOfAttacks(const Board& chess_board)
{
	list_of_attacks.clear();
	const int current_column = GetColumn();
	const int current_row = GetRow();

	/* rook attacks begin */
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
	/* rook attacks end */

	/* bishop attacks begin */
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

	for (int west = current_column - 1, north = current_row + 1; ColumnRowWithinBounds(west, north); west--, north++)
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
	/* bishop attacks end */
}

bool Queen::MoveLikeRook(const Board& chess_board, const int& new_column, const int& new_row)
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

bool Queen::MoveLikeBishop(const Board& chess_board, const int& new_column, const int& new_row)
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
