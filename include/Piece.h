#ifndef PIECE_H
#define PIECE_H

#include <vector>

enum class PieceColor
{
	White,
	Black,
};

enum class PieceType
{
	Pawn,
	Knight,
	Bishop,
	Rook,
	Queen,
	King,
};

enum class MoveType
{
	Move,
	Capture,
	Enpassant,
	Promote,
	CastleQueenside,
	CastleKingside,
	Undefined,
};

class Board;

typedef std::pair<int, int> PairOfInts;
typedef std::vector<PairOfInts> VectorOfIntPairs;

class Piece
{
public:
	Piece(PieceColor, PieceType, int, int);
	virtual ~Piece();
	PieceColor GetPieceColor() const;
	PieceType GetPieceType() const;
	int GetColumn() const;
	int GetRow() const;
	void SetColumnRow(const int&, const int&);
	MoveType GetMoveType() const;
	void SetMoveType(const MoveType&);
	VectorOfIntPairs GetListOfMoves() const;
	PairOfInts GetLastUsedPiece() const;
	VectorOfIntPairs GetListOfAttacks() const;
	virtual void PrintPiece() const = 0;
	virtual bool IsMoveValid(const Board&, const int&, const int&) = 0;
	virtual void UpdateListOfAttacks(const Board&) = 0;
	
protected:
	bool ColumnRowWithinBounds(const int&, const int&) const;
	int AbsoluteValue(const int&) const;

private:
	PieceColor piece_color;
	PieceType piece_type;
	int column;
	int row;
	MoveType move_type;
	VectorOfIntPairs list_of_moves;
	static PairOfInts last_used_piece;

protected:
	VectorOfIntPairs list_of_attacks;
};

#endif
