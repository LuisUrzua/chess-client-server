#include "include/Piece.h"

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
}

MoveType Piece::GetMoveType() const
{
	return move_type;
}

void Piece::SetMoveType(const MoveType& type_of_move)
{
	move_type = type_of_move;
}
