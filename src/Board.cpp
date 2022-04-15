#include "include/Board.h"
#include "include/Pawn.h"

#include <iostream>

#define COLUMN_A 1
#define COLUMN_B 2
#define COLUMN_C 3
#define COLUMN_D 4
#define COLUMN_E 5
#define COLUMN_F 6
#define COLUMN_G 7
#define COLUMN_H 8
#define ROW_1 1
#define ROW_2 2
#define ROW_3 3
#define ROW_4 4
#define ROW_5 5
#define ROW_6 6
#define ROW_7 7
#define ROW_8 8

#define ASCII_COLUMN_OFFSET 0x40
#define ASCII_ROW_OFFSET 0x30

Board::Board()
{
	for (int column = COLUMN_A; column <= COLUMN_H; column += COLUMN_A)
	{
		for (int row = ROW_1; row <= ROW_8; row += ROW_1)
		{
			squares_on_board.insert({ { column, row }, Square(column, row) });
		}
	}

	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_A, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_B, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_D, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::Black, COLUMN_A, ROW_7));
	pieces_on_board.push_back(new Pawn(PieceColor::Black, COLUMN_H, ROW_7));

	for (const auto& piece : pieces_on_board)
	{
		squares_on_board.at({ piece->GetColumn(), piece->GetRow() }).InsertPiece(piece);
	}
}

void Board::PrintBoard() const
{
	const char border = '-';
	const int chars_per_column = 8 * 3;
	std::cout << std::endl;
	std::cout << "   " << " A " << " B " << " C " << " D " << " E " << " F " << " G " << " H " << std::endl;
	std::cout << "   " << std::string(chars_per_column, border) << std::endl;

	for (int row = ROW_8; row >= ROW_1; row -= ROW_1)
	{
		std::cout << row << " |";

		for (int column = COLUMN_A; column <= COLUMN_H; column += COLUMN_A)
		{
			squares_on_board.at({ column, row }).PrintSquare();
		}

		std::cout << row << std::endl;
		std::cout << "   " << std::string(chars_per_column, border) << std::endl;
	}

	std::cout << "   " << " A " << " B " << " C " << " D " << " E " << " F " << " G " << " H " << std::endl << std::endl;
}

Piece* Board::GetPieceFromBoard(const int& column, const int& row) const
{
	return squares_on_board.at({ column, row }).GetPieceOnSquare();
}

const std::map<PieceColor, std::string> color_to_string =
{
	{ PieceColor::White, "White" },
	{ PieceColor::Black, "Black" },
};
const std::map<int, char> int_to_column =
{
	{ COLUMN_A, 'A' },
	{ COLUMN_B, 'B' },
	{ COLUMN_C, 'C' },
	{ COLUMN_D, 'D' },
	{ COLUMN_E, 'E' },
	{ COLUMN_F, 'F' },
	{ COLUMN_G, 'G' },
	{ COLUMN_H, 'H' },
};
const std::map<int, char> int_to_row =
{
	{ ROW_1, '1' },
	{ ROW_2, '2' },
	{ ROW_3, '3' },
	{ ROW_4, '4' },
	{ ROW_5, '5' },
	{ ROW_6, '6' },
	{ ROW_7, '7' },
	{ ROW_8, '8' },
};

bool Board::CorrectUserInput(const std::string& user_input, const PieceColor& color) const
{
	/* assume user_input has correct format*/
	const int current_column_index = 0;
	const int current_row_index = 1;
	const int new_column_index = 3;
	const int new_row_index = 4;

	const int current_column = user_input.at(current_column_index) - ASCII_COLUMN_OFFSET;
	const int current_row = user_input.at(current_row_index) - ASCII_ROW_OFFSET;
	const int new_column = user_input.at(new_column_index) - ASCII_COLUMN_OFFSET;
	const int new_row = user_input.at(new_row_index) - ASCII_ROW_OFFSET;

	bool valid_user_input = false;

	if (GetPieceFromBoard(current_column, current_row) == nullptr)
	{
		std::cout << int_to_column.at(current_column) << int_to_row.at(current_row) << ": This square is empty." << std::endl;
		return valid_user_input;
	}

	for (const auto& piece : pieces_on_board)
	{
		if (piece->GetColumn() == current_column && piece->GetRow() == current_row)
		{
			if (piece->GetPieceColor() != color)
			{
				/* break loop since every position/square can only have one piece */
				std::cout << int_to_column.at(current_column) << int_to_row.at(current_row) <<
					": This piece does not belong to player " << color_to_string.at(color) << std::endl;
				break;
			}

			if (piece->IsMoveValid(*this, new_column, new_row))
			{
				std::cout << int_to_column.at(current_column) << int_to_row.at(current_row) << ": This move is legal." << std::endl;
				valid_user_input = true;
				break;
			}
			else
			{
				std::cout << int_to_column.at(new_column) << int_to_row.at(new_row) <<
					": This move is illegal." << std::endl;
				break;
			}
		}
	}

	return valid_user_input;
}

/* TODO: add a parameter that will identify which type of move (e.g. capture, move, enpassant, promotion, castle, promotion) */
void Board::MovePiece(const std::string& user_input)
{
	const int current_column_index = 0;
	const int current_row_index = 1;
	const int new_column_index = 3;
	const int new_row_index = 4;

	const int current_column = user_input.at(current_column_index) - ASCII_COLUMN_OFFSET;
	const int current_row = user_input.at(current_row_index) - ASCII_ROW_OFFSET;
	const int new_column = user_input.at(new_column_index) - ASCII_COLUMN_OFFSET;
	const int new_row = user_input.at(new_row_index) - ASCII_ROW_OFFSET;

	Piece* move_this_piece;

	for (auto& piece : pieces_on_board)
	{
		if (piece->GetColumn() == current_column && piece->GetRow() == current_row)
		{
			/* this condition should be true once every time this function is called */
			move_this_piece = piece;
			break;
		}
	}

	move_this_piece->SetColumnRow(new_column, new_row);
	squares_on_board.at({ current_column, current_row }).RemovePieceOnSquare();
	squares_on_board.at({ new_column, new_row }).InsertPiece(move_this_piece);

	/*
	if (move_type == MoveType::Move)
	{
		move_this_piece->SetColumnRow(new_column, new_row);
		squares_on_board.at({ current_column, current_row }).RemovePieceOnSquare();
		squares_on_board.at({ new_column, new_row }).InsertPiece(move_this_piece);
	}
	else if (move_type == MoveType::Capture)
	{

	}
	else if (move_type == MoveType::Enpassant)
	{

	}
	else if (move_type == MoveType::Castle)
	{

	}
	etc.
	*/
}
