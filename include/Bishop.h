#ifndef BISHOP_H
#define BISHOP_H

#include "include/Piece.h"

class Bishop : public Piece
{
public:
	Bishop(PieceColor, int, int);
	~Bishop() override;
	void PrintPiece() const override;
	bool IsMoveValid(const Board&, const int&, const int&) override;
	void UpdateListOfAttacks(const Board&) override;
};

#endif
