#ifndef PIECE_H
#define PIECE_H

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
	virtual void PrintPiece() const = 0;
	virtual bool IsMoveValid(const Board&, const int&, const int&) = 0;

private:
	PieceColor piece_color;
	PieceType piece_type;
	int column;
	int row;
	MoveType move_type;
};

#endif
