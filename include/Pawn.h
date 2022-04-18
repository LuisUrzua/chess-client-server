#ifndef PAWN_H
#define PAWN_H

#include "include/Piece.h"

class Pawn : public Piece
{
public:
	Pawn(PieceColor, int, int);
	~Pawn() override;
	void PrintPiece() const override;
	bool IsMoveValid(const Board&, const int&, const int&) override;
	void UpdateListOfAttacks(const Board&) override;

private:
	bool OneSquareForward(const Board&, const int&, const int&);
	bool TwoSquaresForward(const Board&, const int&, const int&);
	bool CaptureLeft(const Board&, const int&, const int&);
	bool CaptureRight(const Board&, const int&, const int&);
	bool EnpassantLeft(const Board&, const int&, const int&);
	bool EnpassantRight(const Board&, const int&, const int&);
};

#endif
