#include "include/Piece.h"
#include "include/Board.h"

#define NUMBER_OF_COLUMNS 8
#define NUMBER_OF_ROWS 8
#define COLUMN_LIMIT_LEFT 1
#define COLUMN_LIMIT_RIGHT 8
#define ROW_LIMIT_BOTTOM 1
#define ROW_LIMIT_TOP 8

PairOfInts Piece::last_used_piece;

Piece::Piece(PieceColor color, PieceType type, int c, int r)
{
	piece_color = color;
	piece_type = type;
	column = c;
	row = r;
	move_type = MoveType::Undefined;
}

Piece::~Piece()
{

}

PieceColor Piece::GetPieceColor() const
{
	return piece_color;
}

PieceType Piece::GetPieceType() const
{
	return piece_type;
}

int Piece::GetColumn() const
{
	return column;
}

int Piece::GetRow() const
{
	return row;
}

void Piece::SetColumnRow(const int& c, const int& r)
{
	column = c;
	row = r;
	list_of_moves.push_back({ column, row });
	Piece::last_used_piece = { column, row };
}

MoveType Piece::GetMoveType() const
{
	return move_type;
}

void Piece::SetMoveType(const MoveType& type_of_move)
{
	move_type = type_of_move;
}

VectorOfIntPairs Piece::GetListOfMoves() const
{
	return list_of_moves;
}

PairOfInts Piece::GetLastUsedPiece() const
{
	return Piece::last_used_piece;
}

VectorOfIntPairs Piece::GetListOfAttacks() const
{
	return list_of_attacks;
}

bool Piece::ColumnRowWithinBounds(const int& c, const int& r) const
{
	if (c >= COLUMN_LIMIT_LEFT && c <= COLUMN_LIMIT_RIGHT && r >= ROW_LIMIT_BOTTOM && r <= ROW_LIMIT_TOP)
	{
		return true;
	}
	else
	{
		return false;
	}
}
