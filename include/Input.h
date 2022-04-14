#ifndef INPUT_H
#define INPUT_H

#include <string>

class Input
{
public:
	Input();
	std::string ReadInput();

private:
	bool CorrectInputLength(const std::string&);
	bool CorrectFormat(std::string&);
};

#endif
