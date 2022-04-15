#ifndef PAWN_H
#define PAWN_H

#include "include/Piece.h"

class Pawn : public Piece
{
public:
	Pawn(PieceColor, int, int);
	void PrintPiece() const override;

private:
};

#endif
