#ifndef KNIGHT_H
#define KNIGHT_H

#include <include/Piece.h>

class Knight : public Piece
{
public:
	Knight(PieceColor, int, int);
	~Knight() override;
	void PrintPiece() const override;
	bool IsMoveValid(const Board&, const int&, const int&) override;
	void UpdateListOfAttacks(const Board&) override;
};

#endif
