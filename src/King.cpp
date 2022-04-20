#include "include/King.h"
#include "include/Board.h"

#include <iostream>
#include <algorithm>

#define NUMBER_OF_COLUMNS 8
#define NUMBER_OF_ROWS 8
#define COLUMN_A 1
#define COLUMN_B 2
#define COLUMN_C 3
#define COLUMN_D 4
#define COLUMN_E 5
#define COLUMN_F 6
#define COLUMN_G 7
#define COLUMN_H 8
#define ROW_1 1
#define ROW_8 8

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

	if (MoveOrCapture(chess_board, new_column, new_row) ||
		CastleQueenside(chess_board, new_column, new_row) ||
		CastleKingside(chess_board, new_column, new_row))
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

	for (int c = 1; c <= NUMBER_OF_COLUMNS; c++)
	{
		for (int r = 1; r <= NUMBER_OF_ROWS; r++)
		{
			const Piece* enemy_piece = chess_board.GetPieceFromBoard(c, r);

			if (enemy_piece != nullptr)
			{
				if (enemy_piece->GetPieceColor() != color)
				{
					const VectorOfIntPairs list_of_enemy_attacks = enemy_piece->GetListOfAttacks();

					for (const auto& attack : list_of_enemy_attacks)
					{
						if (attack.first == new_column && attack.second == new_row)
						{
							return move_or_capture;
						}
					}
				}
			}
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

bool King::CastleQueenside(const Board& chess_board, const int& new_column, const int& new_row)
{
	bool castle_queenside = false;
	const int current_column = GetColumn();
	const int current_row = GetRow();
	const PieceColor color = GetPieceColor();
	const int first_row = (color == PieceColor::White) ? ROW_1 : ROW_8;
	const int rook_column = COLUMN_A;
	const int rook_row = first_row;
	const Piece* rook_piece = chess_board.GetPieceFromBoard(rook_column, rook_row);

	if (rook_piece == nullptr)
	{
		return castle_queenside;
	}
	else
	{
		if (rook_piece->GetPieceColor() != color || rook_piece->GetListOfMoves().size() > 0 || rook_piece->GetPieceType() != PieceType::Rook)
		{
			return castle_queenside;
		}
	}

	if (chess_board.GetPieceFromBoard(COLUMN_B, first_row) != nullptr || chess_board.GetPieceFromBoard(COLUMN_C, first_row) != nullptr ||
		chess_board.GetPieceFromBoard(COLUMN_D, first_row) != nullptr)
	{
		return castle_queenside;
	}

	for (int c = COLUMN_A; c <= COLUMN_H; c++)
	{
		for (int r = ROW_1; r <= ROW_8; r++)
		{
			const Piece* enemy_piece = chess_board.GetPieceFromBoard(c, r);

			if (enemy_piece != nullptr)
			{
				if (enemy_piece->GetPieceColor() != color)
				{
					const VectorOfIntPairs list_of_enemy_attacks = enemy_piece->GetListOfAttacks();
					for (const auto& attack : list_of_enemy_attacks)
					{
						if (attack.first == COLUMN_E && attack.second == first_row)
						{
							return castle_queenside;
						}

						if (attack.first == COLUMN_D && attack.second == first_row)
						{
							return castle_queenside;
						}

						if (attack.first == COLUMN_C && attack.second == first_row)
						{
							return castle_queenside;
						}
					}
				}
			}
		}
	}

	if (current_column == COLUMN_E && current_row == first_row && GetListOfMoves().size() == 0 && new_column == COLUMN_C && new_row == first_row)
	{
		castle_queenside = true;
		SetMoveType(MoveType::CastleQueenside);
	}

	return castle_queenside;
}

bool King::CastleKingside(const Board& chess_board, const int& new_column, const int& new_row)
{
	bool castle_kingside = false;
	const int current_column = GetColumn();
	const int current_row = GetRow();
	const PieceColor color = GetPieceColor();
	const int first_row = (color == PieceColor::White) ? ROW_1 : ROW_8;
	const int rook_column = COLUMN_H;
	const int rook_row = first_row;
	const Piece* rook_piece = chess_board.GetPieceFromBoard(rook_column, rook_row);

	if (rook_piece == nullptr)
	{
		return castle_kingside;
	}
	else
	{
		if (rook_piece->GetPieceColor() != color || rook_piece->GetListOfMoves().size() > 0 || rook_piece->GetPieceType() != PieceType::Rook)
		{
			return castle_kingside;
		}
	}

	if (chess_board.GetPieceFromBoard(COLUMN_F, first_row) != nullptr || chess_board.GetPieceFromBoard(COLUMN_G, first_row) != nullptr)
	{
		return castle_kingside;
	}

	for (int c = COLUMN_A; c <= COLUMN_H; c++)
	{
		for (int r = ROW_1; r <= ROW_8; r++)
		{
			const Piece* enemy_piece = chess_board.GetPieceFromBoard(c, r);

			if (enemy_piece != nullptr)
			{
				if (enemy_piece->GetPieceColor() != color)
				{
					const VectorOfIntPairs list_of_enemy_attacks = enemy_piece->GetListOfAttacks();
					for (const auto& attack : list_of_enemy_attacks)
					{
						if (attack.first == COLUMN_E && attack.second == first_row)
						{
							return castle_kingside;
						}

						if (attack.first == COLUMN_F && attack.second == first_row)
						{
							return castle_kingside;
						}

						if (attack.first == COLUMN_G && attack.second == first_row)
						{
							return castle_kingside;
						}
					}
				}
			}
		}
	}

	if (current_column == COLUMN_E && current_row == first_row && GetListOfMoves().size() == 0 && new_column == COLUMN_G && new_row == first_row)
	{
		castle_kingside = true;
		SetMoveType(MoveType::CastleKingside);
	}

	return castle_kingside;
}

void King::UpdateListOfAttacks(const Board& chess_board)
{
	list_of_attacks.clear();
	const int current_column = GetColumn();
	const int current_row = GetRow();
	const int left_column = current_column - 1;
	const int middle_column = current_column;
	const int right_column = current_column + 1;
	const int top_row = current_row + 1;
	const int center_row = current_row;
	const int bottom_row = current_row - 1;

	if (ColumnRowWithinBounds(middle_column, top_row))
	{
		list_of_attacks.push_back({ middle_column, top_row });
	}
	
	if (ColumnRowWithinBounds(right_column, top_row))
	{
		list_of_attacks.push_back({ right_column, top_row });
	}
	
	if (ColumnRowWithinBounds(right_column, center_row))
	{
		list_of_attacks.push_back({ right_column, center_row });
	}
	
	if (ColumnRowWithinBounds(right_column, bottom_row))
	{
		list_of_attacks.push_back({ right_column, bottom_row });
	}
	
	if (ColumnRowWithinBounds(middle_column, bottom_row))
	{
		list_of_attacks.push_back({ middle_column, bottom_row });
	}
	
	if (ColumnRowWithinBounds(left_column, bottom_row))
	{
		list_of_attacks.push_back({ left_column, bottom_row });
	}
	
	if (ColumnRowWithinBounds(left_column, center_row))
	{
		list_of_attacks.push_back({ left_column, center_row });
	}
	
	if (ColumnRowWithinBounds(left_column, top_row))
	{
		list_of_attacks.push_back({ left_column, top_row });
	}
}

bool King::Checkmate(const Board& chess_board)
{
	bool king_in_check = false;
	bool king_checkmate = false;
	int number_of_checks = 0;

	for (int c = COLUMN_A; c <= COLUMN_H; c++)
	{
		for (int r = ROW_1; r <= ROW_8; r++)
		{
			const Piece* piece_on_square = chess_board.GetPieceFromBoard(c, r);

			if (piece_on_square != nullptr)
			{
				if (piece_on_square->GetPieceColor() != GetPieceColor())
				{
					const VectorOfIntPairs attack_squares = piece_on_square->GetListOfAttacks();

					for (const auto& attack : attack_squares)
					{
						if (attack.first == GetColumn() && attack.second == GetRow())
						{
							king_in_check = true;
							number_of_checks++;
						}
					}
				}
			}
		}
	}

	if (!king_in_check)
	{
		return king_checkmate;
	}

	if (number_of_checks == 1)
	{
		if (!MoveKingOutOfCheck(chess_board))
		{
			king_checkmate = true;
		}
	}
	else if (number_of_checks == 2)
	{
		if (!MoveKingOutOfCheck(chess_board))
		{
			king_checkmate = true;
		}
	}

	return king_checkmate;
}

bool King::MoveKingOutOfCheck(const Board& chess_board)
{
	bool king_out_of_check = false;
	const int c = GetColumn();
	const int r = GetRow();
	const PieceColor color = GetPieceColor();
	VectorOfIntPairs enemy_attacks;
	VectorOfIntPairs squares_around_king;
	squares_around_king.push_back({ c, r + 1 });
	squares_around_king.push_back({ c + 1, r + 1 });
	squares_around_king.push_back({ c + 1, r });
	squares_around_king.push_back({ c + 1, r - 1 });
	squares_around_king.push_back({ c, r - 1 });
	squares_around_king.push_back({ c - 1, r - 1 });
	squares_around_king.push_back({ c - 1, r });
	squares_around_king.push_back({ c - 1, r + 1 });

	/* erase invalid squares */
	for (VectorOfIntPairs::iterator it = squares_around_king.begin(); it != squares_around_king.end();)
	{
		if (!ColumnRowWithinBounds(it->first, it->second))
		{
			it = squares_around_king.erase(it);
		}
		else if (ColumnRowWithinBounds(it->first, it->second) && chess_board.GetPieceFromBoard(it->first, it->second) != nullptr)
		{
			/* erase squares that contain friendly pieces */
			if (chess_board.GetPieceFromBoard(it->first, it->second)->GetPieceColor() == color)
			{
				it = squares_around_king.erase(it);
			}
			else
			{
				++it;
			}
		}
		else
		{
			++it;
		}
	}

	/* gather all enemy attacks */
	for (int col = COLUMN_A; col <= COLUMN_H; col++)
	{
		for (int row = ROW_1; row <= ROW_8; row++)
		{
			const Piece* enemy_piece = chess_board.GetPieceFromBoard(col, row);

			if (enemy_piece != nullptr)
			{
				if (enemy_piece->GetPieceColor() != color)
				{
					const VectorOfIntPairs enemy_piece_attacks = enemy_piece->GetListOfAttacks();

					for (const auto& attack : enemy_piece_attacks)
					{
						enemy_attacks.push_back(attack);
					}
				}
			}
		}
	}

	/* remove valid squares which are being attacked by enemy pieces */
	for (const auto& attack : enemy_attacks)
	{
		VectorOfIntPairs::iterator square_next_to_king = std::find(std::begin(squares_around_king), std::end(squares_around_king), attack);

		if (square_next_to_king != std::end(squares_around_king))
		{
			squares_around_king.erase(square_next_to_king);
		}
	}

	if (squares_around_king.size() > 0)
	{
		king_out_of_check = true;
	}

	return king_out_of_check;
}
