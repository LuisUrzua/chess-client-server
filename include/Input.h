#ifndef INPUT_H
#define INPUT_H

#include <string>

enum class PieceColor;

class Board;

class Input
{
public:
	Input(std::string);
	std::string ReadInput(const Board&);

private:
	bool CorrectInputLength(const std::string&);
	bool CorrectFormat(std::string&);

private:
	PieceColor player_color;
};

#endif
