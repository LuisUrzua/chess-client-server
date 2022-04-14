#include "include/Input.h"

#include <iostream>

Input::Input()
{

}

std::string Input::ReadInput()
{
	std::cout << "Enter input: ";
	std::string user_input;
	std::getline(std::cin, user_input);
	
	return user_input;
}
