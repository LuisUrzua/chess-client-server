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

class Piece
{
public:
	Piece(PieceColor, PieceType, int, int);
	PieceColor GetPieceColor() const;
	PieceType GetPieceType() const;
	int GetColumn() const;
	int GetRow() const;
	void SetColumn(const int&);
	void SetRow(const int&);
	virtual void PrintPiece() const = 0;

private:
	PieceColor piece_color;
	PieceType piece_type;
	int column;
	int row;
};

#endif
