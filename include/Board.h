#ifndef BOARD_H
#define BOARD_H

#include "include/Square.h"

#include <map>
#include <vector>

class Piece;

typedef std::map<std::pair<int, int>, Square> MapOfSquares;
typedef std::vector<Piece*> VectorOfPieces;

class Board
{
public:
	Board();
	void PrintBoard() const;

private:
	MapOfSquares squares_on_board;
	VectorOfPieces pieces_on_board;
};

#endif
