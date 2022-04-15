#ifndef PAWN_H
#define PAWN_H

#include "include/Piece.h"

class Pawn : public Piece
{
public:
	Pawn(PieceColor, int, int);
	void PrintPiece() const override;
	bool IsMoveValid(const Board&, const int&, const int&) override;

private:
	bool OneSquareForward(const Board&, const int&, const int&);
};

#endif
