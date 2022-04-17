#include "include/Piece.h"

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
