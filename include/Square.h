#ifndef SQUARE_H
#define SQUARE_H

#include <vector>

class Piece;

typedef std::pair<int, int> ColumnRowPair;
typedef std::vector<ColumnRowPair> VectorOfColumnRow;

class Square
{
public:
	Square(int, int);
	void InsertPiece(Piece*);
	void PrintSquare() const;
	Piece* GetPieceOnSquare() const;
	void RemovePieceOnSquare();

private:
	int column;
	int row;
	Piece* piece_on_square;
};

#endif
