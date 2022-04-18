#ifndef ROOK_H
#define ROOK_H

#include "include/Piece.h"

class Rook : public Piece
{
public:
	Rook(PieceColor, int, int);
	~Rook() override;
	void PrintPiece() const override;
	bool IsMoveValid(const Board&, const int&, const int&) override;
	void UpdateListOfAttacks(const Board&) override;
};

#endif
