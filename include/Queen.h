#ifndef QUEEN_H
#define QUEEN_H

#include "include/Piece.h"

class Queen : public Piece
{
public:
	Queen(PieceColor, int, int);
	~Queen() override;
	void PrintPiece() const override;
	bool IsMoveValid(const Board&, const int&, const int&) override;
	void UpdateListOfAttacks(const Board&) override;

private:
	bool MoveLikeRook(const Board&, const int&, const int&);
	bool MoveLikeBishop(const Board&, const int&, const int&);
};

#endif
