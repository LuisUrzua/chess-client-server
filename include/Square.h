#ifndef SQUARE_H
#define SQUARE_H

class Piece;

class Square
{
public:
	Square(int, int);
	void InsertPiece(Piece*);
	void PrintSquare() const;
	Piece* GetPieceOnSquare() const;

private:
	int column;
	int row;
	Piece* piece_on_square;
};

#endif
