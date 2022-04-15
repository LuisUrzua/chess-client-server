#include "include/Input.h"
#include "include/Piece.h"
#include "include/Board.h"

#include <iostream>
#include <algorithm>

#define ASCII_A 0x41
#define ASCII_H 0x48
#define ASCII_1 0x31
#define ASCII_8 0x38
#define ASCII_FORWARD_SLASH 0x2F

std::map<std::string, PieceColor> string_to_color =
{
	{ "White", PieceColor::White },
	{ "Black", PieceColor::Black },
};

Input::Input(std::string color)
{
	player_color = string_to_color.at(color);
}

std::string Input::ReadInput(const Board& chess_board)
{
	std::string user_input;

	while (true)
	{
		std::cout << "Enter input: ";
		std::getline(std::cin, user_input);

		if (!CorrectInputLength(user_input))
		{
			std::cout << "Incorrect input size, try again." << std::endl;
			continue;
		}
		else if (!CorrectFormat(user_input))
		{
			std::cout << "Incorrect format, try again." << std::endl;
			continue;
		}
		else if (!chess_board.CorrectUserInput(user_input, player_color))
		{
			continue;
		}
		else
		{

			break;
		}
	}

	return user_input;
}

bool Input::CorrectInputLength(const std::string& user_input)
{
	const int input_size = 5;
	return (user_input.size() == input_size) ? true : false;
}

bool Input::CorrectFormat(std::string& user_input)
{
	const int source_column_index = 0;
	const int source_row_index = 1;
	const int forward_slash_index = 2;
	const int destination_column_index = 3;
	const int destination_row_index = 4;

	std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::toupper);

	const char source_column_char = user_input.at(source_column_index);
	const int source_row_char = user_input.at(source_row_index);
	const int forward_slash_char = user_input.at(forward_slash_index);
	const int destination_column_char = user_input.at(destination_column_index);
	const int destination_row_char = user_input.at(destination_row_index);

	if (source_column_char < ASCII_A || source_column_char > ASCII_H)
	{
		return false;
	}
	else if (source_row_char < ASCII_1 || source_row_char > ASCII_8)
	{
		return false;
	}
	else if (forward_slash_char != ASCII_FORWARD_SLASH)
	{
		return false;
	}
	else if (destination_column_char < ASCII_A || destination_column_char > ASCII_H)
	{
		return false;
	}
	else if (destination_row_char < ASCII_1 || destination_row_char > ASCII_8)
	{
		return false;
	}
	else
	{
		return true;
	}
}
