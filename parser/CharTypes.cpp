// g++ x.cpp -std=c++11

#include <iostream>
#include <vector>
#include "CharTypes.h"
#include "LayoutCharacters.h"

bool CharTypes::hexFlags[256]= {false};
bool CharTypes::firstIdentifierFlags[256]= {false};
bool CharTypes::identifierFlags[256]= {false};
bool CharTypes::whitespaceFlags[256]= {false};

//http://www.codeproject.com/Articles/18314/Static-Initialization-Function-in-Classes
bool CharTypes::__init = CharTypes::init();
bool CharTypes::init() 
{
	// hex 
	for (short c = 0; c < 256; ++c) {
		//std::cout << " in hex " << c << std::endl;
		if (c >= 'A' && c <= 'F') {
			hexFlags[c] = true;
		} else if (c >= 'a' && c <= 'f') {
			hexFlags[c] = true;
		} else if (c >= '0' && c <= '9') {
			hexFlags[c] = true;
		}
	}
	//std::cout << "hex done" << std::endl;
	// hex  done

	// firstidentifierflags
	for (short c = 0; c < 256; ++c) {
		//std::cout << "firstIdentifierFlags " << c << std::endl;
		if (c >= 'A' && c <= 'Z') {
			firstIdentifierFlags[c] = true;
		} else if (c >= 'a' && c <= 'z') {
			firstIdentifierFlags[c] = true;
		}
	}
	firstIdentifierFlags['`'] = true;
	firstIdentifierFlags['_'] = true;
	firstIdentifierFlags['$'] = true;
	//return;

	// firstidentifierflags done


	//identifierflags 
	for (short c = 0; c < 256; ++c) {
		if (c >= 'A' && c <= 'Z') {
			identifierFlags[c] = true;
		} else if (c >= 'a' && c <= 'z') {
			identifierFlags[c] = true;
		} else if (c >= '0' && c <= '9') {
			identifierFlags[c] = true;
		}
	}
	// identifierFlags['`'] = true;
	identifierFlags['_'] = true;
	identifierFlags['$'] = true;
	identifierFlags['#'] = true;
	//identifierflags  done



	// whitespaceflags 
	for (int i = 0; i <= 32; ++i) {
		whitespaceFlags[i] = true;
	}

	whitespaceFlags[LayoutCharacters::EOI] = false;
	for (int i = 0x7F; i <= 0xA0; ++i) {
		whitespaceFlags[i] = true;
	}

	whitespaceFlags[160] = true; // 特别处理
	// whitespaceflags  done

	return true;
}

CharTypes::CharTypes () 
{
	std::cout << " in CharTypes's constructor " << std::endl;
}

CharTypes::~CharTypes () 
{
	std::cout << " in CharTypes's destructor " << std::endl;
}
bool CharTypes::isIdentifierChar(char c) {
	//if (c <= identifierFlags.length) {
	if (c <= (sizeof(identifierFlags)/sizeof(*identifierFlags)) ) {
		return identifierFlags[c];
	}
	//return c != '　' && c != '，';
	return false;
}


bool CharTypes::isHex(char c) {
	return c < 256 && hexFlags[c];
}

bool CharTypes::isDigit(char c) {

	std::cout << "in CharTypes isDigit"<< std::endl;
	return c >= '0' && c <= '9';
}

bool CharTypes::isFirstIdentifierChar(char c) {

	//std::cout << "in CharTypes::isFirstIdentifierChar " << std::endl;

	//std::string x(&c);
	//bool b =  (x != "　" && x != "，");
	//if (b)
		//return b;

	if (c <= 256) {
		//std::cout << "in CharTypes::isFirstIdentifierChar , c <= 256, c is:  " << c <<  ", and firstIdentifierFlags[c] is: " << firstIdentifierFlags[c] << std::endl;
		return firstIdentifierFlags[c];
	}
	return false;
	//std::string x(&c);
	//return x != "　" && x != "，";
}

/**
 * @return false if {@link LayoutCharacters#EOI}
 */
bool CharTypes::isWhitespace(char c) {
	return (
			//c == '　' // Chinese space
			//||	
			c <= 256 && whitespaceFlags[c]);
}

bool CharTypes::isWhitespace(std::string c) {
	bool a = (c.compare("　") == 0 ); // Chinese space
	char x = c.at(0);
	return (
			a
			||	x <= 256 && whitespaceFlags[x]);
}

