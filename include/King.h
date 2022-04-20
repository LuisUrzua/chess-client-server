#ifndef KING_H
#define KING_H

#include "include/Piece.h"

class King : public Piece
{
public:
	King(PieceColor, int, int);
	~King() override;
	void PrintPiece() const override;
	bool IsMoveValid(const Board&, const int&, const int&) override;
	void UpdateListOfAttacks(const Board&) override;
	bool Checkmate(const Board&) override;

private:
	bool MoveOrCapture(const Board&, const int&, const int&);
	bool CastleQueenside(const Board&, const int&, const int&);
	bool CastleKingside(const Board&, const int&, const int&);
	bool MoveKingOutOfCheck(const Board&);
	bool CaptureAttackingEnemyPiece(const Board&, const Piece*);
	bool BlockAttackingEnemyPiece(const Board&, const Piece*);
};

#endif
