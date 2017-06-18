//http://codereview.stackexchange.com/questions/14309/conversion-between-enum-and-string-in-c-class-header
//http://stackoverflow.com/questions/207976/how-to-easily-map-c-enums-to-strings
#include <iostream>
#include "Token.h"

int main()
{
	std::cout << " enum SELECT = " << tokenStringList.at(TOKEN_SELECT) << std::endl;
	std::string all = "ALL";

	return 0;
}


