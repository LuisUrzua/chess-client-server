#include "include/Piece.h"

Piece::Piece(PieceColor color, PieceType type, int c, int r)
{
	piece_color = color;
	piece_type = type;
	column = c;
	row = r;
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

void Piece::SetColumn(const int& c)
{
	column = c;
}

void Piece::SetRow(const int& r)
{
	row = r;
}
