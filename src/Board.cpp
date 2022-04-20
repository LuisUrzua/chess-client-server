#include "include/Board.h"
#include "include/Pawn.h"
#include "include/King.h"
#include "include/Rook.h"
#include "include/Bishop.h"
#include "include/Knight.h"
#include "include/Queen.h"

#include <iostream>
#include <algorithm>

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

	pieces_on_board.push_back(new Knight(PieceColor::White, COLUMN_B, ROW_1));
	pieces_on_board.push_back(new Knight(PieceColor::White, COLUMN_G, ROW_1));

	pieces_on_board.push_back(new Bishop(PieceColor::White, COLUMN_C, ROW_1));
	pieces_on_board.push_back(new Bishop(PieceColor::White, COLUMN_F, ROW_1));

	pieces_on_board.push_back(new Rook(PieceColor::White, COLUMN_A, ROW_1));
	pieces_on_board.push_back(new Rook(PieceColor::White, COLUMN_H, ROW_1));

	pieces_on_board.push_back(new Queen(PieceColor::White, COLUMN_D, ROW_1));

	pieces_on_board.push_back(new King(PieceColor::White, COLUMN_E, ROW_1));

	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_A, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_B, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_C, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_D, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_E, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_F, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_G, ROW_2));
	pieces_on_board.push_back(new Pawn(PieceColor::White, COLUMN_H, ROW_2));

	pieces_on_board.push_back(new Knight(PieceColor::Black, COLUMN_B, ROW_8));
	pieces_on_board.push_back(new Knight(PieceColor::Black, COLUMN_G, ROW_8));

	pieces_on_board.push_back(new Bishop(PieceColor::Black, COLUMN_C, ROW_8));
	pieces_on_board.push_back(new Bishop(PieceColor::Black, COLUMN_F, ROW_8));

	pieces_on_board.push_back(new Rook(PieceColor::Black, COLUMN_A, ROW_8));
	pieces_on_board.push_back(new Rook(PieceColor::Black, COLUMN_H, ROW_8));

	pieces_on_board.push_back(new Queen(PieceColor::Black, COLUMN_D, ROW_8));

	pieces_on_board.push_back(new King(PieceColor::Black, COLUMN_E, ROW_8));

	pieces_on_board.push_back(new Pawn(PieceColor::Black, COLUMN_A, ROW_7));
	pieces_on_board.push_back(new Pawn(PieceColor::Black, COLUMN_B, ROW_7));
	pieces_on_board.push_back(new Pawn(PieceColor::Black, COLUMN_C, ROW_7));
	pieces_on_board.push_back(new Pawn(PieceColor::Black, COLUMN_D, ROW_7));
	pieces_on_board.push_back(new Pawn(PieceColor::Black, COLUMN_E, ROW_7));
	pieces_on_board.push_back(new Pawn(PieceColor::Black, COLUMN_F, ROW_7));
	pieces_on_board.push_back(new Pawn(PieceColor::Black, COLUMN_G, ROW_7));
	pieces_on_board.push_back(new Pawn(PieceColor::Black, COLUMN_H, ROW_7));

	for (const auto& piece : pieces_on_board)
	{
		squares_on_board.at({ piece->GetColumn(), piece->GetRow() }).InsertPiece(piece);
	}
}

Board::~Board()
{
	/* delete pieces and squares */
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

	//for (const auto& piece : pieces_on_board)
	//{
	//	piece->PrintPiece();
	//	std::cout << ": " << piece->GetColumn() << piece->GetRow() << ": " << color_to_string.at(piece->GetPieceColor()) << std::endl;
	//}

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
				std::cout << int_to_column.at(new_column) << int_to_row.at(new_row) << ": This move is legal." << std::endl;
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

void Board::UpdateBoard(std::string& user_input)
{
	const int current_column_index = 0;
	const int current_row_index = 1;
	const int new_column_index = 3;
	const int new_row_index = 4;

	const int current_column = user_input.at(current_column_index) - ASCII_COLUMN_OFFSET;
	const int current_row = user_input.at(current_row_index) - ASCII_ROW_OFFSET;
	const int new_column = user_input.at(new_column_index) - ASCII_COLUMN_OFFSET;
	const int new_row = user_input.at(new_row_index) - ASCII_ROW_OFFSET;

	Piece* player_piece;

	for (auto& piece : pieces_on_board)
	{
		if (piece->GetColumn() == current_column && piece->GetRow() == current_row)
		{
			/* this condition should be true once every time this function is called */
			player_piece = piece;
			break;
		}
	}

	/* call this function to ensure that the MoveType is updated */
	player_piece->IsMoveValid(*this, new_column, new_row);

	if (player_piece->GetMoveType() == MoveType::Move)
	{
		MovePiece(player_piece, new_column, new_row);
	}
	else if (player_piece->GetMoveType() == MoveType::Capture)
	{
		CapturePiece(player_piece, new_column, new_row);
	}
	else if (player_piece->GetMoveType() == MoveType::Enpassant)
	{
		Enpassant(player_piece, new_column, new_row);
	}
	else if (player_piece->GetMoveType() == MoveType::Promote)
	{
		Promote(player_piece, new_column, new_row, user_input);
	}
	else if (player_piece->GetMoveType() == MoveType::CastleQueenside)
	{
		CastleQueenside(player_piece, new_column, new_row);
	}
	else if (player_piece->GetMoveType() == MoveType::CastleKingside)
	{
		CastleKingside(player_piece, new_column, new_row);
	}
	else
	{
		std::cout << "Error: Undefined move type" << std::endl;
	}

	for (auto& piece : pieces_on_board)
	{
		piece->UpdateListOfAttacks(*this);
	}

	Checkmate((player_piece->GetPieceColor() == PieceColor::White) ? PieceColor::Black : PieceColor::White);
	Stalemate((player_piece->GetPieceColor() == PieceColor::White) ? PieceColor::Black : PieceColor::White);
}

void Board::MovePiece(Piece* player_piece, const int& new_column, const int& new_row)
{
	squares_on_board.at({ player_piece->GetColumn(), player_piece->GetRow() }).RemovePieceOnSquare();
	player_piece->SetColumnRow(new_column, new_row);
	squares_on_board.at({ new_column, new_row }).InsertPiece(player_piece);
}

void Board::CapturePiece(Piece* player_piece, const int& new_column, const int& new_row)
{
	squares_on_board.at({ player_piece->GetColumn(), player_piece->GetRow() }).RemovePieceOnSquare();
	squares_on_board.at({ new_column, new_row }).RemovePieceOnSquare();

	const Piece* enemy_piece;

	for (const auto& piece : pieces_on_board)
	{
		if (piece->GetColumn() == new_column && piece->GetRow() == new_row)
		{
			enemy_piece = piece;
			break;
		}
	}

	pieces_on_board.erase(std::remove(pieces_on_board.begin(), pieces_on_board.end(), enemy_piece), pieces_on_board.end());
	player_piece->SetColumnRow(new_column, new_row);
	squares_on_board.at({ new_column, new_row }).InsertPiece(player_piece);
}

void Board::Enpassant(Piece* player_pawn, const int& new_column, const int& new_row)
{
	const int enpassant_column = new_column;
	const int enpassant_row = player_pawn->GetRow();
	squares_on_board.at({ enpassant_column, enpassant_row }).RemovePieceOnSquare();
	const Piece* enemy_piece;

	for (const auto& piece : pieces_on_board)
	{
		if (piece->GetColumn() == enpassant_column && piece->GetRow() == enpassant_row)
		{
			enemy_piece = piece;
			break;
		}
	}

	pieces_on_board.erase(std::remove(pieces_on_board.begin(), pieces_on_board.end(), enemy_piece), pieces_on_board.end());
	squares_on_board.at({ player_pawn->GetColumn(), player_pawn->GetRow() }).RemovePieceOnSquare();
	player_pawn->SetColumnRow(new_column, new_row);
	squares_on_board.at({ new_column, new_row }).InsertPiece(player_pawn);
}

void Board::Promote(Piece* player_pawn, const int& new_column, const int& new_row, std::string& user_input)
{
	const Piece* enemy_piece = GetPieceFromBoard(new_column, new_row);
	const MoveType move_or_capture = (enemy_piece != nullptr) ? MoveType::Capture : MoveType::Move;

	if (move_or_capture == MoveType::Capture)
	{
		squares_on_board.at({ new_column, new_row }).RemovePieceOnSquare();
		pieces_on_board.erase(std::remove(pieces_on_board.begin(), pieces_on_board.end(), enemy_piece), pieces_on_board.end());
	}

	if (user_input.size() == 5)
	{
		std::string pawn_promotion;

		while (true)
		{
			std::cout << "Pawn promotion. Choose any of the following: (K)night, (B)ishop, (R)ook, (Q)ueen -> ";
			std::getline(std::cin, pawn_promotion);
			std::transform(pawn_promotion.begin(), pawn_promotion.end(), pawn_promotion.begin(), ::toupper);

			if (pawn_promotion.size() != 1)
			{
				std::cout << "Input size must be 1 letter. Try again." << std::endl;
				continue;
			}
			else if (pawn_promotion.at(0) != 'K' && pawn_promotion.at(0) != 'B' && pawn_promotion.at(0) != 'R' && pawn_promotion.at(0) != 'Q')
			{
				std::cout << "Letter must be 'K', 'B', 'R', or 'Q'. Try again." << std::endl;
				continue;
			}
			else
			{
				user_input.append(pawn_promotion);

				if (pawn_promotion.at(0) == 'K')
				{
					pieces_on_board.push_back(new Knight(player_pawn->GetPieceColor(), new_column, new_row));
				}
				else if (pawn_promotion.at(0) == 'B')
				{
					pieces_on_board.push_back(new Bishop(player_pawn->GetPieceColor(), new_column, new_row));
				}
				else if (pawn_promotion.at(0) == 'R')
				{
					pieces_on_board.push_back(new Rook(player_pawn->GetPieceColor(), new_column, new_row));
				}
				else if (pawn_promotion.at(0) == 'Q')
				{
					pieces_on_board.push_back(new Queen(player_pawn->GetPieceColor(), new_column, new_row));
				}

				break;
			}
		}
	}
	else if (user_input.size() == 6)
	{
		std::cout << "Pawn promotion." << std::endl;

		if (user_input.at(5) == 'K')
		{
			pieces_on_board.push_back(new Knight(player_pawn->GetPieceColor(), new_column, new_row));
		}
		else if (user_input.at(5) == 'B')
		{
			pieces_on_board.push_back(new Bishop(player_pawn->GetPieceColor(), new_column, new_row));
		}
		else if (user_input.at(5) == 'R')
		{
			pieces_on_board.push_back(new Rook(player_pawn->GetPieceColor(), new_column, new_row));
		}
		else if (user_input.at(5) == 'Q')
		{
			pieces_on_board.push_back(new Queen(player_pawn->GetPieceColor(), new_column, new_row));
		}
	}

	squares_on_board.at({ new_column, new_row }).InsertPiece(pieces_on_board.back());
	squares_on_board.at({ player_pawn->GetColumn(), player_pawn->GetRow() }).RemovePieceOnSquare();
	pieces_on_board.erase(std::remove(pieces_on_board.begin(), pieces_on_board.end(), player_pawn), pieces_on_board.end());
}

void Board::CastleQueenside(Piece* player_king, const int& new_column, const int& new_row)
{
	const int rook_column = COLUMN_A;
	const int rook_row = player_king->GetRow();
	const int rook_column_destination = COLUMN_D;
	const int rook_row_destination = player_king->GetRow();
	Piece* player_rook = GetPieceFromBoard(rook_column, rook_row);

	squares_on_board.at({ rook_column, rook_row }).RemovePieceOnSquare();
	player_rook->SetColumnRow(rook_column_destination, rook_row_destination);
	squares_on_board.at({ rook_column_destination, rook_row_destination }).InsertPiece(player_rook);

	squares_on_board.at({ player_king->GetColumn(), player_king->GetRow() }).RemovePieceOnSquare();
	player_king->SetColumnRow(new_column, new_row);
	squares_on_board.at({ new_column, new_row }).InsertPiece(player_king);
}

void Board::CastleKingside(Piece* player_king, const int& new_column, const int& new_row)
{
	const int rook_column = COLUMN_H;
	const int rook_row = player_king->GetRow();
	const int rook_column_destination = COLUMN_F;
	const int rook_row_destination = player_king->GetRow();
	Piece* player_rook = GetPieceFromBoard(rook_column, rook_row);

	squares_on_board.at({ rook_column, rook_row }).RemovePieceOnSquare();
	player_rook->SetColumnRow(rook_column_destination, rook_row_destination);
	squares_on_board.at({ rook_column_destination, rook_row_destination }).InsertPiece(player_rook);

	squares_on_board.at({ player_king->GetColumn(), player_king->GetRow() }).RemovePieceOnSquare();
	player_king->SetColumnRow(new_column, new_row);
	squares_on_board.at({ new_column, new_row }).InsertPiece(player_king);
}

void Board::Checkmate(const PieceColor& enemy_color)
{
	Piece* enemy_king;

	for (const auto& piece : pieces_on_board)
	{
		if (piece->GetPieceType() == PieceType::King && piece->GetPieceColor() == enemy_color)
		{
			enemy_king = piece;
			break;
		}
	}

	if (enemy_king->Checkmate(*this))
	{
		PrintBoard();
		std::cout << "Checkmate! " << ((enemy_color == PieceColor::White) ? "Black" : "White") << " wins." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Board::Stalemate(const PieceColor& enemy_color)
{
	bool at_least_one_valid_move = false;

	for (const auto& piece : pieces_on_board)
	{
		if (piece->GetPieceColor() == enemy_color)
		{
			for (int c = COLUMN_A; c <= COLUMN_H; c++)
			{
				for (int r = ROW_1; r <= ROW_8; r++)
				{
					MoveType save_move = piece->GetMoveType();
					
					if (piece->IsMoveValid(*this, c, r))
					{
						at_least_one_valid_move = true;
						piece->SetMoveType(save_move);
						return;
					}
					else
					{
						piece->SetMoveType(save_move);
					}
				}
			}
		}
	}

	if (!at_least_one_valid_move)
	{
		PrintBoard();
		std::cout << "Stalemate! It's a draw." << std::endl;
		exit(EXIT_FAILURE);
	}
}
