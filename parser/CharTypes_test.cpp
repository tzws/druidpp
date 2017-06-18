// g++ x.cpp -std=c++11
#include <iostream>
#include <vector>
#include "CharTypes.h"

int main ()
{
	CharTypes c;
	std::cout << c.isDigit('9') << std::endl;
	std::cout << c.isWhitespace(' ') << std::endl;
	std::cout << c.isWhitespace("　") << std::endl;
	std::cout << c.isFirstIdentifierChar(',') << std::endl;
	std::cout << c.isIdentifierChar('$') << std::endl;
	std::cout << c.isIdentifierChar('z') << std::endl;
	std::cout << c.isIdentifierChar(' ') << std::endl;

  return 0;
}
