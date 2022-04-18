#ifndef BOARD_H
#define BOARD_H

#include "include/Square.h"

#include <map>
#include <vector>

enum class PieceColor;

class Piece;

typedef std::map<std::pair<int, int>, Square> MapOfSquares;
typedef std::vector<Piece*> VectorOfPieces;

class Board
{
public:
	Board();
	~Board();
	void PrintBoard() const;
	Piece* GetPieceFromBoard(const int&, const int&) const;
	bool CorrectUserInput(const std::string&, const PieceColor&) const;
	void UpdateBoard(const std::string&);
	void MovePiece(Piece*, const int&, const int&);
	void CapturePiece(Piece*, const int&, const int&);
	void Enpassant(Piece*, const int&, const int&);
	// bool Stalemate();
	// bool Checkmate();

private:
	MapOfSquares squares_on_board;
	VectorOfPieces pieces_on_board;
	Piece* last_used_piece;
};

#endif
